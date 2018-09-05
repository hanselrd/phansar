#include "psar_archive.hpp"
#include "../core/log.hpp"

namespace common {
namespace archives {
namespace psar_archive {
core::json load(std::istream &is) {
    auto j = core::json::from_cbor(is);
    LOGD << "Loaded " << core::json::to_cbor(j).size() << " bytes";
    return j;
}

void save(std::ostream &os, const core::json &j) {
    auto cbor = core::json::to_cbor(j);
    os.write(reinterpret_cast<const char *>(cbor.data()), cbor.size());
    LOGD << "Saved " << cbor.size() << " bytes";
}
} // namespace psar_archive
} // namespace archives
} // namespace common
