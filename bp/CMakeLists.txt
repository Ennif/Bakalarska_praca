cmake_minimum_required(VERSION 3.10)

project(bp)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")

set(PQXX /usr/local/include/pqxx)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

add_executable(bp main.cpp Database/db_connection.cpp Database/db_connection.h Database/nlohmann/json.hpp data/pathToConfig.h Database/database_local/sqlite_local_path.h)

TARGET_LINK_LIBRARIES(bp  ${PQXX_LIB} ${PQ_LIB})