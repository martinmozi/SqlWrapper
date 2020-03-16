add_executable (select select.cpp)

target_link_libraries (select LINK_PUBLIC sql-wrapper)