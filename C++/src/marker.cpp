#include "marker.hpp"

#include <algorithm>

const Color BACKGROUND = BLACK;
const Color DEFAULT_MARK = WHITE;
const Color DEFAULT_SUCCESS = GREEN;
const Color DEFAULT_FAILURE = RED;

Marker::Marker(int num_elements) : m_length(num_elements) {
    m_arr = std::vector<unsigned int>();
    m_arr_marks = std::unordered_map<unsigned int, Color>();
    shuffle_array();
}

void Marker::make_array() {
    if (m_arr.size() != m_length) m_arr.resize(m_length, 0);

    std::iota(m_arr.begin(), m_arr.end(),
              1);  // Overwrites the Values in the Array starting with one
    // incrementing for each element after that.
}

void Marker::shuffle_array() {
    if (m_arr.size() != m_length) make_array();

    std::shuffle(m_arr.begin(), m_arr.end(),
                 m_gen);  // randomizes the array order
}

size_t Marker::get_length() { return m_length; }

void Marker::mark_index(int index, Color col) {
    if (index < m_length && index >= 0) m_arr_marks[index] = col;
}

Color Marker::get_marked_index(int index) {
    Color out = DEFAULT_MARK;
    auto it = m_arr_marks.find(index);
    if (it != m_arr_marks.end()) {
        out = it->second;
    }
    return out;
}

void Marker::clear_marks() { m_arr_marks.clear(); }

std::vector<unsigned int>& Marker::get_array() { return m_arr; }