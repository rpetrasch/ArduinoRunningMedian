#!/bin/sh
cp ./src/* arduino
cd ./arduino
rm ./main.cpp
zip ArduinoRunningMedian ./*
mv ArduinoRunningMedian.zip ../
cd ../


