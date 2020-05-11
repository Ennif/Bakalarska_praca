cmake_minimum_required(VERSION 3.10)

project(bp)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()
#modify value "NAME", when your library is stored somewhere else
set(NAME /usr/local)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")
set(PQXX ${NAME}/include/pqxx)

set(LIB_DIR_LOCATION /usr/local/lib/)
find_library(sqlite3 PATHS ${LIB_DIR_LOCATION})
set(INCLUDE_DIRS ${NAME}/include/sqlite)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

set(SERVER_DATABASE Database/db_connection.cpp Database/db_connection.h data/pathToConfig.h)
set(LOCAL_DATABASE Database/database_local/sqlite_local_path.h Database/database_local/db_localDatabase.cpp Database/database_local/db_localDatabase.h)
add_executable(bp main.cpp  Database/nlohmann/json.hpp ${SERVER_DATABASE} ${LOCAL_DATABASE})

TARGET_LINK_LIBRARIES(bp  ${PQXX_LIB} ${PQ_LIB} sqlite3)
TARGET_INCLUDE_DIRECTORIES(bp PRIVATE ${INCLUDE_DIRS})