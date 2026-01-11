#ifndef MARKER_HPP
#define MARKER_HPP

#include <raylib.h>

#include <ctime>
#include <random>
#include <unordered_map>

#include "vector"

extern const Color BACKGROUND;
extern const Color DEFAULT_MARK;
extern const Color DEFAULT_SUCCESS;
extern const Color DEFAULT_FAILURE;

class Marker {
   private:
    void make_array();
    std::vector<unsigned int> m_arr;
    unsigned int m_length;
    std::unordered_map<unsigned int, Color> m_arr_marks;

    std::random_device m_rd;
    std::mt19937 m_gen;

   public:
    Marker(int num_elements);
    void shuffle_array();
    size_t get_length();
    void mark_index(int index, Color col);
    Color get_marked_index(int index);
    void clear_marks();
    std::vector<unsigned int>& get_array();
};

#endif  // MARKER_HPP
