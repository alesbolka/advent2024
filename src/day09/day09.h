#ifndef DAY_09
#define DAY_09

#include <string>
#include <vector>

namespace day09
{

class Disk {
public:
  Disk(std::string input);
  void defragment();
  int64_t checkSum();
protected:
  std::vector<uint16_t> data;

  int findNextEmpty(int offset);
  void print();
};

inline int64_t task1(std::vector<std::string> lines)
{
  Disk disk(lines[0]);

  disk.defragment();
  return disk.checkSum();
}

inline int64_t task2(std::vector<std::string> lines)
{
  return -1;
}

inline int64_t executor(int task, std::vector<std::string> input)
{

  if (task == 1) {
    return task1(input);
  }

  if (task == 2) {
    return task2(input);
  }

  return -1;
};


}

#endif
