#include <phansar/common/macros.hpp>

namespace phansar::_ {
enum class colors { white, black, red, blue, green, yellow, cyan, magenta, pink };

enum permissions { read, write, execute };

struct vec3 {
    float x, y, z;
};

struct material {
    PH_METADATA(readonly) vec3 ambient;
    PH_METADATA(readonly) vec3 diffuse;
    PH_METADATA(readonly) vec3 specular;
    float shininess;
};

class entity {
    PH_METADATA(readonly) std::uint32_t id;
    vec3 position;
};

class access {
public:
    int pub_x;

protected:
    int protected_x;

private:
    int private_x;
};
} // namespace phansar::_
