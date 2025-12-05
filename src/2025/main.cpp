// SPDX-FileCopyrightText: 2025 SternXD
// SPDX-License-Identifier: MIT

#include "common.h"
#include "day_1/day_1.h"
#include "day_2/day_2.h"
#include "day_3/day_3.h"
#include <iostream>
#include <string>
#include <map>
#include <functional>

void print_usage(const char* program_name) {
    std::cerr << "Usage: " << program_name << " <day_number>" << std::endl;
    std::cerr << "  or:  " << program_name << " -<day_number>" << std::endl;
    std::cerr << "  or:  " << program_name << " --day <day_number>" << std::endl;
    std::cerr << std::endl;
    std::cerr << "Examples:" << std::endl;
    std::cerr << "  " << program_name << " 1" << std::endl;
    std::cerr << "  " << program_name << " -2" << std::endl;
    std::cerr << "  " << program_name << " --day 1" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    int day_num = -1;
    std::string arg = argv[1];
    
    if (arg == "--day" && argc >= 3) {
        try {
            day_num = std::stoi(argv[2]);
        } catch (const std::exception&) {
            std::cerr << "Error: Invalid day number: " << argv[2] << std::endl;
            return 1;
        }
    } else if (arg[0] == '-') {
        // Handle -1, -2, etc.
        try {
            day_num = std::stoi(arg.substr(1));
        } catch (const std::exception&) {
            std::cerr << "Error: Invalid day number: " << arg << std::endl;
            return 1;
        }
    } else {
        try {
            day_num = std::stoi(arg);
        } catch (const std::exception&) {
            std::cerr << "Error: Invalid day number: " << arg << std::endl;
            return 1;
        }
    }
    
    std::map<int, std::function<void(Answer&)>> day_functions = {
        {1, run_day_1},
        {2, run_day_2},
        {3, run_day_3},
    };
    
    if (day_num < 1 || day_num > 25) {
        std::cerr << "Error: Day number must be between 1 and 25." << std::endl;
        return 1;
    }
    
    auto it = day_functions.find(day_num);
    if (it == day_functions.end()) {
        std::cerr << "Error: Day " << day_num << " is not implemented yet." << std::endl;
        return 1;
    }
    
    try {
        Answer answer;
        it->second(answer);
        answer.print();
        return 0;
    } catch (const RisError& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }
}

