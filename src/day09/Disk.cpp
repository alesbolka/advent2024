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

void Disk::defragment()
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

int64_t Disk::checkSum()
{
  int64_t res = 0;

  for (int ii = 0; data[ii] != 0; ii++)
  {
    res += ii * (data[ii] - 1);
  }

  return res;
}

}