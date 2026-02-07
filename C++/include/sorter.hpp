#pragma once
#include <raylib.h>

#include <string>

#include "algorithms.hpp"

class Sorter {
private:
  int m_checked_indeces = 0;
  Algorithm m_algorithm;
  Marker m_marker;

public:
  Sorter(std::string name, std::string time_complexity,
         std::string space_complexity, bool (*sort_func)(Marker &, Algorithm &),
         int num_elements);

  Marker &get_marker();

  AlgStatus run_step();
  CheckStatus check_array_step();
};