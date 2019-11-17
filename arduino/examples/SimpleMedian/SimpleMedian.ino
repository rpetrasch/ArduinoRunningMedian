/**
 * Simple Heap Test Program for ArduinoRunningMedian Lib
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
 
#include <HeapUtils.h>
#include <Heap.h>
#include <RunningMedian.h>

// Create a running median object that manages a min and max heap for median calculation
RunningMedian runningMedian(100);

// string for formatted output
char outputString[100];
float values[] = {5, 15, 1, 3, 2, 8, 7, 100, 9, 10, 6, 11, 4, -88, 2};
int size = ARRAY_SIZE(values);

/**
 * Setup
 * creates an array and sends values and median via serial channel
 */
void setup() {

  // Initialize Serial port
  Serial.begin(19200);
  Serial.println();
  Serial.println("--------------------------------");
  Serial.println("Running Median - Test");
  Serial.println("--------------------------------");
  printMedian(values, size);
  
}

/**
 * Main Loop
 * nothing to see here
 */
void loop() {
//  Serial.println("Reset the object and add elements again");
//  runningMedian.reset();
//  printMedian(values, size);
//  delay(1000);
}

/**
 * Sends the array elements with the median values to the serial channel
 */
void printMedian(float values[], int size) {
    float median = 0; // variable for effective median
    for(int i = 0; i < size; i++) {
        median = runningMedian.getMedian(values[i]);
        // sprintf(outputString, "Element: %f \t Median: %f", values[i], median);
        // Serial.println(outputString);
        Serial.print(values[i]);Serial.print(" \t ");Serial.print(median);
        Serial.println();
    }
    delete &runningMedian;
}
