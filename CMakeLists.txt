function(checkSqlite)
    if (SQLITE3_LIBRARIES AND SQLITE3_INCLUDE_DIRS)
        set(SQLITE3_FOUND TRUE)
    else (SQLITE3_LIBRARIES AND SQLITE3_INCLUDE_DIRS)
        find_package(PkgConfig)
        if (PKG_CONFIG_FOUND)
            pkg_check_modules(_SQLITE3 REQUIRED sqlite3)
        else (PKG_CONFIG_FOUND)
            find_package(SQLite3 REQUIRED)
        endif (PKG_CONFIG_FOUND)
    endif()
endfunction()

cmake_minimum_required(VERSION 3.8)
project(SqlWrapper VERSION 1.0.0 LANGUAGES CXX)

option(SQLITE_BACKEND "build with sqlite support" ON)
option(POSTGRESQL_BACKEND "build with PostgreSql support" ON)

include(GNUInstallDirs) # Installation directories for `install` command and pkgconfig file
find_package(Threads REQUIRED)

set(LIB_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(LIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(BACKEND_LIBRARIES "")
if (POSTGRESQL_BACKEND)
    find_package(PostgreSQL REQUIRED)
    add_definitions(-DPQ_BACKEND)
    set(BACKEND_LIBRARIES ${BACKEND_LIBRARIES} ${PostgreSQL_LIBRARIES})
    set(BACKEND_SOURCES_PQ 
        ${LIB_SOURCE_DIR}/pq/connection_impl.cpp
        ${LIB_SOURCE_DIR}/pq/transaction_impl.cpp
        ${LIB_SOURCE_DIR}/pq/statement_impl.cpp
        ${LIB_SOURCE_DIR}/pq/transaction_statement_impl.cpp
        ${LIB_SOURCE_DIR}/pq/selector_impl.cpp
        ${LIB_SOURCE_DIR}/pq/db_row_impl.cpp)
endif()

if (SQLITE_BACKEND)
    checkSqlite()
    add_definitions(-DSQLITE_BACKEND)
    set(BACKEND_SOURCES_SQLITE 
        ${LIB_SOURCE_DIR}/sqlite/connection_impl.cpp
        ${LIB_SOURCE_DIR}/sqlite/transaction_impl.cpp
        ${LIB_SOURCE_DIR}/sqlite/statement_impl.cpp
        ${LIB_SOURCE_DIR}/sqlite/transaction_statement_impl.cpp
        ${LIB_SOURCE_DIR}/sqlite/selector_impl.cpp
        ${LIB_SOURCE_DIR}/sqlite/db_row_impl.cpp)
endif()

set(CMAKE_CXX_STANDARD 14)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-W -Wextra -Wall -Wno-gnu -pedantic)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-W -Wextra -Wall -pedantic)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  # using Visual Studio C++
endif()

set(LIB_PUBLIC_HEADERS
    ${LIB_INCLUDE_DIR}/database.h
    ${LIB_INCLUDE_DIR}/db_row.h
    ${LIB_INCLUDE_DIR}/statement.h
    ${LIB_INCLUDE_DIR}/transaction_statement.h  
    ${LIB_INCLUDE_DIR}/selector.h)

set(LIB_CPP_SOURCES
    ${BACKEND_SOURCES_PQ}
    ${BACKEND_SOURCES_SQLITE}
    ${LIB_SOURCE_DIR}/data.cpp
    ${LIB_SOURCE_DIR}/db_row_impl.cpp
    ${LIB_SOURCE_DIR}/connection_impl.cpp
    ${LIB_SOURCE_DIR}/selector.cpp
    ${LIB_SOURCE_DIR}/statement_impl.cpp
    ${LIB_SOURCE_DIR}/transaction.cpp
    ${LIB_SOURCE_DIR}/transaction_statement_impl.cpp)

set(LIB_SOURCES ${LIB_PUBLIC_HEADERS} ${LIB_CPP_SOURCES})
add_library(sql-wrapper-objects OBJECT ${LIB_SOURCES})
set_target_properties(sql-wrapper-objects PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(sql-wrapper SHARED $<TARGET_OBJECTS:sql-wrapper-objects>)
add_library(sql-wrapper-static STATIC $<TARGET_OBJECTS:sql-wrapper-objects>)
target_link_libraries(sql-wrapper ${BACKEND_LIBRARIES} Threads::Threads ${CMAKE_DL_LIBS})
target_link_libraries(sql-wrapper-static ${BACKEND_LIBRARIES} Threads::Threads ${CMAKE_DL_LIBS})

set_target_properties(sql-wrapper
    PROPERTIES
    PUBLIC_HEADER "${LIB_PUBLIC_HEADERS}"
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    OUTPUT_NAME "sql-wrapper")

install(TARGETS sql-wrapper
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT libraries # This is for Windows
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT libraries
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT static_libraries
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sql-wrapper COMPONENT dev)

option(ENABLE_EXAMPLES "Build and install examples (default ON)" ON)
if(ENABLE_EXAMPLES)
    add_subdirectory("${CMAKE_SOURCE_DIR}/examples")
endif()

if(WIN32 AND NOT CYGWIN)
    set(LIB_CONFIG_INSTALL_DIR CMake)
else()
    set(LIB_CONFIG_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/SqlWrapper)
endif()

include(CMakePackageConfigHelpers)

configure_file(SqlWrapperConfig.cmake.in SqlWrapperConfig.cmake @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/SqlWrapperConfig.cmake DESTINATION ${LIB_CONFIG_INSTALL_DIR} COMPONENT dev)

write_basic_package_version_file(SqlWrapperConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)

install(FILES ${CMAKE_BINARY_DIR}/SqlWrapperConfigVersion.cmake DESTINATION ${LIB_CONFIG_INSTALL_DIR} COMPONENT dev)

