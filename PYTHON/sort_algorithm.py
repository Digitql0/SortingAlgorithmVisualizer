import random
import time
from shared import *

class SortAlg:
    def __init__(self, _name, tcomp, scomp, sort_func, num_elements):
        self.name = _name
        self.time_complexity = tcomp
        self.space_complexity = scomp
        self.func = sort_func
        self.length = num_elements
        self.arr = []
        self.arr_hashmap = {}
        self.visual_start = None
        self.visual_end = None
        self.sort_start = None
        self.sort_end = None
        self.sort_time = 0
        self.comparisons = 0
        self.swaps = 0
        self.accesses = 0
        self.writes = 0
        self.auxiliary_writes = 0
        self.checked = 0
        self.shuffleArray()

    def __makeArray(self):
        self.arr = list(range(1, self.length + 1))

    def calcSortDuration(self):
        self.sort_time = self.sort_end - self.sort_start

    def shuffleArray(self):
        if (len(self.arr) <= self.length): 
            self.__makeArray()
            print("arr shuffled")
        
        random.shuffle(self.arr)

    def markIndex(self, index, col):
        self.arr_hashmap[index] = col

    def getMarkedIndex(self, index):
        if index in self.arr_hashmap:
            return self.arr_hashmap[index]
        else:
            return DEFAULT_MARK

    def clearMarks(self):
        keys = list(self.arr_hashmap.keys())
        for key in keys:
            del self.arr_hashmap[key]

    def getArray(self):
        return self.arr
    
    def checkArray(self, draw):
        if len(self.arr) == 0:
            self.shuffleArray

        i = 0
        max = 0
        while i < self.length:
            if i == 0:
                max = self.arr[0]
                self.markIndex(i, DEFAULT_SUCCESS)
                draw(self)
            elif self.arr[i] >= max: # arr up to index is sorted
                max = self.arr[i]
                self.markIndex(i, DEFAULT_SUCCESS)
                draw(self)
            else:
                self.markIndex(i, DEFAULT_FAILURE)
                draw(self)
                break
            i += 1
        if i >= self.length: self.checked = 1
        else: self.checked = 2
        draw(self)

    def run(self, draw, clock):
        draw(self)
        time.sleep(1)
        self.visual_start = time.time()
        self.func(self, draw, clock)
        self.visual_end = time.time()
        self.clearMarks()
        draw(self)
        self.checkArray(draw)
        time.sleep(2)