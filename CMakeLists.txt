cmake_minimum_required(VERSION 3.6)
project(mqtt-client-base)

find_package (Threads REQUIRED)
find_package (OpenSSL REQUIRED)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/" CACHE PATH "The executable output path")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/" CACHE PATH "The library output path")
set(OPENSSL_LIBRARY_FILE "" CACHE PATH "The directory containing the OpenSSL library")
set(OPENSSL_CRYPTO_FILE "" CACHE PATH "The directory containing the OpenSSL crypto library")
set(OPENSSL_USE_STATIC_LIBS TRUE CACHE BOOL "Use static linkage of the  OpenSSL libraries, opposed to dynamic linkage")

include_directories(${PROJECT_SOURCE_DIR}/ext/include
                    ${PROJECT_SOURCE_DIR}/include)

link_directories(${PROJECT_SOURCE_DIR}/ext/lib
                 ${OPENSSL_LIBRARY_PATH})

file(GLOB sources "src/*.cpp")
file(GLOB healders "include/*.h" "include/*.hpp")

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} ${sources} ${healders} src/Callbacks.cpp include/Callbacks.hpp)

# Add linked libraries
if(OPENSSL_LIBRARY_FILE AND OPENSSL_CRYPTO_FILE)
    target_link_libraries (${PROJECT_NAME} paho-mqttpp3 paho-mqtt3as ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARY_FILE} ${OPENSSL_CRYPTO_FILE})
else()
    target_link_libraries (${PROJECT_NAME} paho-mqttpp3 paho-mqtt3as ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY})
endif()
