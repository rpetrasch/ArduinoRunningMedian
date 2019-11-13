/**
 * Implementation for Running Median
 *
 * Running Median (for integer values) uses min and max heap.
 * Calculation of the effective / running median for an increasing number of values
 * using 2 heaps
 * a) max heap = left side for elements that are less than effective median
 * b) min heap = right side for elements that are greater than effective median
 * The number of elements in both heaps differ utmost by 1 element
 *
 * Complexity: O(n log(n)) for getting the median
 *
 * @see https://www.geeksforgeeks.org/median-of-stream-of-integers-running-integers/
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

#include "RunningMedian.h"
#include "HeapUtils.h"
#include "Heap.h"
#include "StringUtils.h"

/**
 * Constructor
 *
 * @param array_size size of the min and max heaps
 */
RunningMedian::RunningMedian(int array_size) :
        maxHeap(array_size, &greaterOrEqual),
        minHeap(array_size, &lessOrEqual) {
        median = FLOAT_MIN;
}

/**
  * Destructor
  * ToDo implement
  */
RunningMedian::~RunningMedian() {
//    delete &minHeap;
//    delete &maxHeap;
}

/**
 * Calculate the running media for the new element based on the existing elements
 * in the min and max heaps. It inserts the new element and heapify towards root
 * in order to get the updated median.
 *
 * @param element new element for effective median calculation
 * @return effective median or MIN_INT (heap size overflow)
 */
float RunningMedian::getMedian(int element) {
    // Check whether heaps are balanced. yes: sign will be 0
    int sign = signum(maxHeap.size(), minHeap.size());
    bool added = true; // check add (heap size): optimistic approach
    switch (sign) {
        case 1: // More elements in left (max) heap
            if (element < median) { // current element -> left (max) heap
                // Remove top element from left heap and add into right (min) heap
                added = minHeap.add(maxHeap.poll());
                // add the new element to the left (max) heap
                added &= maxHeap.add(element);
            } else {
                // current element -> right (min) heap
                added = minHeap.add(element);
            }
            // Both heaps are balanced -> calculate the mean
            median = mean(maxHeap.peek(), minHeap.peek());
            break;
        case 0: // Left and right heap contain same number of elements
            if (element < median) { // current element -> left (max) heap
                added = maxHeap.add(element); // add element to the left heap
                median = maxHeap.peek(); // get the root of the left heap
            } else {
                // current element -> right (min) heap
                added = minHeap.add(element); // add element to the right heap
                median = minHeap.peek(); // get the root of the right heap
            }
            break;
        case -1: // More elements in right (min) heap
            if (element < median) { // current element -> left (max) heap
                added = maxHeap.add(element); // add element to the left heap
            } else {
                // Remove top element from right heap and add to left heap
                added = maxHeap.add(minHeap.poll());
                added &= minHeap.add(element); // add element to the right heap
            }
            // Both heaps are balanced -> calculate the mean
            median = mean(maxHeap.peek(), minHeap.peek());
            break;
        default: ; // nothing to see here
    }
    if (added) return median;
    else return FLOAT_MIN;
}

/**
 * Calculate the running media  based on the existing elements in the min and max heaps.
 *
 * @return effective median or MIN_INT (heaps are empty)
 */
float RunningMedian::getMedian() {
    median = mean(maxHeap.peek(), minHeap.peek());
    return median;
}

/**
 * Delete an old element from one heap and add a new element to another heap.
 * Check whether the two heap sizes differ and try to balance it out.
 *
 * @param heapDelete heap with the old element to be deleted
 * @param heapAdd heap with the new element to be added
 * @param oldElement old element to be deleted
 * @param newElement new element to be added
 * @return true = done, false = failure
 */
bool deleteAddBalance(Heap &heapDelete, Heap &heapAdd, float oldElement, float newElement) {
    bool done = true;
    heapDelete.deleteLazy(oldElement); // lazily delete the old element
    heapAdd.add(newElement); // add new element to the heap
    // check number of elements: may differ by more than 1 -> need to balance out
    int sign = signum(heapDelete.size(), heapAdd.size());
    switch (sign) {
        case 1: // More elements in delete heap
            done = heapAdd.add(heapDelete.poll());
            break;
        case -1: // More elements in add heap
            done = heapDelete.add(heapAdd.poll());
            break;
        case 0: // both heap have the same number of elements
        default: ; // Nothing to see here
    }
    return done;
}

/**
 * Update an element and heapify. This is used when using a ring buffer for
 * sliding window median.
 *
 * @param element that is to be removed
 * @return true (removed) or false (element not found)
 */
bool RunningMedian::updateElement(int oldElement, float newElement) {
    bool updated = true;
    if (median > FLOAT_MIN) {
        if (oldElement < median) { // old element -> left (max) heap
            if (newElement < median) { // new element -> left (max) heap
                updated = maxHeap.findAndUpdateElement(oldElement, newElement);
            } else {
                deleteAddBalance(maxHeap, minHeap, oldElement, newElement);
            }
        } else { // old element -> right (min) heap
            if (newElement >= median) {
                updated = minHeap.findAndUpdateElement(oldElement, newElement);
            } else { // new element -> left (max) heap
                deleteAddBalance(minHeap, maxHeap, oldElement, newElement);
            }
        }
    } else {
        updated = false;
        // ToDo
    }
    return updated;
}

/**
  * Resets the heaps and median without freeing the memory
  */
void RunningMedian::reset() {
    minHeap.reset();
    maxHeap.reset();
    median = FLOAT_MIN;
}

/**
 * Converts the heaps and the median to a string
 * ToDo remove the casts
 *
 * @return heaps and median as a string
 */
char* RunningMedian::toString() {
    char* result;
    char buffer[30];
    result = stringConcat((char*)"Max Heap: ", getMaxHeap()->toString());
    result = stringConcat(result, (char*)"\nMin Heap: ");
    result = stringConcat(result, getMinHeap()->toString());
    result = stringConcat(result, (char*)"\nMedian: ");
    stringConcat(result, stringFormat(buffer, (const char*) "%d", median)); // std::to_string(median);
    return result;
}