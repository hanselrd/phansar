#ifndef COMMON_ARCHIVES_PSAR_ARCHIVE_HPP
#define COMMON_ARCHIVES_PSAR_ARCHIVE_HPP

#include "../core/json.hpp"
#include <iostream>

namespace common {
namespace archives {
namespace psar_archive {
core::json load(std::istream &is);
void save(std::ostream &os, const core::json &j);
} // namespace psar_archive
} // namespace archives
} // namespace common

#endif
