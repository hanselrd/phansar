#include <phansar/vendor/hedley.hpp>

#if HEDLEY_HAS_ATTRIBUTE(annotate)
#    define PH_ANNOTATE(...) __attribute__((annotate(#    __VA_ARGS__)))
#else
#    define PH_ANNOTATE(...)
#endif

#define PH_METADATA(...) PH_ANNOTATE(phansar, metadata, __VA_ARGS__)

namespace phansar::unittest {
enum class colors { white, black, red, blue, green, yellow, cyan, magenta, pink };

/* enum permissions { read, write, execute }; */

struct vec3 {
    float x, y, z;
};

auto g_k = []() { return 1; };

/* struct material { */
/*     PH_METADATA(readonly) vec3 ambient; */
/*     PH_METADATA(readonly) vec3 diffuse; */
/*     PH_METADATA(readonly) vec3 specular; */
/*     float shininess; */
/* }; */

/* class entity { */
/*     PH_METADATA(readonly) std::uint32_t id; */
/*     vec3 position; */
/* }; */

/* class access { */
/* public: */
/*     int pub_x; */

/* protected: */
/*     int protected_x; */

/* private: */
/*     int private_x; */
/* }; */

} // namespace phansar::unittest
