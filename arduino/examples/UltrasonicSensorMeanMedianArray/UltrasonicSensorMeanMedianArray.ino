/**
 * Simple Test Program for Arduino: Calculated mean and median for smoothing
 * of a series of ultrasonic sensor values (buffer size is 50 and cycle delay is
 * 3 ms (milliseconds) + 11 ms for sensor value read + execution time for mean/median
 * calculation (ca. 35 ms) => time window (for running mean/median) is around 1.75 s
 *
 * @author Roland Petrasch, roland.petrasch@gmail.com
 * @copyright 2019 Roland Petrasch, Thailand
 * @version 1.0
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <string.h>

// Pin constants ------------------------------------------------------------
const int triggerPin = 2; // Trigger for US sensor
const int echoPin = 3;    // Echo for US sensor

// Loop configuration and globals vars --------------------------------------
const int delayMS        = 3;    // delay in ms between cycles of sensor read
const int serialBaudRate = 19200;
// Variables for duration of the ping and the distance result in centimeters:
const int sensorShortLowPulseDelay = 1;
const int sensorHighPulseDelay = 10;
float distance = 0;
// size of the ring buffer (used for mean/mean and median)
const int bufferSize   = 50;     // Should be an even number (see smoothWithMedian())
unsigned long time; // for time measurement

// Smoothing with mean variables -------------------------------------------
int distanceSmoothMean = 0;
int meanBuffer[bufferSize];      // meanBuffer from sensor (distance): ring buffer
int meanBufferIndex    = 0;      // index of the current reading
float totalForMean     = 0;      // running totalForMean (sum of sensor distance values)

// Smoothing with median variables ------------------------------------------
int distanceSmoothMedian = 0;
int rawDataSorted[bufferSize]; // Sorted list for Median
int medianBuffer[bufferSize];  // Ring buffer for Median
int medianBufferIndex    = 0;
int counterRunningMedian = 0;

// Relative Difference variables ----------------------------------------------
const bool doSmoothWithMean   = true;
const bool doSmoothWithMedian    = true;
// Used to draw the values below/above each other
const int smoothMeanLineDisplayOffset   = -5;
const int smoothMedianLineDisplayOffset = -10;

/**
 * Setup function
 **/
void setup() {
    // initialize serial communication
    Serial.begin(serialBaudRate);
    // Trigger is sent to the sensor and echo is received by the sensor
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.println(F("Start ---------------------------------------------------------"));
}

/**
 * Main loop function
 **/
void loop() {
    time = millis();
    // Read the sensor duration value (distance in cm)
    distance = getDistance();
    // Send the distance to the serial port
    printValue("Distance:", distance); // unit: cm

    if (doSmoothWithMean) {
        distanceSmoothMean = smoothWithMean();
        printValue("DistSmooth:", distanceSmoothMean + smoothMeanLineDisplayOffset);
    }
    if (doSmoothWithMedian) {
        distanceSmoothMedian = smoothWithMedian();
        printValue("DistSmoothMedian:", distanceSmoothMedian + smoothMedianLineDisplayOffset);
    }
    Serial.println();
    delay(delayMS);
    printValue("Duration:", millis() - time);
}

/**
 * Smoothing with mean (calculated from ring buffer):
 * The current value (distance) is used to calculate a new mean
 * that can be taken instead of the original distance value
 **/
int smoothWithMean() {
    // subtract the old reading (from the last cycle)
    totalForMean = totalForMean - meanBuffer[meanBufferIndex];
    meanBuffer[meanBufferIndex] = distance;
    totalForMean = totalForMean + distance;
    meanBufferIndex = meanBufferIndex + 1;
    if (meanBufferIndex >= bufferSize) {
        meanBufferIndex = 0;
    }
    return totalForMean / bufferSize;
}

/**
 * Smoothing with median (calculated from median ring buffer):
 * The current value (distance) is used to calculate a new median
 * that can be taken instead of the original distance value
 **/
int smoothWithMedian() {
    int oldDistance = medianBuffer[medianBufferIndex];
    medianBuffer[medianBufferIndex++] = distance;
    if (medianBufferIndex >= bufferSize) {
        medianBufferIndex = 0;
    }
    for (int i = 0; i < bufferSize; i++) {
        if (rawDataSorted[i] == oldDistance) {
            rawDataSorted[i] = distance; // exchange the old value with the new (current) one
            break;
        }
    }
    sort();
    int index = bufferSize/2;
    distanceSmoothMedian = (rawDataSorted[index-1]+rawDataSorted[index])/2;
    return distanceSmoothMedian;
}

/**
 * Simple print function for Serial.print with or without a label
 */
void printValue(String label, float value) {
    if(label != NULL) Serial.print(label);
    Serial.print(value);
    Serial.print(" ");
}

/**
 * Measures and returns the distance in cm
 */
float getDistance() {
    // Sensor is triggered by HIGH pulse of 10 or more ms
    // Short LOW pulse beforehand ensures clean HIGH pulse
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(sensorShortLowPulseDelay);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(sensorHighPulseDelay);
    digitalWrite(triggerPin, LOW);
    // Read signal from sensor and return the distance in cm
    return pulseIn(echoPin, HIGH) / 58; // 29 (speed of sound: 340 m/s or 29 microseconds/cm) * 2
}

/**
 * Bubblesort implementation: with O(n^2) it is not really good, but has a very compact
 * code size. Other algorithms like quicksort has O(n^2) in the worst case
 * and O(n log n) in the best case. Even Timsort needs O(n\log n) comparisions in the
 * worst case. For now, we use the simple Bubblesort. ToDo: use/implement faster algorithm here.
 */
void sort() {
    int temp;
    for(int i = 0; i < (bufferSize-1); i++) {
        for(int j = 0; j < (bufferSize-(i+1)); j++) {
            if(rawDataSorted[j] > rawDataSorted[j+1]) {
                temp = rawDataSorted[j];
                rawDataSorted[j] = rawDataSorted[j+1];
                rawDataSorted[j+1] = temp;
            }
        }
    }
}