#include <raylib.h>

#include <thread>

#include "algorithms.hpp"
#include "marker.hpp"
#include "shared.hpp"
#include "sorter.hpp"

void draw(Sorter &algorithm);

int main() {
  InitWindow(WIDTH, HEIGHT, "Sort Visualizer");
  // SetTargetFPS(FPS);

  Sorter bubble("Bubble Sort", "?", "?", bubble_sort_step, WIDTH / 2);
  Sorter cocktail_shaker("Cocktail Shaker", "?", "?", cocktail_shaker_sort_step,
                         WIDTH / 3 * 2);
  Sorter quick("Quick Sort", "?", "?", quick_sort_step, WIDTH * 2);
  Sorter insertion("Insertion Sort", "?", "?", insertion_sort_step, WIDTH * 2);
  Sorter selection("Selection Sort", "?", "?", selection_sort_step, WIDTH * 2);
  Sorter merge("Merge Sort", "?", "?", merge_sort_step, WIDTH * 2);

  while (bubble.run_step() != 1 && !WindowShouldClose()) {
    draw(bubble);
  }
  while (bubble.check_array_step() < 2 && !WindowShouldClose()) {
    draw(bubble);
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));

  while (cocktail_shaker.run_step() != 1 && !WindowShouldClose()) {
    draw(cocktail_shaker);
  }

  while (cocktail_shaker.check_array_step() < 2 && !WindowShouldClose()) {
    draw(cocktail_shaker);
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));

  while (quick.run_step() != 1 && !WindowShouldClose()) {
    draw(quick);
  }

  while (quick.check_array_step() < 2 && !WindowShouldClose()) {
    draw(quick);
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));

  while (insertion.run_step() != 1 && !WindowShouldClose()) {
    draw(insertion);
  }

<<<<<<< HEAD
  while (insertion.check_array_step() < 2 && !WindowShouldClose()) {
    draw(insertion);
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));

  while (selection.run_step() != 1 && !WindowShouldClose()) {
    draw(selection);
  }

  while (selection.check_array_step() < 2 && !WindowShouldClose()) {
    draw(selection);
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));

  while (merge.run_step() != 1 && !WindowShouldClose()) {
    draw(merge);
  }

  while (merge.check_array_step() < 2 && !WindowShouldClose()) {
    draw(merge);
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));

  while (!WindowShouldClose()) {
    draw(merge);
  }
  CloseWindow();
=======
  while (insertion.run_step() != 1 && !WindowShouldClose()) {
    draw(insertion);
  }

  while (insertion.check_array_step() < 2 && !WindowShouldClose()) {
    draw(insertion);
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));

  while (selection.run_step() != 1 && !WindowShouldClose()) {
    draw(selection);
  }

  while (selection.check_array_step() < 2 && !WindowShouldClose()) {
    draw(selection);
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));

  while (merge.run_step() != 1 && !WindowShouldClose()) {
    draw(merge);
  }

  while (merge.check_array_step() < 2 && !WindowShouldClose()) {
    draw(merge);
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));

  while (!WindowShouldClose()) {
    draw(merge);
  }
  CloseWindow();
>>>>>>> refs/remotes/origin/main
}

void draw(Sorter &sorter) {
  BeginDrawing();
  Marker &marker = sorter.get_marker();
  std::vector<unsigned int> &arr = marker.get_array();
  int arr_length = arr.size();
  ClearBackground(BACKGROUND);
  if (arr_length <= 0)
    return;

  // TODO: drawText Function implementation

  float bar_width = float(GetScreenWidth()) / arr_length;
  if (bar_width < 1)
    bar_width = 1;

  for (int i = 0; i < arr_length; i++) {
    unsigned int &value = arr.at(i);
    float rect_height = (float(value) / arr_length) * GetScreenHeight();
    Color col = marker.get_marked_index(i);
    DrawRectangle(float(GetScreenWidth()) / arr_length * i,
                  GetScreenHeight() - rect_height, bar_width, rect_height, col);
  }
  EndDrawing();
}