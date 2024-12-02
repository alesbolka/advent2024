#ifndef _H_HELPERS
#define _H_HELPERS

#include <string>
#include <vector>

namespace helpers
{

std::vector<std::string> readFileLines(const std::string path);

std::vector<std::string> splitString(const std::string& str, char separator = '\n');

/**
 * This is a horribly inefficient helper, but it's somewhat magicky and strips all integers from a string into a vector
 */
std::vector<int> parseIntsFromLine(const std::string& str);

void printIntVector(std::vector<int> vec);

}
#endif