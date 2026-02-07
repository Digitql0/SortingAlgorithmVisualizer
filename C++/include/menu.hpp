#ifndef MENU_HPP
#define MENU_HPP

#include "sorter.hpp"
#include <optional>
#include <raylib.h>
#include <vector>

struct MenuHelper {
    Sorter sorter;
    Rect rect;
}

class Menu {
public:
  void addSorter(Sorter sorter);
  void addSorter(std::string name, std::string time_complexity,
                 std::string space_complexity,
                 bool (*sort_func)(Marker &, Algorithm &), int num_elements);
  void run();
  Menu(std::vector<Sorter> sorters);
  void assignEndCondition(bool (*func)());
  void update(Vector2 mousePosition);

private:
  bool static calculateEndCondition();
  bool (*end_condition_func)() = calculateEndCondition;
  void drawMenu();
  std::vector<MenuHelper> options;
  unsigned int rows;
  unsigned int columns;
  bool end_condition = false;
  std::optional<MenuHelper> curr;
  void (*draw)(Sorter &sorter);
};

#endif // MENU_HPP
