cmake_minimum_required(VERSION 3.10)
project(SortingAlgorithmVisualizer LANGUAGES C CXX)

# Add the Debug Options
option(DEBUG "Enable debug features and tools" OFF)

# Set Compile Standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

# What happens if Debug is enabled
if(DEBUG)
    message(STATUS "Debug mode enabled: adding debug flags and sanitizers")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)

    # HERE ADD DEBUG OPTIONS

    # SANITIZERS
    # add_compile_options(-g -O0 -Wall -Wextra -Wpedantic)
    # add_link_options(-fsanitize=address,undefined)

    # VALGRIND (cmake --build . --run_valgrind)
    # add_custom_target(run_valgrind
    #     COMMAND valgrind --leak-check=full --track-origins=yes $<TARGET_FILE:${PROJECT_NAME}App>
    #     DEPENDS ${PROJECT_NAME}App
    #     COMMENT "Running ${PROJECT_NAME}App under Valgrind"
    # )

endif()

# External Libraries
# add_subdirectory(external/OTHERLIB)
# add_subdirectory(external/OTHERLIB)

# Collect sources
file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.c
)
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# Build as a static library
add_library(${PROJECT_NAME} STATIC ${LIB_SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
# target_link_libraries(${PROJECT_NAME} PUBLIC OTHERLIB)
# target_link_libraries(${PROJECT_NAME} PUBLIC OTHERLIB)

# External Packages
find_package(raylib REQUIRED)
# find_package(secondPackage REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC raylib)

set(APP_SOURCES src/main.cpp)

# Build as an Executable
add_executable(${PROJECT_NAME}App ${APP_SOURCES})
target_link_libraries(${PROJECT_NAME}App PRIVATE ${PROJECT_NAME})

#Summary
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Debug mode: ${DEBUG}")
