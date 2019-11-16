/**
 * Heap (for integer keys=values) backed by an integer array.
 * This heap implementation is a priority queue: min or max heap = complete binary tree data structure
 * with "priority" (min or max value as root depending on the comparator)
 * a) max heap: key (value) of a parent is greater than or equal to the key of its child
      Example: Heap(new int[MAX_HEAP_SIZE], &greaterOrEqual)
 * b) min heap: key (value) of a parent is less than or equal to the key of its child
 *    Example: Heap(new int[MAX_HEAP_SIZE], &lessOrEqual)
 *
 * Complexity: O(log n) for insert and delete
 *
 * @see Java Priority Queue: https://docs.oracle.com/javase/7/docs/api/java/util/PriorityQueue.html
 * @see Min-max heap https://en.wikipedia.org/wiki/Min-max_heap

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

// #include <string> // Arduino does not support string
#include <string.h>
#include <stdlib.h>
#include "HeapUtils.h"

#ifndef RUNNINGMEDIAN_HEAP_H
#define RUNNINGMEDIAN_HEAP_H

// Heap capacity
#define DEFAULT_MAX_HEAP_SIZE (128)
#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

// Integer max and min, cannot use bits/stdc++.h or limits.h (Arduino)
#define INT_MAX (2147483647)
#define INT_MIN (2147483648)
#define FLOAT_MAX  (3.40282e38f)
#define FLOAT_MIN (-3.40282e38f)

class Heap {

public:
    /**
     * Constructor
     * Initializes heap array and assigns the comparator required in heapification
     *
     * @param heapArraySize size of the array that backs the tree
     * @param comparatorFunction pointer to a comparator function (greater, smaller) for min or max heap
     */
    Heap(int heapArraySize, bool (*comparatorFunction)(float, float));

    /**
     * Constructor
     * Initializes heap array with the DEFAULT_HEAP_SIZE and assigns the comparator required in heapification
     *
     * @param comparatorFunction pointer to a comparator function (greater, smaller) for min or max heap
     */
    explicit Heap(bool (*comparatorFunction)(float, float));

    /**
     * Destructor
     */
    ~Heap();

    /**
     * Add a key = element to the heap
     *
     * @param key new heap element
     * @return true (success) or false (failure)
     */
    bool add(int key);

    /**
     * Get = retrieve the root of the tree = element with highest "priority" = lowest or highest value
     * If there is no root element FLOAT_MIN is returned
     *
     * @return the top / root element: the lowest value for min heap, the largest value for max heap
     */
    float peek();

    /**
     * Take the root of the tree: retrieve and removes the element
     * If there is no root element FLOAT_MIN is returned
     *
     * @return the top / root element: the lowest value for min heap, the largest value for max heap
     */
    float poll();

    /**
     * Returns the number of elements in the help
     *
     * @return number of elements in the help or -1 is the heap is empty
     */
    int size();

    /**
     * Find an element by its key / value and update (replace) it with the new value
     *
     * @param oldElement to be found and updated in the heap
     * @param newElement to be used for the update
     * @return true (updated) or false (not found)
     */
    bool findAndUpdateElement(float oldElement, float newElement);

    /**
     * Delete an element by its key / value (lazy delete)
     *
     * @param element to be deleted
     * @return true (deleted) or false (not found)
     */
    bool deleteLazy(float element);

    /**
     * Resets the heap without freeing the memory
     */
    void reset();

    /**
      * Getter methods for test purposes only. Do not use in order to change the
      * array "outside" the Heap context. ToDo Delete this for production use.
      *
      * @return array / current index
      */
    float * getHeapArray() { return heapArray;}
    float getHeapCurrentIndex() { return heapCurrentIndex;}

    /**
     * Converts the heap array to a string
     * @return heap array as a string
     */
    // std::string toString(); // Arduino does not support string
    char *toString();

protected:
    // Array that backs the heap
    // Contains the keys = objects/elements of the tree (in this case: float values)
    float *heapArray;
    // Comparator: see HeapUtils (greaterOrEqual, lessOrEqual)
    // Used for min and max heap
    bool  (*comparator)(float a, float b);
    // current heap array index starts with 0,
    // i.e. heapCurrentIndex + 1 must always less than maxHeapSize
    int heapCurrentIndex;
    // index of the last inserted element
    int lastInsertedIndex = NOT_DEFINED;
    // Max heap size = capacity (number of elements)
    int maxHeapSize;

    /**
     * Get the parent key (element value) of the element with the index
     *
     * @param index of the element
     * @return parent value of the element
     */
    int parent(int index);

    /**
     * (Re-)Create the heap from the element with the index towards the root
     * = converting a binary tree into a heap (complete, and parent of a node is more "extreme"
     * than the node)
     * ToDo Optimize
     *
     * @param index of the element
     */
    void heapify(int index);

    /**
     * (Re-)Create the heap from the leaf element(s) towards the root
     * = converting a binary tree into a heap (complete, and parent of a node is more "extreme"
     * than the node)
     *
     * @param index of the element
     */
    void heapifyUp();

    /**
     * (Re-)Create the heap starting from the root
     */
    void heapifyDown();

    /**
     * Find an element by its key / value and return the index (in the heap array)
     *
     * @param element to be found in the heap
     * @return index of the element in the heap array
     */
    int find(float element);

    /**
     * Check for lazily deleted root and poll (remove) recursively
     */
    void checkDeletedRoot();

    /**
     * Retrieve the left child element
    *
    * @param index of the parent element
    * @return ket (value) of left child.
    **/
    int leftChild(int index);

    /**
    * Retrieve the right child element
    *
    * @param index of the parent element
    * @return ket (value) of right child.
    **/
    int rightChild(int index);

    /** Check whether a left child exists
     *
     * @param index of the element to be checked
     * @return true = left child, false = no left child
     **/
    bool hasLeftChild(int index);

    /** Check whether a right child exists
     *
     * @param index of the element to be checked
     * @return true = right child, false = no right child
     **/
    bool hasRightChild(int index);
};

#endif //RUNNINGMEDIAN_HEAP_H
