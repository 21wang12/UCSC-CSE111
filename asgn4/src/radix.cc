/*
 * Copyright (C) 2018-2022 David C. Harrison. All rights reserved.
 *
 * You may not use, distribute, publish, or modify this code without 
 * the express written permission of the copyright holder.
 */
#include <iostream>
#include <thread>
#include <mutex>
#include "radix.h"

void ParallelRadixSort::msd(std::vector<std::reference_wrapper<std::vector<unsigned int>>> &lists, unsigned int cores) {
    std::cout << cores << std::endl;
    std::cout << "hello world" << std::endl;
    // ============================================================================= //
    // Step1 : Calculate k
    // ============================================================================= //
}