/**
 * Test Program for Arduino using the RunningMedian Library
 * Mean and median are calculated and used for smoothing a series of ultrasonic
 * sensor values (buffer size is 50 and cycle delay is 3 ms (milliseconds)
 * + 11 ms for sensor value read + execution time for mean/median
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

#include <RunningMedian.h>

// Pin constants ------------------------------------------------------------
const int triggerPin = 2; // Trigger for US sensor
const int echoPin = 3;    // Echo for US sensor

// Loop configuration and globals vars --------------------------------------
const int delayMS        = 3;    // delay in ms between cycles of sensor read
const int serialBaudRate = 19200;
// Variables for duration of the ping and the distance result in centimeters:
const int sensorShortLowPulseDelay = 1;
const int sensorHighPulseDelay = 10;
// long  duration = 0;
float distance = 0, distanceDelta = 0, distanceDeltaOld = 0, distanceSmooth = 0, distanceSmoothMedian = 0, distanceSkip = 0, distanceOld  = 0, distancePreserved = 0, relDiff = 0;

// Smooth with average variables ----------------------------------------------
const int numReadings = 50;     // size of the ring buffer
int readings[numReadings];      // readings from sensor (distance): ring buffer
int readIndex         = 0;      // index of the current reading
float total           = 0;      // running total (sum of sensor distance values)
float average         = 0;      // average of sensor distance

// Skip outliers with simple delta --------------------------------------------
const float simpleDeltaThreshold = 40; // 40 cm delta
// Skip outliers with average variable ----------------------------------------
const float averageTheshold = 0.15; // threshold for skip the distance, e.g. 10%
// Skip outliers above rel. diff. threshold -----------------------------------
const float relDifferenceThreshold = 1.0;
// Median
RunningMedian runningMedian(numReadings);
int counterRunningMedian = 0;

// Relative Difference variables ----------------------------------------------
const bool doSmoothWithSimpleDelta = false;
const bool doSmoothWithAverage   = true;
const bool doSmoothWithMedian    = true;
const bool doSmoothWithMAD       = false;
const bool doSkipWithAverage     = false;
const bool doRelDiff             = false;
const bool showRelDiff           = false;
const bool showRelDiffDelta      = false;
// Used to draw the values below/above each other
const int relDistanceDeltaDisplayOffset   =  -5;
const int relDistanceSmoothDisplayOffset  = -10; 
const int relDistanceSkipDisplayOffset    = -15;
const int relDistanceRelDiffDisplayOffset = -20;
const int relDistanceSmoothMedianDisplayOffset = -20;

/**
 * Setup function 
 **/
void setup() {
  // initialize serial communication
  Serial.begin(serialBaudRate);
  // Trigger is sent to the sensor and echo is received by the sensor
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // Initialize the Ring buffer for relative difference
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
     // readings[thisReading] = 0;
     distance = getDistance();
     updateAverage();
  }

  // Intialize old distance value for rel. difference
  // duration = readSensor(); 
  // convert duration (time) into a distance
  // distance = microsecondsToCentimeters(duration);
  distance = getDistance();
  distanceOld = distance;
  distanceDeltaOld = distance;

  Serial.println("Start ---------------------------------------------------------");
}

/**
 * Main loop function
 **/
void loop() {
  // Read the sensor duration value (time)
  // duration = readSensor(); 
  // Convert duration (time) into a distance
  // distance = microsecondsToCentimeters(duration);
  distance = getDistance();
  // if (distance  > 500) distance = 500; 


  // Send the distance to the serial port
  printValue("Distance:", distance); // unit: cm

  if (doSmoothWithSimpleDelta ) {
    distanceDelta = smoothWithSimpleDelta();
    printValue("DistSimpleDelta:", distanceDelta + relDistanceDeltaDisplayOffset);
  }
  if (doSmoothWithAverage) {
    distanceSmooth = smoothWithAverage();
    printValue("DistSmooth:", distanceSmooth + relDistanceSmoothDisplayOffset);
  }
  if (doSmoothWithMedian) {
    if (counterRunningMedian+1 >= numReadings){
       printValue("Reset:", 100);
       runningMedian.reset();
       counterRunningMedian = 0;
    } else {
       printValue("Reset:", 10);
    }
    distanceSmoothMedian = runningMedian.getMedian(distance);
    printValue("DistSmoothMedian:", distanceSmoothMedian + relDistanceSmoothMedianDisplayOffset);
    counterRunningMedian++;
  }
  if (doSkipWithAverage) {
    distanceSkip = skipWithAverage();
    printValue("DistSkip:", distanceSkip + relDistanceSkipDisplayOffset);
    
  }
  if (doRelDiff) {
    relDiff = calcRelativeDifference();
    if (relDiff > 10.0) relDiff = 10.0; // Just limit the values for better plot (>1000%)
    if (showRelDiff) {
      printValue("RelDiff:", relDiff);
    }
    if (relDiff <= relDifferenceThreshold) {
      printValue("RelDiffCorr:", 0);
    } else {
      printValue("RelDiffCorr:", 40);
      distancePreserved = distance;
    }
    printValue("Distance(relDiff):", distancePreserved + relDistanceRelDiffDisplayOffset);
  }
  Serial.println();
  delay(delayMS);
}

/**
 * Smoothing with simple delta
 **/
long smoothWithSimpleDelta() {
  float delta = abs(distanceOld-distance);
  if (delta > simpleDeltaThreshold) {
     return distanceDeltaOld;
  } else {
    distanceDeltaOld = distance;
    return distance;
  }
}

/**
 * Smoothing with average (calculated from ring buffer):
 * The current value (distance) is used to calculate a new average
 * that can be taken instead of the original distance value
 **/
long smoothWithAverage() {
  updateAverage();
  return average;
}

/**
 * Smoothing with skipping logic
 * The average (mean) is used, relative (percentage) delta is calculated
 **/
long skipWithAverage() {
  float relativeChange = abs(distance - average)/average;
  printValue("DistSkip(relChange):", relativeChange);
  if (relativeChange > averageTheshold && total != 0) { 
    printValue("DistSkip(bool):", 50);
    return average;
  }
  printValue("DistSkip(bool):", 0);
  updateAverage();
  return average;
}

/**
 * Calculation of the mean (average)
 */
void updateAverage() {
  // subtract the old reading (from the last cycle)
  total = total - readings[readIndex];
  readings[readIndex] = distance;
  total = total + distance;
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings;
}

/**
 * Calculate the relative difference
 * https://en.wikipedia.org/wiki/Relative_change_and_difference
 */ 
float calcRelativeDifference() {
  float deltaAbsolute = abs(distanceOld-distance);
  // long scale = max(abs(distanceOld), abs(distance));
  // float scale = min(abs(distanceOld), abs(distance));
  float scale = abs(distanceOld);
  if (showRelDiffDelta) {
    printValue("RelDiffDelta:",deltaAbsolute); printValue("Scale:",scale);
  }
  float relativeDifference = deltaAbsolute/scale;
/* scale the absolute difference
  max(|x|, |y|),
  max(x, y),
  min(|x|, |y|),
  min (x, y),
  (x + y)/2
  (|x| + |y|)/2.
*/
  distanceOld = distance;
  return relativeDifference;
}


/**
 * Simple print function for Serial.print with or without label
 */
void printValue(String label, float value) {
   if(label != NULL) Serial.print(label);
   Serial.print(value);
   Serial.print(" ");   
}

/**
 * Read the sensor and return the duration for the ping (sound)
 */
float readSensor() {
  // Sensor is triggered by HIGH pulse of 10 or more ms
  // Short LOW pulse beforehand ensures clean HIGH pulse
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Read signal from sensor and return the duration
  return pulseIn(echoPin, HIGH);
}

int microsecondsToCentimeters(long microseconds) {
  // Speed of sound is 340 m/s or 29 microseconds per centimeter.
  // Ping travels out and back => take half of the distance travelled.
  return microseconds / 29 / 2;
}

/**
 * Return the distance in cm 
 * save one function call, see microsecondsToCentimeters
 */
float getDistance() {
  // Sensor is triggered by HIGH pulse of 10 or more ms
  // Short LOW pulse beforehand ensures clean HIGH pulse
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(sensorShortLowPulseDelay);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(sensorHighPulseDelay);
  digitalWrite(triggerPin, LOW);

  // Read signal from sensor and return the duration
  // return pulseIn(echoPin, HIGH);
  
  // Return the distance in cm (save one function call, see microsecondsToCentimeters)
  return pulseIn(echoPin, HIGH) / 58;
}
