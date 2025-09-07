cmake_minimum_required(VERSION 3.20)
set(PostgreSQL_ADDITIONAL_VERSIONS "17")
project(Task_01)
add_executable(Task_01 main.cpp Task_01.cpp Task_01.h)
add_subdirectory("C:\\libpqxx\\libpqxx-7.10.1" libpqxx-build) # Укажите путь к libpq++
target_compile_features(Task_01 PRIVATE cxx_std_17) # Включите C++17
target_link_libraries(Task_01 pqxx)