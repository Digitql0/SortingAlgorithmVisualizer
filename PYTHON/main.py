import pygame
import time
from sorts import *
from shared import *
from sort_algorithm import *

font = None

def drawText(algorithm):
    
    t_name = "Name: "
    t_time_complexity = "Time Complexity: "
    t_space_compexity = "Space Complexity: "
    t_num_elements = "Numbers: "
    t_visual_time = "Visual Time: "
    t_sort_time = "Sort Time: "
    t_comparions = "Comparisons: "
    t_swaps = "Swaps: "
    t_accesses = "Accesses: "
    t_writes = "Writes: "
    t_auxiliary_writes = "Writes To Auxiliary Array(s): "

    color = None
    if algorithm.checked == 0: color = DEFAULT_MARK
    elif algorithm.checked == 1: color = DEFAULT_SUCCESS
    else: color = DEFAULT_FAILURE

    t_name += algorithm.name

    t_time_complexity += algorithm.time_complexity

    t_space_compexity += algorithm.space_complexity

    t_num_elements += str(algorithm.length)

    if (algorithm.visual_start != None):
        duration = 0
        if (algorithm.visual_end == None): duration = time.time()
        else: duration = algorithm.visual_end
        duration -= algorithm.visual_start

        t_visual_time += str(duration)
    else:
        t_visual_time += str(0)
    
    t_sort_time += str(algorithm.sort_time)

    t_comparions += str(algorithm.comparisons)

    t_swaps += str(algorithm.swaps)
    
    t_accesses += str(algorithm.accesses)
    
    t_writes += str(algorithm.writes)
    
    t_auxiliary_writes += str(algorithm.auxiliary_writes)
    
    text_x = TEXT_PADDING[0]
    text_y = TEXT_PADDING[1]

    t_name = font.render(t_name, True, color)
    screen.blit(t_name, (text_x, text_y))
    text_y += FONT_SIZE + LINE_PADDING

    t_time_complexity = font.render(t_time_complexity, True, color)
    screen.blit(t_time_complexity, (text_x, text_y))
    text_y += FONT_SIZE + LINE_PADDING

    t_space_compexity = font.render(t_space_compexity, True, color)
    screen.blit(t_space_compexity, (text_x, text_y))
    text_y += FONT_SIZE + LINE_PADDING

    t_num_elements = font.render(t_num_elements, True, color)
    screen.blit(t_num_elements, (text_x, text_y))
    text_y += FONT_SIZE * 2 + LINE_PADDING

    t_visual_time = font.render(t_visual_time, True, color)
    screen.blit(t_visual_time, (text_x, text_y))
    text_y += FONT_SIZE + LINE_PADDING

    t_sort_time = font.render(t_sort_time, True, color)
    screen.blit(t_sort_time, (text_x, text_y))
    text_y += FONT_SIZE * 2 + LINE_PADDING

    t_swaps = font.render(t_swaps, True, color)
    screen.blit(t_swaps, (text_x, text_y))
    text_y += FONT_SIZE + LINE_PADDING

    t_comparions = font.render(t_comparions, True, color)
    screen.blit(t_comparions, (text_x, text_y))
    text_y += FONT_SIZE + LINE_PADDING

    t_accesses = font.render(t_accesses, True, color)
    screen.blit(t_accesses, (text_x, text_y))
    text_y += FONT_SIZE * 2 + LINE_PADDING

    t_writes = font.render(t_writes, True, color)
    screen.blit(t_writes, (text_x, text_y))
    text_y += FONT_SIZE + LINE_PADDING

    t_auxiliary_writes = font.render(t_auxiliary_writes, True, color)
    screen.blit(t_auxiliary_writes, (text_x, text_y))
    text_y += FONT_SIZE + LINE_PADDING

# Function to draw the array as bars
def draw(algorithm):
    arr_length = len(algorithm.getArray())
    screen.fill(BACKGROUND)

    drawText(algorithm)

    bar_width = (WIDTH / arr_length)

    for i, value in enumerate(algorithm.getArray()):
        # Scale the bar height to fit the screen
        rect_height = (value / arr_length) * HEIGHT
        col = algorithm.getMarkedIndex(i)
        pygame.draw.rect(screen, col, (i * bar_width, HEIGHT - rect_height, bar_width, rect_height))

    pygame.display.flip()

# Initialize pygame
pygame.init()

font = pygame.font.SysFont(None, FONT_SIZE)

# Main program to run the visualization
def main():
    # Create the pygame window
    global screen
    screen = pygame.display.set_mode((WIDTH, HEIGHT))
    pygame.display.set_caption("Bubble Sort Visualization")
    
    clock = pygame.time.Clock()

    bubble = SortAlg("Bubble Sort", "?", "?", bubble_sort, 200)
    cocktail_shaker = SortAlg("Cocktail Shaker Sort", "?", "?", cocktail_shaker_sort, 200)
    quick = SortAlg("Quick Sort", "?", "?", quick_sort, 200)
    
    bubble.run(draw, clock)
    cocktail_shaker.run(draw, clock)
    quick.run(draw, clock)

    # Keep the window open after sorting is complete
    done = False
    while not done:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True
    pygame.quit()

if __name__ == "__main__":
    main()
