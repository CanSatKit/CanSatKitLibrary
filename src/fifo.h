#ifndef CANSATKITLIBRARY__FIFO_H_
#define CANSATKITLIBRARY__FIFO_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>

template<class T, uint16_t max_size>
class FIFO {
 public:
  FIFO() {
    flush();
  }
  
  void append(T element) {
    if (size() != max_size) {
      count++;
      writePos = (writePos + 1) % max_size;
      data[writePos] = element;
    }
  }
  
  T get() {
    if (size() != 0) {
      count--;
      readPos = (readPos + 1) % max_size;
      return data[readPos];
    }
    return T();
  }
  
  size_t size() const {
    return count;
  }

  size_t free_space() const {
    return max_size - count;
  }
  
  void flush() {
    writePos = readPos = count = 0;
  }
  
 private:
  volatile uint16_t writePos, readPos, count;  
  T data[max_size];
};

#endif  // CANSATKITLIBRARY__FIFO_H_
