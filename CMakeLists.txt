cmake_minimum_required(VERSION 3.6)
project(MQTT)

find_package (Threads REQUIRED)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/")

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/ext/include)

link_directories(${PROJECT_SOURCE_DIR}/ext/lib/paho-mqtt-c)
link_directories(${PROJECT_SOURCE_DIR}/ext/lib/paho-mqtt-cpp)

file(GLOB sources "src/*.cpp")

set(CMAKE_CXX_STANDARD 14)

add_executable(MQTT ${PROJECT_SOURCE_DIR}/src/main.cpp)

# Add linked libraries
target_link_libraries (MQTT ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries (MQTT ${PROJECT_SOURCE_DIR}/ext/lib/paho-mqtt-c/libpaho-mqtt3.a)
target_link_libraries (MQTT ${PROJECT_SOURCE_DIR}/ext/lib/paho-mqtt-cpp/libpaho-mqttpp3.a)