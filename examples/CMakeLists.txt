add_executable (select select.cpp)
target_link_libraries (select LINK_PUBLIC sql-wrapper)

add_executable (statement statement.cpp)
target_link_libraries (statement LINK_PUBLIC sql-wrapper)
