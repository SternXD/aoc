cmake_minimum_required(VERSION 3.10)
project(AdventOfCode)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find all year directories and add them as subdirectories
file(GLOB year_dirs LIST_DIRECTORIES true "src/*")
list(FILTER year_dirs INCLUDE REGEX "src/[0-9]+$")

foreach(year_path IN LISTS year_dirs)
    get_filename_component(year_dir ${year_path} NAME)
    set(year_cmake "${year_path}/CMakeLists.txt")
    
    # Check if CMakeLists.txt exists for this year
    if(EXISTS "${year_cmake}")
        add_subdirectory(${year_path} ${year_dir})
    else()
        message(WARNING "Year ${year_dir} does not have a CMakeLists.txt file at ${year_cmake}")
    endif()
endforeach()
