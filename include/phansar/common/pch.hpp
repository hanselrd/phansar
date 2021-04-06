#ifndef PHANSAR_COMMON_PCH_HPP
#define PHANSAR_COMMON_PCH_HPP

#include <algorithm>
#include <any>
#include <array>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <filesystem>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <random>
#include <ratio>
#include <regex>
#include <shared_mutex>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>
#include <version>

#ifdef __has_include
#    if __has_include(<experimental/propagate_const>)
#        include <experimental/propagate_const>
#    endif
#endif

#endif
