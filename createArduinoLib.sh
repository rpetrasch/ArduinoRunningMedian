#!/bin/sh
cp ./src/* arduino
cd ./arduino
rm ./main.cpp
zip -r ArduinoRunningMedian ./*
mv ArduinoRunningMedian.zip ../
cd ../


