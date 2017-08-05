#!/bin/sh
DIR="$( cd "$( dirname "$0" )" && pwd )"

echo "Installs dependancies.."
apt-get install build-essential gcc make cmake cmake-gui cmake-curses-gui libssl-dev doxygen graphviz

echo "Pulling Paho.MQTT.c.."
sudo mkdir $DIR/build-deps/
cd $DIR/build-deps/
git clone https://github.com/eclipse/paho.mqtt.c

echo "Building Paho.MQTT.c.."
cd $DIR/build-deps/paho.mqtt.c/
cmake -DPAHO_WITH_SSL=TRUE -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_STATIC=TRUE -DPAHO_BUILD_SHARED=FALSE
make

echo "Pulling Paho.MQTT.cpp.."
sudo mkdir $DIR/build-deps/
cd $DIR/build-deps/
git clone https://github.com/eclipse/paho.mqtt.cpp

echo "Building Paho.MQTT.cpp.."
cd $DIR/build-deps/paho.mqtt.cpp/
cmake -DPAHO_WITH_SSL=TRUE -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_STATIC=TRUE -DPAHO_BUILD_SHARED=FALSE -DPAHO_MQTT_C_PATH=../paho.mqtt.c/ -DPAHO_MQTT_C_LIB=../paho.mqtt.c/src/libpaho.mqtt3as-static.a
make 

echo "Copying built libs to $DIR/ext/lib/"
cp $DIR/build-deps/paho.mqtt.c/src/libpaho-mqtt3as-static.a $DIR/ext/lib/libpaho-mqtt3as.a
cp $DIR/build-deps/paho.mqtt.cpp/src/libpaho-mqttpp3.a $DIR/ext/lib/libpaho-mqttpp3.a

rm -r $DIR/build-deps
