from shared import *
from sort_algorithm import *

FPS = 60

# Bubble Sort function
def bubble_sort(alg : SortAlg, draw, clock):
    alg.sort_start = time.time()
    n = alg.length
    for i in range(n):
        for j in range(0, n - i - 1):
            if alg.getArray()[j] > alg.getArray()[j + 1]:
                # Swap the elements
                alg.getArray()[j], alg.getArray()[j + 1] = alg.getArray()[j + 1], alg.getArray()[j]
                alg.swaps += 1
                # Redraw the alg.getArray()ay with the swapped bars
                alg.sort_end = time.time()
                alg.calcSortDuration()
                alg.markIndex(j, BLUE)
                draw(alg)
                alg.markIndex(j, DEFAULT_MARK)
                alg.sort_start = time.time()
                # clock.tick(FPS)  # Control the speed of sorting
            alg.accesses += 2
            alg.comparisons += 1
    alg.sort_end = time.time()
    alg.calcSortDuration()

# Cocktail Shaker Sort function
def cocktail_shaker_sort(alg : SortAlg, draw, clock):
    n = alg.length
    swapped = True
    start = 0
    end = n - 1
    while swapped:
        swapped = False
        # Traverse from left to right
        for i in range(start, end):
            if alg.getArray()[i] > alg.getArray()[i + 1]:
                alg.getArray()[i], alg.getArray()[i + 1] = alg.getArray()[i + 1], alg.getArray()[i]
                alg.swaps += 1
                swapped = True
                alg.markIndex(i, BLUE)
                draw(alg)
                alg.markIndex(i, DEFAULT_MARK)
                # clock.tick(FPS)  # Control the speed of sorting
            alg.accesses += 2
            alg.comparisons += 1
        if not swapped:
            break
        swapped = False
        end -= 1
        # Traverse from right to left
        for i in range(end, start, -1):
            if alg.getArray()[i] < alg.getArray()[i - 1]:
                alg.getArray()[i], alg.getArray()[i - 1] = alg.getArray()[i - 1], alg.getArray()[i]
                alg.swaps += 1
                swapped = True
                alg.markIndex(i, BLUE)
                draw(alg)
                alg.markIndex(i, DEFAULT_MARK)
                # clock.tick(FPS)  # Control the speed of sorting
            alg.accesses += 2
            alg.comparisons += 1
        start += 1

def quick_sort(alg : SortAlg, draw, clock, low=0, high=None):
    if high is None:
        high = alg.length - 1  # Set default high value if not provided

    if low < high:
        pivot_index = partition(alg, low, high, draw, clock)
        alg.markIndex(pivot_index, BLUE)
        quick_sort(alg, draw, clock, low, pivot_index - 1)  # Left side
        quick_sort(alg, draw, clock, pivot_index + 1, high)  # Right side
        alg.markIndex(pivot_index, DEFAULT_MARK)

# Partition function
def partition(alg : SortAlg, low, high, draw, clock):
    pivot = alg.getArray()[high]
    i = low - 1
    for j in range(low, high):
        if alg.getArray()[j] <= pivot:
            i += 1
            alg.getArray()[i], alg.getArray()[j] = alg.getArray()[j], alg.getArray()[i]  # Swap
            draw(alg)  # Draw the array after each swap
            # clock.tick(FPS)  # Control the speed of the visualization
    alg.getArray()[i + 1], alg.getArray()[high] = alg.getArray()[high], alg.getArray()[i + 1]  # Swap pivot with arr[i + 1]
    draw(alg)  # Draw after the final swap
    # clock.tick(FPS)
    return i + 1