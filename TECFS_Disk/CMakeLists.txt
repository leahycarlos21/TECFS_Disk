cmake_minimum_required(VERSION 3.12)
project(TECFS_Disk)

set(CMAKE_CXX_STANDARD 11)

add_executable(TECFS_Disk main.cpp Singleton.cpp Singleton.h GestorDB.cpp GestorDB.h GestorVideos.cpp GestorVideos.h DataStructures/LinkedList.h DataStructures/Node.h)
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")
find_package (SFML REQUIRED system window graphics network audio)

target_link_libraries(TECFS_Disk ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})