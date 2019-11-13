/**
 * Implementation for the Heap
 *
 * Heap (for integer keys=values) backed by an integer array.
 * This heap implementation is a priority queue: min or max heap = complete binary tree data structure
 * with "priority" (min or max value as root depending on the comparator)
 * a) max heap: key (value) of a parent is greater than or equal to the key of its child
      Example: Heap(new int[MAX_HEAP_SIZE], &greaterOrEqual)
 * b) min heap: key (value) of a parent is less than or equal to the key of its child
 *    Example: Heap(new int[MAX_HEAP_SIZE], &lessOrEqual)
 *
 * Complexity: O(log(n)) for insert and delete
 *
 * @see Java Priority Queue: https://docs.oracle.com/javase/7/docs/api/java/util/PriorityQueue.html
 * @see Min-max heap https://en.wikipedia.org/wiki/Min-max_heap
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

#include "Heap.h"
#include "HeapUtils.h"
#include "StringUtils.h"


/**
 * Constructor
 * Initializes heap array and assigns the comparator required in heapification
 *
 * @param heapArraySize size of the array that backs the tree
 * @param comparatorFunction pointer to a comparator function (greater, smaller) for min or max heap
 */
Heap::Heap(int heapArraySize, bool (*comparatorFunction)(float, float)) : comparator(comparatorFunction) {
    heapCurrentIndex = NOT_DEFINED;
    maxHeapSize = heapArraySize;
    heapArray = new float[heapArraySize];
    for (int i = 0; i < heapArraySize; i++) {
        heapArray[i] = FLOAT_MIN;
    }
}

/**
 * Constructor
 * Initializes heap array with the DEFAULT_HEAP_SIZE and assigns the comparator required in heapification
 *
 * @param comparatorFunction pointer to a comparator function (greater, smaller) for min or max heap
 */
Heap::Heap(bool (*comparatorFunction)(float, float)) : Heap(DEFAULT_MAX_HEAP_SIZE, comparatorFunction) {
}

/**
 * Destructor
 */
Heap::~Heap() {
    if ( this->heapArray ) {
        // delete[] heapArray; // ToDo Error (free(): double free detected in tcache 2)
    }
}

/**
 * Add a key = element to the heap
 *
 * @param key new heap element
 * @return true (success) or false (failure)
 */
bool Heap::add(int key) {
    bool inserted = false;
    if(heapCurrentIndex + 1 < maxHeapSize ) {
        heapCurrentIndex++;
        inserted = true;
        heapArray[heapCurrentIndex] = key;
        lastInsertedIndex = heapCurrentIndex;
        heapify(heapCurrentIndex);
    }
    return inserted;
}

/**
 * Check for lazily deleted root and poll (remove) recursively
 */
void Heap::checkDeletedRoot() {
    if(heapArray[0] <= FLOAT_MIN) { // ToDo consider min/max
        poll();
        checkDeletedRoot();
    }
}

/**
 * Get = retrieve the root of the tree = element with highest "priority" = lowest or highest value
 * If there is no root element FLOAT_MIN is returned
 *
 * @return the top / root element: the lowest value for min heap, the largest value for max heap
 */
float Heap::peek() {
    float peedkedElement = FLOAT_MIN;
    if(heapCurrentIndex >= 0 ) {
        peedkedElement = heapArray[0];
    }
    return peedkedElement;
}

/**
 * Take the root of the tree: retrieve and removes the element
 * If there is no root element FLOAT_MIN is returned
 *
 * @return the top / root element: the lowest value for min heap, the largest value for max heap
 */
float Heap::poll() {
    float polledElement = FLOAT_MIN;
    if(heapCurrentIndex != NOT_DEFINED) {
        polledElement = heapArray[0];
        swap(heapArray[0], heapArray[heapCurrentIndex]);
        heapify(parent(heapCurrentIndex--)); // rebuild the tree and decrease size
    }
    return polledElement;
}

/**
 * Returns the number of elements in the help
 *
 * @return number of elements in the heap or 0 (heap is empty)
 */
int Heap::size() {
    return heapCurrentIndex + 1;
}

/**
 * Get the parent (index) of the element with the given index
 *
 * @param index of the element
 * @return parent (index) of the element
 */
int Heap::parent(int index) {
    if( index <= 0 ) {
        return NOT_DEFINED;
    }
    return (index - 1)/2;
}

/**
 * (Re-)Create the heap from the element with the index towards the root
 * = converting a binary tree into a heap (complete, and parent of a node is more "extreme"
 * than the node)
 *
 * @param index of the element
 */
void Heap::heapify(int index) {
    int parentIndex = parent(index);
    // comparision: max heap or min heap (depends on the comparator)
    if( parentIndex >= 0 && comparator(heapArray[index], heapArray[parentIndex]) ) {
        swap(heapArray[index], heapArray[parentIndex]);
        heapify(parentIndex);
    }
}

/**
 * Find an element by its key / value and update (replace) it with the new value
 *
 * @param oldElement to be found and updated in the heap
 * @param newElement to be used for the update
 * @return true (updated) or false (not found)
 */
bool Heap::findAndUpdateElement(float oldElement, float newElement) {
    int indexOldElement =  find(oldElement);
    if (indexOldElement != NOT_DEFINED) {
        heapArray[indexOldElement] = newElement;
        heapify(indexOldElement);
        return true;
    }
    return false;
}

/**
 * Delete an element by its key / value (lazy delete)
 *
 * @param element to be deleted
 * @return true (deleted) or false (not found)
 */
bool Heap::deleteLazy(float element) {
    if (element == peek()) {
        poll();
        return true;
    }
    int indexElementToBeDeleted =  find(element);
    if (indexElementToBeDeleted != NOT_DEFINED) {
        if (lastInsertedIndex != NOT_DEFINED) {
            // ToDo test this
            heapArray[indexElementToBeDeleted] = heapArray[lastInsertedIndex];
            heapify(parent(lastInsertedIndex));
            heapArray[lastInsertedIndex] = FLOAT_MIN; // ToDo consider min/max
            lastInsertedIndex = NOT_DEFINED;
            return true;
        }
    }
    return false;
}

/**
 * Resets the heap without freeing the memory
 */
void Heap::reset() {
    heapCurrentIndex  = NOT_DEFINED;
    lastInsertedIndex = NOT_DEFINED;
    while(size() > 0) poll();
}


/**
 * Converts the heap array to a string
 * @return heap array as a string
 */
char* Heap::toString() {
    char* result = (char*) "";
    char buffer[30];
    for (int i = 0; i <= heapCurrentIndex; i++) {
        stringFormat(buffer, FORMAT_STRING_INT, heapArray[i]);
        result = stringConcat(result, buffer);
    }
    return result;
}

/**
 * Find an element by its key / value and return the index (in the heap array)
 *
 * @param element to be found in the heap
 * @return index of the element in the heap array
 */
int Heap::find(float element) {
    for (int i = 0; i <= heapCurrentIndex; i++) {
        if (heapArray[i] == element) return i;
    }
    return NOT_DEFINED;
}


