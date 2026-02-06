#include "menu.hpp"
#include "algorithms.hpp"
#include <raylib.h>

void Menu::addSorter(Sorter sorter) { options.push_back(sorter); }

void Menu::addSorter(std::string name, std::string time_complexity,
                     std::string space_complexity,
                     bool (*sort_func)(Marker &, Algorithm &),
                     int num_elements) {
  Sorter sorter(name, time_complexity, space_complexity, sort_func,
                num_elements);
  options.push_back(sorter);
}

void Menu::run() {
  if (!curr) {
    drawMenu();
  } else {
    while (end_condition == false) {
      switch (curr->get_algorithm_status()) {
      case AlgStatus::WAITING:
      case AlgStatus::RUNNING:
        curr->run_step();
        end_condition = end_condition_func();
        break;
      default:
        switch (curr->get_check_status()) {
        case CheckStatus::WAITING:
        case CheckStatus::RUNNING:
          curr->check_array_step();
          end_condition = end_condition_func();
          break;
        default:
          end_condition = true;
          break;
        }
        break;
      }
    }
  }
}

void Menu::drawMenu() {}

void Menu::update(Vector2 mousePosition) {}

Menu::Menu(std::vector<Sorter> sorters) { options = sorters; }

void Menu::assignEndCondition(bool (*func)()) { end_condition_func = func; }

bool static calculateEndCondition() {
  return WindowShouldClose() || GetKeyPressed() != 0;
}