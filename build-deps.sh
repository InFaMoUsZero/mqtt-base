#!/bin/sh
PROJECT_DIR="$( cd "$( dirname "$0" )" && pwd )"
BUILD_DEPS_DIR="$PROJECT_DIR/build-deps/"
LIB_DIR="$PROJECT_DIR/ext/lib"

if [ ! -d "$BUILD_DEPS_DIR" ]; then
sudo mkdir $PROJECT_DIR/build-deps/
fi

# Create lib folder if doesn't exist
if [ ! -d "$LIB_DIR" ]; then
  mkdir $PROJECT_DIR/ext/lib
fi

## Install dependences required for this project
echo "Installs dependancies.."
apt-get install build-essential gcc make cmake cmake-gui cmake-curses-gui libssl-dev doxygen graphviz

# Pull PAHO.MQTT.C from github
echo "Pulling Paho.MQTT.c.."
cd $PROJECT_DIR/build-deps/
git clone https://github.com/eclipse/paho.mqtt.c

# Build PAHO.MQTT.C as a static lib
echo "Building Paho.MQTT.c.."
cd $PROJECT_DIR/build-deps/paho.mqtt.c/
cmake -DPAHO_WITH_SSL=TRUE -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_STATIC=TRUE -DPAHO_BUILD_SHARED=FALSE
make

# Pull PAHO.MQTT.CPP from github
echo "Pulling Paho.MQTT.cpp.."
cd $PROJECT_DIR/build-deps/
git clone https://github.com/eclipse/paho.mqtt.cpp

# Build PAHO.MQTT.CPP as a static lib
echo "Building Paho.MQTT.cpp.."
cd $PROJECT_DIR/build-deps/paho.mqtt.cpp/
cmake -DPAHO_WITH_SSL=TRUE -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_STATIC=TRUE -DPAHO_BUILD_SHARED=FALSE \
       -DPAHO_MQTT_C_PATH=../paho.mqtt.c/ -DPAHO_MQTT_C_LIB=../paho.mqtt.c/src/libpaho.mqtt3as-static.a
make 

echo "Copying built libs to $PROJECT_DIR/ext/lib/"
cp $PROJECT_DIR/build-deps/paho.mqtt.c/src/libpaho-mqtt3as-static.a $PROJECT_DIR/ext/lib/libpaho-mqtt3as.a
cp $PROJECT_DIR/build-deps/paho.mqtt.cpp/src/libpaho-mqttpp3.a $PROJECT_DIR/ext/lib/libpaho-mqttpp3.a

rm -r $PROJECT_DIR/build-deps
