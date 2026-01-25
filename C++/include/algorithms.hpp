#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <any>
#include <ctime>
#include <string>
#include <unordered_map>
#include <vector>

#include "marker.hpp"

extern const int FPS;

struct QuickSortHelper {
    int m_low;
    int m_high;
    int m_pivot;
    int m_i;
    int m_j;
    bool m_done;
    QuickSortHelper(int low, int high);
};

class Algorithm {
   private:
    void reset_map();
    std::unordered_map<std::string, std::any> m_data_map;
    bool (*m_func)(Marker&,
                   Algorithm&);  // if bool return true, its done

    const std::string m_name;
    const std::string m_time_complexity;
    const std::string m_space_complexity;

    // Tracking Variables
    std::time_t m_sort_start;
    std::time_t m_sort_end;
    int m_sort_time = 0;
    int m_writes = 0;
    int m_auxiliary_writes = 0;
    int m_swaps = 0;
    int m_accesses = 0;
    int m_comparisons = 0;

   public:
    Algorithm(std::string name, std::string time_complexity,
              std::string space_complexity,
              bool (*function)(Marker&, Algorithm&));
    // 0 = ran without return true
    // 1 = ran and returned true -> stop
    // 2 = didnt run
    int run(Marker& marker);
    int highest_helpers = 0;
    int check(Marker& marker);
    void insert_data(std::string key, std::any data);
    // nullptr if not retrievable
    std::any retrieve_data(std::string key);
    template <typename T>
    T get_value(const std::string& key, T default_val);

    int m_last_check_index = 0;
    unsigned int m_highest_check_value = 0;
    // 0 = check still running
    // 1 = didnt run check yet
    // 2 = check succesful
    // 3 = check failed
    int m_check_result = 1;
    bool m_check_ready = false;
};

// TODO: if you want make the other sorting algorithms too and let them play.

bool bubble_sort_step(Marker& marker, Algorithm& alg);
bool cocktail_shaker_sort_step(Marker& marker, Algorithm& alg);
bool quick_sort_step(Marker& marker, Algorithm& alg);
bool insertion_sort_step(Marker& marker, Algoritm& alg);
bool selection_sort_step(Marker& marker, Algoritm& alg);
bool merge_sort_step(Marker& marker, Algoritm& alg);
int check_array_step(Marker& marker, Algorithm& alg);

#endif  // ALGORITHMS_HPP