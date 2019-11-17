/**
 * Test Program for the Running Median (for integer values)
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

#include <iostream>
#include "Heap.h"
#include "RunningMedian.h"

using namespace std;

/**
 * Print heap elements on the screen.
 * This works non-destructively: Backing array elements are shown
 *
 * @param heap heap objects
 * @param name of the heap
 */
void printHeapArray(Heap *heap, const string &name) {
    float *array = heap->getHeapArray();
    cout << name;
    for (int i = 0; i <= heap->getHeapCurrentIndex(); i++) {
        float key = array[i];
        cout << " " << key;
    }
    cout << endl;
}

/**
 * Print heap elements on the screen.
 * This works destructively: poll() is called until no more elements in the heap
 *
 * @param heap heap objects
 * @param name of the heap
 */
void printHeapPoll(Heap *heap, const string name) {
    cout << name;
    while (true) {
        float key = heap->poll();
        if (key <= FLOAT_MIN) break;
        cout << " " << key;
    }
    cout << endl;
}

/**
 * Print all elements of the heap, the element (value) and the median
 *
 * @param values array with integer values
 * @param size of the array
 * @param runningMedian object for calc the running median based on the elements of the array
 */
void printSingleHeapMedian(int value, float median, RunningMedian &runningMedian, float counter) {
    cout << "--------------------------------------- " << counter << endl;
    printHeapArray(runningMedian.getMaxHeap(), "Max heap array: ");
    printHeapArray(runningMedian.getMinHeap(), "Min heap array: ");
    cout << "Element: " << value << "\tMedian: " << median << endl;
}


/**
 * Get th median for all elements (and adding them to the heaps) and
 * print the element and the median
 *
 * @param values array with integer values
 * @param size of the array
 * @param runningMedian object for calc the running median based on the elements of the array
 */
void printAllHeapMedian(float *values, float size, RunningMedian &runningMedian) {
    float median = 0;
    for (int i = 0; i < size; i++) {
        median = runningMedian.getMedian(values[i]);
        printSingleHeapMedian(values[i], median, runningMedian, i);
        if (median <= FLOAT_MIN) {
            cout << "Heap size overflow." << endl;
            break;
        }

    }
}


/**
 * Main test program
 * Contains 4 test cases for using the running median / sliding median
 */
int main() {
    if (true) {
        Heap maxHeap(10, &greaterOrEqual);
        Heap minHeap(10, &lessOrEqual);

        cout << "---------------------------------------------------------------" << endl;
        cout << "Test 0: heap test" << endl;
        maxHeap.add(1);
        maxHeap.add(1);
        maxHeap.add(2);
        maxHeap.add(1);
        maxHeap.add(3);
        maxHeap.add(1);
        maxHeap.add(2);
        maxHeap.add(4);

        cout << maxHeap.poll() << endl;
        cout << maxHeap.poll() << endl;
        cout << maxHeap.poll() << endl;
        cout << maxHeap.poll() << endl;
        cout << maxHeap.poll() << endl;
        cout << maxHeap.poll() << endl;
        cout << maxHeap.poll() << endl;
        cout << maxHeap.poll() << endl;
        cout << maxHeap.poll() << endl;


        minHeap.add(2);
        minHeap.add(2);
        minHeap.add(2);
        minHeap.add(2);
        minHeap.add(3);
        minHeap.add(4);
        minHeap.add(2);
        minHeap.add(1);

        cout << minHeap.poll() << endl;
        cout << minHeap.poll() << endl;
        cout << minHeap.poll() << endl;
        cout << minHeap.poll() << endl;
        cout << minHeap.poll() << endl;
        cout << minHeap.poll() << endl;
        cout << minHeap.poll() << endl;
        cout << minHeap.poll() << endl;
        cout << minHeap.poll() << endl;

    }
    if (false) {
        Heap minHeap(100, &lessOrEqual);
        minHeap.add(167 ); minHeap.add(167 ); minHeap.add(36 ); minHeap.add(26 ); minHeap.add(33 ); minHeap.add(30 );
        minHeap.add(30 ); minHeap.add(25 );
        minHeap.add(24 );
        minHeap.add(28 ); minHeap.add(30 ); minHeap.add(27 );
        minHeap.add(28 ); minHeap.add(26 ); minHeap.add(26 ); minHeap.add(25 ); minHeap.add(25 );
        minHeap.add(23);
        // printHeapArray(&minHeap, "heap: ");
        printHeapPoll(&minHeap, "heap: ");;

    }

    if (false) {
        cout << "---------------------------------------------------------------" << endl;
        cout << "Test 1: heap size 2 / 6 elements -> heap overflow" << endl;
        float values[] = {1, 2, 3, 4, 5, 6}; // 6 elements
        int size = ARRAY_SIZE(values);
        RunningMedian runningMedian(2); // 2 heaps -> capacity for 4 elements
        printAllHeapMedian(values, size, runningMedian);
        cout << "---" << endl;
        printHeapPoll(runningMedian.getMaxHeap(), "Max heap");
        printHeapPoll(runningMedian.getMinHeap(), "Min heap");
    }

    if (false) {
        cout << "---------------------------------------------------------------" << endl;
        cout << "Test 2: heap size OK and 2 outliers" << endl;
        float values[] = {5, 15, 1, 3, 2, 8, 7, 1000, 9, 10, 6, 11, 4, -88, 2};
        float size = ARRAY_SIZE(values);
        RunningMedian runningMedian(8);
        printAllHeapMedian(values, size, runningMedian);
        cout << "---" << endl;
        printHeapPoll(runningMedian.getMaxHeap(), "Max heap");
        printHeapPoll(runningMedian.getMinHeap(), "Min heap");
    }
    if (false) {
        cout << "---------------------------------------------------------------" << endl;
        cout << "Test 3: Duplicates" << endl;
        float values[] = {1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 11, 4, -88, 1}; // 15 elements
        float size = ARRAY_SIZE(values);
        RunningMedian runningMedian(8);
        printAllHeapMedian(values, size, runningMedian);
        cout << "---" << endl;
        printHeapPoll(runningMedian.getMaxHeap(), "Max heap");
        printHeapPoll(runningMedian.getMinHeap(), "Min heap");
    }
    if (true) {
        cout << "---------------------------------------------------------------" << endl;
        cout << "Test 4: Ring Buffer -> update values" << endl;
        float values[] = {1, 4, 6, 8, 2, 3}; // 6 elements
        float size = ARRAY_SIZE(values);
        RunningMedian runningMedian(6);
        printAllHeapMedian(values, size, runningMedian);

        bool updated = runningMedian.updateElement(1, 2);
        if (updated) {
            float median = runningMedian.getMedian();
            cout << "---------------------------------------" << endl;
            cout << "Element updated: " << "1 -> 2" << "\tMedian: " << median << endl;
            printSingleHeapMedian(2, median, runningMedian, 1);
        }
        updated = runningMedian.updateElement(4, 5);
        if (updated) {
            float median = runningMedian.getMedian();
            cout << "---------------------------------------" << endl;
            cout << "Element updated: " << "4 -> 5" << "\tMedian: " << median << endl;
            printSingleHeapMedian(5, median, runningMedian, 2);
        }
        cout << "---" << endl;
        cout << "toString: \n" << runningMedian.toString() << endl;
        cout << "---" << endl;
        printHeapPoll(runningMedian.getMaxHeap(), "Max heap");
        printHeapPoll(runningMedian.getMinHeap(), "Min heap");
    }
    if (false) {
        cout << "---------------------------------------------------------------" << endl;
        cout << "Test 5: Reset" << endl;
        float values[] = {1, 2, 3, 4}; // 4 elements
        float size = ARRAY_SIZE(values);
        RunningMedian runningMedian(8);
        printAllHeapMedian(values, size, runningMedian);
        runningMedian.reset();
        float median = runningMedian.getMedian();
        cout << "After reset: median: " << median << endl;
        cout << "---" << endl;
        cout << "toString: \n" << runningMedian.toString() << endl;
        cout << "---" << endl;
        printHeapPoll(runningMedian.getMaxHeap(), "Max heap");
        printHeapPoll(runningMedian.getMinHeap(), "Min heap");
    }
    if (false) {
        cout << "Test 5: Arduino Data" << endl;
        float values[] = {59, 59, 58, 59, 60, 59, 60, 60, 167, 168, 169, 168, 168, 62, 61, 168, 62, 167, 168, 168, 168,
                          60, 59, 61, 61, 60, 57, 59, 58, 58, 58, 57, 58, 58, 58, 57, 56, 54, 55, 56, 54, 52};
        float size = ARRAY_SIZE(values);
        RunningMedian runningMedian(30);
        printAllHeapMedian(values, size, runningMedian);
        cout << "*** Resetting the running median" << endl;
        runningMedian.reset();
        for (int i = 0; i < size; i++) {
            float median = runningMedian.getMedian(values[i]);
            cout << median << ", ";
        }
        cout << endl;
        runningMedian.reset();
        for (int i = 0; i < size; i++) {
            float median = runningMedian.getMedian(values[i]);
            cout << median << ", ";
        }
        cout << endl;
    }
    if (false) {
        cout << "Test 6: Static heap size" << endl;
        float values[] = {168, 167, 167, 167, 168, 167, 167, 168, 167, 167, 167, 168, 168, 168, 168, 167, 167, 168, 36,
                          33, 30, 30, 30, 27, 168, 168, 28, 26, 28, 26, 26, 25, 25, 25, 24, 23, 25, 27, 23, 23, 23, 24, 168, 167, 167, 167, 167, 168};
        float size = ARRAY_SIZE(values);
        RunningMedian runningMedian(size);
        printAllHeapMedian(values, size, runningMedian);
        cout << "*** Resetting the running median" << endl;
        runningMedian.reset();
        for (int i = 0; i < size; i++) {
            float median = runningMedian.getMedian(values[i]);
            cout << median << ", ";
        }
        cout << "*** End" << endl;
    }
    return 0;
}
