#include "json_archive.hpp"
#include "../core/log.hpp"

namespace common {
namespace archives {
namespace json_archive {
core::json load(std::istream &is) {
    auto j = core::json::parse(is);
    LOGD << "Loaded " << j.dump(4).size() << " characters";
    return j;
}

void save(std::ostream &os, const core::json &j) {
    os << j.dump(4);
    LOGD << "Saved " << j.dump(4).size() << " characters";
}
} // namespace json_archive
} // namespace archives
} // namespace common
