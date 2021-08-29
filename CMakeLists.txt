cmake_minimum_required(VERSION 3.11.3)

add_definitions(-std=c++17)
add_definitions(-pthread)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(face_detector)

find_package(OpenCV 4.5 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})


add_executable(emotion_detector src/main.cpp)
target_link_libraries(emotion_detector ${OpenCV_LIBRARIES})
