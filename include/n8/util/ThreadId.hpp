/*
 * Copyright (c) 2024 - Nathanne Isip
 * This file is part of N8.
 * 
 * N8 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 * 
 * N8 is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with N8. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef N8_UTIL_THREAD_ID_HPP
#define N8_UTIL_THREAD_ID_HPP

#include <iomanip>
#include <sstream>
#include <thread>

namespace N8Util {

inline static std::string getThreadId(std::thread::id id) {
    std::ostringstream oss;
    oss << "0x" << std::hex << id;

    return oss.str();
}

};

#endif