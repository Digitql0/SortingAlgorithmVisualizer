#include "sorter.hpp"

#include <raylib.h>

#include "algorithms.hpp"
#include "marker.hpp"

Sorter::Sorter(std::string name, std::string time_complexity,
               std::string space_complexity,
               bool (*sort_func)(Marker &, Algorithm &), int num_elements)
    : m_marker(num_elements),
      m_algorithm(name, time_complexity, space_complexity, sort_func) {}

AlgStatus Sorter::run_step() { return m_algorithm.run(m_marker); }

Marker &Sorter::get_marker() { return m_marker; }

// void Sorter::run(void (*draw)(Sorter&)) {
//     draw(*this);
//     std::this_thread::sleep_for(std::chrono::seconds(1));
//     visual_start = std::time(nullptr);
//     func(*this, draw);
//     visual_end = std::time(nullptr);
//     clearMarks();
//     draw(*this);
//     checkArray(draw);
//     std::this_thread::sleep_for(std::chrono::seconds(2));
// }

CheckStatus Sorter::check_array_step() { return m_algorithm.check(m_marker); }

Algorithm &Sorter::get_algorithm() { return m_algorithm; }

CheckStatus Sorter::get_check_status() { return m_algorithm.m_check_result; }

AlgStatus Sorter::get_algorithm_status() {
  return m_algorithm.m_algorithm_result;
}