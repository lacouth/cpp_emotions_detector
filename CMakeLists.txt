cmake_minimum_required(VERSION 3.11.3)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

project(face_detector)

find_package(OpenCV 4.5.3 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

file(GLOB SOURCES
    src/*.cpp)

add_executable(emotion_detector ${SOURCES})
target_link_libraries(emotion_detector ${OpenCV_LIBRARIES})
