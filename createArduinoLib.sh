#!/bin/sh
cp ./src/Heap* arduino
cp ./src/RunningMedian* arduino
cp ./src/StringUtils.h arduino
cd ./arduino
zip -r ArduinoRunningMedian ./*
mv ArduinoRunningMedian.zip ../
cd ../


