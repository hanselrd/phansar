/**
 * This file is part of Phansar.
 *
 * Copyright (C) 2018  Hansel De La Cruz
 *
 * Phansar is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Phansar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COMMON_CORE_ASSERT_HPP
#define COMMON_CORE_ASSERT_HPP

#include "log.hpp"
#include <cstdlib>
#include <stdexcept>

#ifndef NDEBUG
#    define TERMINATE(message) std::terminate()
#else
#    define TERMINATE(message) throw std::runtime_error(message)
#endif

#define MASSERT_ALWAYS(condition, message)                                                         \
    [&] {                                                                                          \
        if (!(condition)) {                                                                        \
            LOGF << "Assertion `" #condition "' failed [" << message << "]";                       \
            TERMINATE(message);                                                                    \
        }                                                                                          \
    }()

#define MASSERT_ALWAYS_IF(enable, condition, message)                                              \
    [&] {                                                                                          \
        if (enable) {                                                                              \
            MASSERT_ALWAYS(condition, message);                                                    \
        }                                                                                          \
    }()

#define ASSERT_ALWAYS(condition)                                                                   \
    [&] {                                                                                          \
        if (!(condition)) {                                                                        \
            LOGF << "Assertion `" #condition "' failed";                                           \
            TERMINATE("");                                                                         \
        }                                                                                          \
    }()

#define ASSERT_ALWAYS_IF(enable, condition)                                                        \
    [&] {                                                                                          \
        if (enable) {                                                                              \
            ASSERT_ALWAYS(condition);                                                              \
        }                                                                                          \
    }()

#ifndef NDEBUG
#    define MASSERT(condition, message) MASSERT_ALWAYS(condition, message)
#    define MASSERT_IF(enable, condition, message) MASSERT_ALWAYS_IF(enable, condition, message)
#    define ASSERT(condition) ASSERT_ALWAYS(condition)
#    define ASSERT_IF(enable, condition) ASSERT_ALWAYS_IF(enable, condition)
#else
#    define MASSERT(ignore1, ignore2) ((void)0)
#    define MASSERT_IF(ignore1, ignore2, ignore3) ((void)0)
#    define ASSERT(ignore1) ((void)0)
#    define ASSERT_IF(ignore1, ignore2) ((void)0)
#endif

#ifndef NDEBUG
#    define EXPECT_TRUE(condition)                                                                 \
        [&] {                                                                                      \
            if (!(condition)) {                                                                    \
                LOGW << "Expected `" #condition "' to be true";                                    \
            }                                                                                      \
            return condition;                                                                      \
        }()

#    define EXPECT_FALSE(condition)                                                                \
        [&] {                                                                                      \
            if (condition) {                                                                       \
                LOGW << "Expected `" #condition "' to be false";                                   \
            }                                                                                      \
            return condition;                                                                      \
        }()
#else
#    define EXPECT_TRUE(condition) (condition)
#    define EXPECT_FALSE(condition) (condition)
#endif

#ifndef NDEBUG
#    define UNUSED_ARG(arg)                                                                        \
        [&] {                                                                                      \
            LOGW << "Unused argument `" #arg "'";                                                  \
            (void)arg;                                                                             \
        }()
#else
#    define UNUSED_ARG(arg) ((void)arg)
#endif

#endif
