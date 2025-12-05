# Get the year from the directory name
get_filename_component(YEAR ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Common utilities library for this year
add_library(aoc_common_${YEAR}
    common.cpp
)

target_include_directories(aoc_common_${YEAR} PUBLIC .)

# Find all day directories
file(GLOB day_dirs LIST_DIRECTORIES true "day_*")
list(FILTER day_dirs INCLUDE REGEX "day_[0-9]+$")
message(STATUS "Found day directories: ${day_dirs}")

# Collect all day source files
set(day_sources "")
foreach(day_path IN LISTS day_dirs)
    get_filename_component(day_dir ${day_path} NAME)
    set(day_cpp "${day_path}/${day_dir}.cpp")
    if(EXISTS "${day_cpp}")
        list(APPEND day_sources "${day_cpp}")
        message(STATUS "Found day source: ${day_cpp}")
    else()
        message(WARNING "Day source file not found: ${day_cpp}")
    endif()
endforeach()

add_executable(aoc${YEAR}
    main.cpp
    ${day_sources}
)

target_include_directories(aoc${YEAR} PRIVATE
    .
)

foreach(day_path IN LISTS day_dirs)
    target_include_directories(aoc${YEAR} PRIVATE ${day_path})
endforeach()

target_link_libraries(aoc${YEAR} aoc_common_${YEAR})
