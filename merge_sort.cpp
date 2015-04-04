#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
    /*
    switch(cmp(a[i], b[j])) { 
      case -1: {  
        //1 
      }; break;
      case 1: {  
        //2 
      }; break;
      case 0 : {
        //3
      }; break;
      default:
        return;
    };
    */
void dump(const int *begin, const int * end) {
  std::cout << "[" << ( end - begin ) << "]: ";
  for (const int *it = begin; it != end; ++it) {
    std::cout << *it << ",";
  } 
  std::cout << std::endl;
}



bool less(const int &lhs, const int &rhs) {
  return lhs < rhs;
}

template <typename data_t, typename less_t>
void merge(
    const data_t *a,
    size_t a_size,
    const data_t *b,
    size_t b_size,
    data_t *result,
    less_t &less
) {
  //std::cout << "MERGE:";
  //dump(a, &a[a_size]);
  //dump(b, &b[b_size]);
  size_t i = 0;
  size_t j = 0;
  //for (size_t result_pos = 0; i < a_size && j < b_size; ++result_pos) {
  for (; i < a_size && j < b_size;) {
    if (less(b[j], a[i])) {
      result[i + j] = b[j];
      ++j;
    } else {
      result[i + j] = a[i];
      ++i;
    }
  }

  if (i == a_size) { // a is over
    for (; j < b_size; ++j) {
      result[i + j] = b[j];
    }
  } else { // b is over
    for (; i < a_size; ++i) {
      result[i + j] = a[i];
    }
  }
  //dump(result, &result[a_size + b_size]);
}

template <typename data_t, typename less_t>
void merge_sort(
    data_t *begin,
    data_t *end,
    data_t *tmp,
    less_t &less
) {
  data_t *data = begin;
  //size_t size = end - begin;
  size_t size = std::distance(begin, end);
  /*
  [0  1  2  9  8  6  7  5  0  1  2]
  [0][1][2][9][8][6][7][5][0][1][2]
  [0  1][2  9][6  8][5  7][0  1][2]
  [0  1  2  9][5  7  6  8](0  1  2)
  [0  1  2  9__5  7  6  8](0  1  2)
  (0  1  2  9__5  7  6  8  0  1  2)
  */

  size_t iteration_count = 0;
  for (size_t chunk_size = 1; chunk_size < size; chunk_size *= 2, ++iteration_count) {
    size_t offset = 0;
    for (; offset + chunk_size < size ; offset += chunk_size * 2) {
      size_t second_chunk_size = chunk_size;
      if (size < offset + chunk_size * 2) { // is last iteration
        second_chunk_size = size - offset - chunk_size;
      }
      merge(&data[offset], chunk_size, &data[offset + chunk_size], second_chunk_size, &tmp[offset], less); 
    }
    //for (; offset < size; ++offset) {
    //  tmp[offset] = data[offset];
    //}
    if (offset < size ) {
      merge(&data[offset], size - offset, &data[size], 0, &tmp[offset], less);
    }
    std::swap(data, tmp);
  }
  //std::cout << "iter_count:" << iteration_count << std::endl;
  if (iteration_count % 2) {
    std::swap(data, tmp);
    //std::cout << "DO_COPY:";
    //dump(data, &data[size]);
    //dump(tmp, &tmp[size]);
    //memcpy(&data[0], &tmp[0], sizeof(data_t) * size);
    for (size_t pos = 0; pos < size; ++pos) {
      data[pos] = tmp[pos];
    } 
    //std::cout << "DONE:";
    //dump(data, &data[size]);
    //dump(tmp, &tmp[size]);
  }
}

int main() {
  std::vector<int> data;
  int value;
  while(fscanf(stdin, "%d", &value) == 1) {
    data.push_back(value);
  }
  
  std::vector<int> tmp(data.size());
  merge_sort(&data[0], &data[data.size()], &tmp[0], less);
  
  for (size_t i = 0; i < data.size(); ++i) {
    printf("%d\n", data[i]);
  }

  return 0;
};


