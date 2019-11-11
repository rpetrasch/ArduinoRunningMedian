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
void printHeapArray(Heap *heap, const string& name) {
    int * array = heap->getHeapArray();
    cout << name;
    for (int i=0; i <= heap->getHeapCurrentIndex(); i++) {
        int key = array[i];
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
void printHeapPoll(Heap *heap, string name) {
    cout << name;
    while(true) {
        int key = heap->poll();
        if (key == NOT_DEFINED) break;
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
void printHeapAndMedian(int value, float median, RunningMedian &runningMedian) {
    cout << "---------------------------------------" << endl;
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
void printMedian(int values[], int size, RunningMedian &runningMedian) {
    float median = 0;
    for(int i = 0; i < size; i++) {
        median = runningMedian.getMedian(values[i]);
        printHeapAndMedian(values[i], median, runningMedian);
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
int main()
{
    {
        cout << "---------------------------------------------------------------" << endl;
        cout << "Test 1: heap size 2 / 6 elements -> heap overflow" << endl;
        int values[] = {1, 2, 3, 4, 5, 6}; // 6 elements
        int size = ARRAY_SIZE(values);
        RunningMedian runningMedian(2); // 2 heaps -> capacity for 4 elements
        printMedian(values, size, runningMedian);
        cout << "---" << endl;
        printHeapPoll(runningMedian.getMaxHeap(), "Max heap");
        printHeapPoll(runningMedian.getMinHeap(), "Min heap");
    }

    {
        cout << "---------------------------------------------------------------" << endl;
        cout << "Test 2: heap size OK and 2 outliers" << endl;
        int values[] = {5, 15, 1, 3, 2, 8, 100, 7, 9, 10, 6, 11, 4, -88, 1};
        int size = ARRAY_SIZE(values);
        RunningMedian runningMedian(8);
        printMedian(values, size, runningMedian);
        cout << "---" << endl;
        printHeapPoll(runningMedian.getMaxHeap(), "Max heap");
        printHeapPoll(runningMedian.getMinHeap(), "Min heap");
    }

    {
        cout << "---------------------------------------------------------------" << endl;
        cout << "Test 3: Duplicates" << endl;
        int values[] = {1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 11, 4, -88, 1}; // 15 elements
        int size = ARRAY_SIZE(values);
        RunningMedian runningMedian(8);
        printMedian(values, size, runningMedian);
        cout << "---" << endl;
        printHeapPoll(runningMedian.getMaxHeap(), "Max heap");
        printHeapPoll(runningMedian.getMinHeap(), "Min heap");
    }
    {
        cout << "---------------------------------------------------------------" << endl;
        cout << "Test 4: Ring Buffer -> update values" << endl;
        int values[] = {1, 4, 6, 8}; // 4 elements
        int size = ARRAY_SIZE(values);
        RunningMedian runningMedian(8);
        printMedian(values, size, runningMedian);

        bool updated = runningMedian.updateElement(1, 2);
        if (updated) {
            float median = runningMedian.getMedian();
            cout << "---------------------------------------" << endl;
            cout << "Element updated: " << "1 -> 2" << "\tMedian: " << median  << endl;
            printHeapAndMedian(2, median, runningMedian);
        }
        updated = runningMedian.updateElement(4, 5);
        if (updated) {
            float median = runningMedian.getMedian();
            cout << "---------------------------------------" << endl;
            cout << "Element updated: " << "4 -> 5" << "\tMedian: " << median  << endl;
            printHeapAndMedian(5, median, runningMedian);
        }
        cout << "---" << endl;
        printHeapPoll(runningMedian.getMaxHeap(), "Max heap");
        printHeapPoll(runningMedian.getMinHeap(), "Min heap");
    }
    return 0;
}
