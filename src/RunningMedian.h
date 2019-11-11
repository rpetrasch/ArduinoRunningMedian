/**
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

#ifndef RUNNINGMEDIAN_H
#define RUNNINGMEDIAN_H

#include "Heap.h"

class RunningMedian {
public:
    /**
     * Constructor
     *
     * @param array_size size of the min and max heaps
     */
    explicit RunningMedian(int array_size);

    /**
      * Destructor
      */
    ~RunningMedian();

    /**
     * Calculate the running media for the new element based on the existing elements
     * in the min and max heaps. It inserts the new element and heapify towards root
     * in order to get the updated median.
     *
     * @param element new element for effective median calculation
     * @return effective median or MIN_INT (heap size overflow)
     */
    float getMedian(int element);

    /**
     * Calculate the running media  based on the existing elements in the min and max heaps.
     *
     * @return effective median or MIN_INT (heaps are empty)
     */
    float getMedian();

    /**
     * Update an element and heapify. This is used when using a ring buffer for
     * sliding window median.
     *
     * @param element that is to be removed
     * @return true (removed) or false (element not found)
     */
    bool updateElement(int oldElement, int newElement);

    /**
     * Getter methods for test purposes only. Do not use in order to change the
     * heaps "outside" the RunningMedian context. ToDo Delete this for production use.
     *
     * @return heap objects
     */
    Heap * getMaxHeap() { return &maxHeap; }
    Heap * getMinHeap() { return &minHeap; }

private:
    Heap maxHeap; // left (max) heap
    Heap minHeap; // right (min) heap
    float median;   // effective median
};

#endif //RUNNINGMEDIAN_H
