cmake_minimum_required(VERSION 3.6)
project(MQTT)

find_package (Threads REQUIRED)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/")
set(OPENSSL_USE_STATIC_LIBS TRUE)

include_directories(
        ${PROJECT_SOURCE_DIR}/ext/include)

link_directories(${PROJECT_SOURCE_DIR}/ext/lib)

file(GLOB sources "src/*.cpp")

set(CMAKE_CXX_STANDARD 11)

add_executable(MQTT ${PROJECT_SOURCE_DIR}/src/main.cpp)

# Add linked libraries
target_link_libraries (MQTT paho-mqttpp3 paho-mqtt3as ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY})
