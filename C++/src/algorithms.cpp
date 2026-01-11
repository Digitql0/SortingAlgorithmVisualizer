#include "algorithms.hpp"

#include <raylib.h>

#include <algorithm>
#include <any>
#include <cstdio>
#include <string>
#include <unordered_map>
#include <vector>

#include "marker.hpp"

const int FPS = 60;

QuickSortHelper::QuickSortHelper(int low, int high)
    : m_low(low),
      m_high(high),
      m_pivot(m_high),
      m_i(m_low - 1),
      m_j(m_low),
      m_done(false) {}

Algorithm::Algorithm(std::string name, std::string time_complexity,
                     std::string space_complexity,
                     bool (*function)(Marker&, Algorithm&))
    : m_name(name),
      m_time_complexity(time_complexity),
      m_space_complexity(space_complexity),
      m_func(function) {
    reset_map();
}

void Algorithm::reset_map() {
    m_data_map = std::unordered_map<std::string, std::any>();
}

int Algorithm::run(Marker& marker) {
    int out = 2;
    if (m_func != nullptr) out = m_func(marker, *this);
    return out;
}

int Algorithm::check(Marker& marker) {
    int out = check_array_step(marker, *this);
    if (out == 1) m_check_ready = true;
    return out;
}

void Algorithm::insert_data(std::string key, std::any data) {
    m_data_map[key] = data;
}

std::any Algorithm::retrieve_data(std::string key) {
    std::any out;
    auto it = m_data_map.find(key);
    if (it != m_data_map.end()) {
        out = it->second;
    }
    return out;
}

template <typename T>
T Algorithm::get_value(const std::string& key, T default_val) {
    std::any any = retrieve_data(key);

    if (any.has_value()) {
        // Passing a refence to std::any, returns a pointer
        // if value is therefore nullptr it will return the default
        // if value isnt a nullptr it will return the dereferenced pointer
        auto value = std::any_cast<T>(&any);
        if (value) {
            return *value;
        }
    }
    insert_data(key, default_val);
    return default_val;
}

bool bubble_sort_step(Marker& marker, Algorithm& alg) {
    marker.clear_marks();
    if (marker.get_length() < 2) return true;

    int index = alg.get_value("index", 0);

    size_t bound = alg.get_value("bound", marker.get_length());

    // it reached the end of the array
    if (index >= marker.get_length() - 1 || index >= bound - 1) {
        // reset the index to zero
        alg.insert_data("index", 0);
        alg.insert_data("bound", bound - 1);

        marker.clear_marks();
        marker.mark_index(0, BLUE);

        bool done = alg.get_value("done", true);
        if (!done) alg.insert_data("done", true);
        return done;
    }

    marker.mark_index(index, BLUE);

    auto& arr = marker.get_array();
    if (arr[index] > arr[index + 1]) {
        std::swap(arr[index], arr[index + 1]);
        alg.insert_data("done", false);
    }

    alg.insert_data("index", index + 1);
    return false;
}

bool cocktail_shaker_sort_step(Marker& marker, Algorithm& alg) {
    marker.clear_marks();

    auto end = alg.get_value("end", marker.get_length() - 1);
    auto start = alg.get_value("start", 0u);
    auto swapped = alg.get_value("swapped", false);
    auto forward = alg.get_value("forward", true);
    auto index = alg.get_value("index", 0u);

    marker.mark_index(index, BLUE);

    if (forward) {
        if (index >= end) {
            forward = !forward;
            end--;
            alg.insert_data("forward", forward);
            alg.insert_data("end", end);
            if (swapped) {
                alg.insert_data("swapped", false);
                return false;
            } else
                return true;
        }

        auto& arr = marker.get_array();
        alg.insert_data("index", index + 1);
        if (arr[index] > arr[index + 1]) {
            std::swap(arr[index], arr[index + 1]);
            alg.insert_data("swapped", true);
            return false;
        }
    } else {
        if (index <= start) {
            forward = !forward;
            start++;
            alg.insert_data("forward", forward);
            alg.insert_data("start", start);
            if (swapped) {
                alg.insert_data("swapped", false);
                return false;
            } else
                return true;
        }

        auto& arr = marker.get_array();
        alg.insert_data("index", index - 1);
        if (arr[index] < arr[index - 1]) {
            std::swap(arr[index], arr[index - 1]);
            alg.insert_data("swapped", true);
            return false;
        }
    }

    return false;
}

bool quick_sort_step(Marker& marker, Algorithm& alg) {
    std::vector<QuickSortHelper> helpers =
        alg.get_value("helpers", std::vector<QuickSortHelper>());

    if (helpers.empty()) {
        bool started = alg.get_value("started", false);
        if (!started) {
            alg.insert_data("started", true);
            QuickSortHelper first(0, marker.get_length() - 1);
            helpers.push_back(first);
            alg.insert_data("helpers", helpers);
        }
        return started;
    }

    QuickSortHelper last = helpers[helpers.size() - 1];

    if ((last.m_low >= last.m_high) || last.m_done) {
        marker.mark_index(last.m_pivot, DEFAULT_MARK);
        helpers.pop_back();
        alg.insert_data("helpers", helpers);
        return false;
    }

    // Partition
    auto& arr = marker.get_array();
    auto pivot_val = arr[last.m_pivot];

    if (last.m_j >= last.m_high) {
        std::swap(arr[last.m_i + 1], arr[last.m_high]);
        marker.mark_index(last.m_pivot, DEFAULT_MARK);
        last.m_pivot = last.m_i + 1;
        marker.mark_index(last.m_pivot, BLUE);
        last.m_done = true;
        helpers.back() = last;
        if (last.m_pivot + 1 < last.m_high) {
            QuickSortHelper r(last.m_pivot + 1, last.m_high);
            marker.mark_index(r.m_pivot, BLUE);
            helpers.push_back(r);
        }
        if (last.m_low < last.m_pivot - 1) {
            QuickSortHelper l(last.m_low, last.m_pivot - 1);
            marker.mark_index(l.m_pivot, BLUE);
            helpers.push_back(l);
        }
        alg.insert_data("helpers", helpers);
        if (helpers.size() > alg.highest_helpers)
            alg.highest_helpers = helpers.size();
        return false;
    }

    if (arr[last.m_j] <= pivot_val) {
        last.m_i++;
        std::swap(arr[last.m_i], arr[last.m_j]);
    }

    last.m_j++;
    helpers.back() = last;
    alg.insert_data("helpers", helpers);
    return false;
}

int check_array_step(Marker& marker, Algorithm& alg) {
    std::printf("%d\n", alg.highest_helpers);
    if (alg.m_check_result == 3) return 3;
    if (alg.m_check_result == 1) {
        alg.m_check_result = 0;
        marker.mark_index(alg.m_last_check_index, DEFAULT_SUCCESS);
    }

    unsigned int check_value = marker.get_array().at(alg.m_last_check_index);

    if (alg.m_highest_check_value <= check_value) {
        marker.mark_index(alg.m_last_check_index, DEFAULT_SUCCESS);
        alg.m_last_check_index += 1;
        alg.m_highest_check_value = check_value;
    } else {
        for (int i = 0; i < alg.m_last_check_index; i++) {
            marker.mark_index(i, DEFAULT_FAILURE);
        }
        return 3;
    }

    if (alg.m_last_check_index >= marker.get_length()) {
        return 2;
    }

    return 0;
}
