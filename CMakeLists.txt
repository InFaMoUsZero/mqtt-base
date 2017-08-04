cmake_minimum_required(VERSION 3.8)
project(MQTT)

find_package (threads REQUIRED)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/")

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/ext/include)

link_directories(${PROJECT_SOURCE_DIR}/ext/lib/paho-mqtt-c)
link_directories(${PROJECT_SOURCE_DIR}/ext/lib/paho-mqtt-cpp)

file(GLOB sources "src/*.cpp")

# Generates library-specific CMake variables for includes and libs paths
#find_package(PHAO-MQTT-C REQUIRED)
#find_package(PHAO-MQTT-CPP REQUIRED)

#include_directories(... ${PHAO-MQTT-C_INCLUDE_DIR})
#include_directories(... ${PHAO-MQTT-CPP_INCLUDE_DIR})

#target_link_libraries(target .. ${PHAO-MQTT-C_LIBRARY})
#target_link_libraries(target .. ${PHAO-MQTT-CPP_LIBRARY})

set(CMAKE_CXX_STANDARD 14)

add_executable(MQTT ${PROJECT_SOURCE_DIR}/src/Main.cpp)
target_link_libraries (MQTT ${PROJECT_SOURCE_DIR}/ext/lib/paho-mqtt-cpp/libpaho-mqttpp3.a)
target_link_libraries (MQTT ${PROJECT_SOURCE_DIR}/ext/lib/paho-mqtt-c/libpaho-mqtt3a.a)