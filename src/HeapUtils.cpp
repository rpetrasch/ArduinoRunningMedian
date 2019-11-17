/**
 * Implementation for the Heap Utilities
 *
 * @author Roland Petrasch, roland.petrasch@gmail.com
 * @copyright 2019 Roland Petrasch, Thailand
 * @version 1.0
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

#include "HeapUtils.h"

/**
 * Comparator for "greater than or equal to"
 * first parameter a is compared with second parameter b: a >= b?
 *
 * @param a first parameter
 * @param b second parameter
 * @return true (a>=b) or false (a<b)
 */
bool greaterOrEqual(float a, float b) {
    return a >= b;
}

/**
 * Comparator for "less than or equal to"
 * first parameter a is compared with second parameter b: a <= b?
 *
 * @param a first parameter
 * @param b second parameter
 * @return true (a<=b) or false (a>b)
 */
bool lessOrEqual(float a, float b) {
    return a <= b;
}

/**
 * Calculation of the mean (average) for 2 values
 * mean = (a+b)/2
 *
 * @param a first param
 * @param b first param
 * @return mean value of a and b
 */
float mean(float a, float b) {
    return (a + b) / 2;
}

/** Generalized signum function
 * used for comparision of the the sizes of min and max heap
 * = 0  if a == b  - same size = heaps are balanced
 * = -1 if a < b   - left contains less elements than right
 * = 1  if a > b   - left contains more elements than right
 *
 * @param left value
 * @param right value
 * @return comparision result: 0, 1, or -1
 **/
int signum(int left, int right) {
    if( left == right )
        return 0;
    return left < right ? -1 : 1;
}

/** Swap a and b
 * changes the value of a with the value of b
 *
 * @param a first param will get the value of b
 * @param b second param will get the value of a
 */
void swap(float &a, float &b){
    float tmp = a;
    a = b;
    b = tmp;
}

/**
 * Get the index of the left child given the parent index
 *
 * @param parentIndex index of the parent element
 * @return index of the left child
 **/
int leftChildIndex(int parentIndex) {
    return 2 * parentIndex + 1;
}

/**
 * Get the index of the left child given the parent index
 *
 * @param parentIndex  index of the parent element
 * @return index of the right child
**/
int rightChildIndex(int parentIndex) {
    return 2 * parentIndex + 2;
}



/**
 * Get the parent (index) of the element with the given index
 *
 * @param index of the element
 * @return parent (index) of the element
 */
int parentIndex(int index) {
    if( index <= 0 ) {
        return NOT_DEFINED;
    }
    return (index - 1)/2;
}

/**
 * Checks whether the element has a parent
 *
 * @param index of the element to checked for a parent
 * @return true  = has parent
 **/
bool hasParent(int index) {
    return parentIndex(index) >= 0;
}