#include <iostream>
#include <cstdio>
#include <vector>


void dump(int *begin, int * end) {
  std::cout << "[" << ( end - begin ) << "]: ";
  for (int *it = begin; it != end; ++it) {
    std::cout << *it << ",";
  } 
  std::cout << std::endl;
}

template <typename data_t>
void swap(data_t &lhs, data_t &rhs) {
  data_t tmp = lhs;
  lhs = rhs;
  rhs = tmp;
}

bool less(const int &lhs, const int &rhs) {
  return lhs < rhs;
}

template <typename data_t, typename less_t>
data_t *split(data_t *begin, data_t *end, less_t &less) {
//  std::cout << "SPLIT:";
//  dump(begin, end);
  // [ begin ... pivot .... current ..... end ]
  // [ begin pivot_0 ....pivot .... curent == end ]
  data_t *pivot = begin + 1; // 1
  data_t *current = begin + 1; // 1
  for(; current != end; ) {
    if (less(*current, *begin)) {
//      std::cout << "L pivot:" << (pivot - begin) << " current: " << (current - begin) << std::endl;
//      dump(begin, end);
      swap(*current, *pivot);
      ++pivot;
      ++current;
    } else {
//      std::cout << "R pivot:" << (pivot - begin) << " current: " << (current - begin) << std::endl;
      ++current;
    }
  }
  swap(*begin, *(pivot - 1));
  return pivot - 1;
}

template <typename data_t, typename less_t>
data_t *_split(data_t *begin, data_t *end, less_t &less) {
  //std::cout << "SPLIT:";
  //dump(begin, end);

  // [ begin ........ end]
  // [ .j ........... i ..]

  bool direction = 0;
  data_t *pivot = begin;
  for (data_t *current = end - 1; pivot != current; ) {
    //std::cout << "d:" << direction << " pivot:" << (pivot - begin) << " current: " << (current - begin) << std::endl;
    if (less(*current, *pivot) xor direction) {
      swap(*current, *pivot);
      swap(current, pivot);
      direction = !direction;
    }

    if (direction) {
      ++current;
    } else {
      --current;
    }
  }
  return pivot;
}

template <typename data_t, typename less_t>
void quick_sort(data_t *begin, data_t *end, less_t &less) {
  //std::cout << "QSORT:";
  //dump(begin, end);
  
  //if (std::distance(begin, end) < 2) { return; }
  if (begin == end) { return; }
  if (begin + 1 == end) { return; }
 
  //swap(*begin, *(begin + rand() % (end - begin)));
  //swap(*begin, *(begin + (end - begin) / 2));
  data_t *pivot = split(begin, end, less);

  // [begin ....... pivot-1  pivot  pivot+1 ..... end)
  // [begin ....... pivot-1][pivot][pivot+1 ..... end)
  quick_sort(begin, pivot, less); 
  quick_sort(pivot + 1, end, less); 
}


int main() {
  srand(42);
  
  std::vector<int> data;
  int value;
  while(fscanf(stdin, "%d", &value) == 1) {
    data.push_back(value);
  }

  quick_sort(&data[0], &data[data.size()], less);
  
  for (size_t i = 0; i < data.size(); ++i) {
    printf("%d\n", data[i]);
  }

  return 0;
};


















