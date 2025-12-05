// SPDX-FileCopyrightText: 2025 SternXD
// SPDX-License-Identifier: MIT

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "common.h"
#include <fstream>
#include <sstream>
#include <cstdlib>

std::string read_puzzle_input(const std::string& key) {
    std::string filename = key;
    std::vector<std::string> possible_paths;
    
    // First, check for environment variable specifying input directory
    const char* input_dir = std::getenv("AOC_INPUT_DIR");
    if (input_dir != nullptr) {
        std::string dir(input_dir);
        // Ensure directory path ends with separator
        if (!dir.empty() && dir.back() != '/' && dir.back() != '\\') {
            dir += "/";
        }
        possible_paths.push_back(dir + filename);
    }
    
    // Also check AOC_INPUT_PATH for a direct path
    const char* input_path = std::getenv("AOC_INPUT_PATH");
    if (input_path != nullptr) {
        std::string path(input_path);
        // Ensure path ends with separator
        if (!path.empty() && path.back() != '/' && path.back() != '\\') {
            path += "/";
        }
        possible_paths.push_back(path + filename);
    }
    
    std::string puzzle_input_folder = "puzzle_input/2025/";
    possible_paths.insert(possible_paths.end(), {
        puzzle_input_folder + filename,
        "../" + puzzle_input_folder + filename,
        "../../" + puzzle_input_folder + filename,
        "../../../" + puzzle_input_folder + filename,
        "../../../../" + puzzle_input_folder + filename
    });
    
    for (const auto& path : possible_paths) {
        std::ifstream file(path);
        if (file.is_open()) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            return buffer.str();
        }
    }
    
    std::string error_msg = "Could not find puzzle input file: " + filename;
    error_msg += "\nSearched in: puzzle_input/2025/";
    if (input_dir != nullptr || input_path != nullptr) {
        error_msg += "\nAlso checked: ";
        if (input_dir != nullptr) error_msg += std::string(input_dir) + "/";
        if (input_path != nullptr) error_msg += std::string(input_path) + "/";
    }
    error_msg += "\nYou can set AOC_INPUT_DIR or AOC_INPUT_PATH environment variable to specify input directory.";
    throw RisError(error_msg);
}

