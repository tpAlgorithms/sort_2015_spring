#include <iostream>
#include <cstdio>
#include <vector>

/*
typedef int data_t;

void sort(data_t *data, size_t size) {

}
*/

template <typename data_t>
void swap(data_t &lhs, data_t &rhs) {
  data_t tmp = lhs;
  lhs = rhs;
  rhs = tmp;
}

bool less(const int &lhs, const int &rhs) {
  return lhs < rhs;
}

bool min_digit_less(const int &lhs, const int &rhs) {
  return (lhs % 10) < (rhs % 10);
}

struct date_t {
  int year;
  int month;
  int day;
};

bool less(const date_t &lhs, const date_t &rhs) {
  if (lhs.year < rhs.year) {
    return true;
  } else if (lhs.year > rhs.year) {
    return false;
  } else {
    if (lhs.month < rhs.month) {
      return true;
    } else if (lhs.month > rhs.month) {
      return false;
    } else {
      return lhs.day < rhs.day;
    }
  }
}

bool complex_less(const int &lhs, const int &rhs) {
  if (min_digit_less(lhs, rhs)) {
    // lhs < (2) rhs
    return true;
  } else if (min_digit_less(rhs, lhs)) {
    // lhs > (2) rhs
    return false; 
  } else {
    // lhs ==(2) rhs
    return less(lhs, rhs);
  }
}

struct min_digit_less_t {
  bool operator() (const int &lhs, const int &rhs) const {
    return min_digit_less(lhs, rhs); 
  }
};

template <typename data_t, typename less_t>
void sort(data_t *begin, data_t *end, const less_t &_less) {
  for (data_t *it = begin; it != end; ++it) {
    for (data_t *pos = end - 1; pos != it; --pos) {
      if (_less(pos[0], pos[-1])) {
        swap(pos[0], pos[-1]);
      }
    }
  }
}

int main() {

  std::vector<int> data;
  int value;
  while(fscanf(stdin, "%d", &value) == 1) {
    data.push_back(value);
  }

  //std::sort(&data[0], &data[data.size()]);
  min_digit_less_t less_object;
  //::sort(&data[0], &data[data.size()], less);
  //::sort(&data[0], &data[data.size()], less_object);
  
  ::sort(&data[0], &data[data.size()], complex_less);

  for (size_t i = 0; i < data.size(); ++i) {
    printf("%d\n", data[i]);
  }

  return 0;
};





















