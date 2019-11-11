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

#ifndef RUNNINGMEDIAN_HEAPUTILS_H
#define RUNNINGMEDIAN_HEAPUTILS_H

/**
 * Comparator for "greater than or equal to"
 * first parameter a is compared with second parameter b: a >= b?
 *
 * @param a first parameter
 * @param b second parameter
 * @return true (a>=b) or false (a<b)
 */
bool greaterOrEqual(int a, int b);

/**
 * Comparator for "less than or equal to"
 * first parameter a is compared with second parameter b: a <= b?
 *
 * @param a first parameter
 * @param b second parameter
 * @return true (a<=b) or false (a>b)
 */
bool lessOrEqual(int a, int b);

/**
 * Calculation of the mean (average) for 2 values
 * mean = (a+b)/2
 *
 * @param a first param
 * @param b first param
 * @return mean value of a and b
 */
float mean(int a, int b);

/** Generalized signum function
 * used for comparision of the the sizes of min and max heap
 *  * = 0  if a == b  - same size = heaps are balanced
 * = -1 if a < b   - left contains less elements than right
 * = 1  if a > b   - left contains more elements than right
 *
 * @param left value
 * @param right value
 * @return comparision result: 0, 1, or -1
 **/
int signum(int a, int b);

/** Swap a and b
 * changes the value of a with the value of b
 *
 * @param a first param will get the value of b
 * @param b second param will get the value of a
 */
void swap(int &a, int &b);

#endif //RUNNINGMEDIAN_HEAPUTILS_H
