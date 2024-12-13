#include "./day09.h"
#include <iostream>


using std::string;
using std::vector;

namespace day09
{

Disk::Disk(string input)
{
  data = vector<uint16_t>{};
  // unsafe if input is too long, but i'm skipping some steps
  // starting with 1 to indicate 0 = empty space
  uint16_t fileIndex = 1;

  for (int ii = 0; ii < input.size(); ii += 2)
  {
    for (int jj = 0; jj < (input[ii] - '0'); jj++)
    {
      data.push_back(fileIndex);
    }

    fileIndex++;
    for (int jj = 0; jj < (input[ii + 1] - '0'); jj++)
    {
      data.push_back(0);
    }
  }
}

int Disk::findNextEmpty(int offset)
{
  for (int jj = offset; jj < data.size(); jj++)
  {
    if (data[jj] == 0)
    {
      return jj;
    }
  }

  return -1;
}

void Disk::fragment()
{
  int lastKnownEmpty = 0;

  for (int ii = (data.size() - 1); ii > lastKnownEmpty; ii--) {
    if (data[ii] == 0) {
      continue;
    }

    lastKnownEmpty = findNextEmpty(lastKnownEmpty);
    data[lastKnownEmpty++] = data[ii];
    data[ii] = 0;
  }
}

void Disk::print()
{
  for (int ii = 0; ii < data.size(); ii++)
  {
    if (data[ii] == 0) {
      std::cout << '.';
    }
    else {
      std::cout << (data[ii] - 1);
    }
  }

  std::cout << std::endl;
}

uint64_t Disk::checkSum()
{
  uint64_t res = 0;

  for (int ii = 0; ii < data.size(); ii++)
  {
    if (data[ii] == 0)
    {
      continue;
    }
    res += ii * (data[ii] - 1);
  }

  return res;
}

// part 2

int Disk::findEmptyBlock(int offset, int desiredLength)
{
  // std::cout << "searching for: " << desiredLength << " from " << offset << std::endl;
  int emptyLength = 0;
  for (int ii = offset; ii < data.size(); ii++)
  {
    if (data[ii] == 0)
    {
      emptyLength++;
      if (emptyLength == desiredLength) {
        return ii - emptyLength + 1;
      }
    }
    else if (emptyLength != 0)
    {
      emptyLength = 0;
    }
  }

  return -1;
}

void Disk::defragment()
{

  int firstEmpty = findEmptyBlock(0, 1);
  uint16_t currentFile = 0;
  int fileLength = 0;

  for (int ii = (data.size() - 1); ii > firstEmpty; ii--) {
    if (data[ii] == 0) {
      continue;
    }

    currentFile = data[ii];
    fileLength = 0;

    while (ii > firstEmpty && data[ii] == currentFile)
    {
      fileLength++;
      ii--;
    }

    int emptySegment = findEmptyBlock(firstEmpty, fileLength);
    if (emptySegment < 0 || emptySegment >= ii)
    {
      // fix the index, since the loop with decrease by 1 as well
      ii++;
      continue;
    }

    if (emptySegment == firstEmpty)
    {
      firstEmpty += emptySegment;
    }

    for (int jj = 0; jj < fileLength; jj++)
    {
      data[emptySegment + jj] = data[ii + jj + 1];
      data[ii + jj + 1] = 0;
    }

    // fix the index, since the loop with decrease by 1 as well
    ii++;
  }
}

}