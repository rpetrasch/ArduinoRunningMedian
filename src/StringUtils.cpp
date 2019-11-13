/**
 * String Utilities Implementation (version for standard C++, do NOT use on Arduino)
 *
 * These functions are needed for the toString() method and because there is a difference
 * between standard C++ and Arduino strings so that the implementation is specific to the platform.
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

#include <cstdio>
#include <string>
#include <cstring>
#include "StringUtils.h"

/**
 * Simple string formatter
 *
 * @param buffer for the string
 * @param formatString string with format %d
 * @param value to be formatted
 * @return formatted string
 */
char* stringFormat(char* buffer, const char* formatString, float value) {
    sprintf(buffer, formatString, value);
    return buffer;
}

/**
 * Concatenation of 2 strings
 *
 * @param string1
 * @param string2
 * @return concatenated string
 */
char* stringConcat(char* string1, char* string2) {
//    std::string s1(string1);
//    std::string s2(string2);
//    std::string result = s1 + s2;
//    const char* resultConstCharArray = result.c_str();
//    char * resultCharArray = (char *) malloc(sizeof(char) * strlen(resultConstCharArray));
//    strcpy(resultCharArray, resultConstCharArray);
//    return resultCharArray;
    return nullptr;
}