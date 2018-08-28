#include <common/core/core.hpp>
#include <common/scopes/scopes.hpp>
#include <cstdint>
#include <fstream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

using namespace common;
using namespace common::core;
namespace fs = common::core::filesystem;

json _compile_assets(const std::string &path) {
    json j;

    fs::directory dir(path);
    while (auto entry = dir.next_entry()) {
        auto name = entry->get_name();
        if (name == ".." || name == "." || name[0] == '.') {
            continue;
        }

        std::string extension = "";
        std::ifstream ifs;
        std::streampos fsize;

        switch (entry->get_type()) {
        case fs::directory_entry::type::DIRECTORY:
            LOGI << "[" << entry->get_name() << "]";

            j[entry->get_name()] = _compile_assets(path + P_DIR_SEPARATOR + entry->get_name());
            break;
        case fs::directory_entry::type::FILE:
            LOGI << "  Found: " << entry->get_name();

            extension = (entry->get_name().find_last_of('.') != std::string::npos)
                            ? entry->get_name().substr(entry->get_name().find_last_of('.') + 1)
                            : "";

            if (extension == "json") {
                ifs.open(path + P_DIR_SEPARATOR + entry->get_name());

                ifs >> j[entry->get_name()];
            } else {
                ifs.open(path + P_DIR_SEPARATOR + entry->get_name(), std::ios::binary);

                std::vector<std::uint8_t> buffer((std::istreambuf_iterator<char>(ifs)),
                                                 (std::istreambuf_iterator<char>()));

                j[entry->get_name()] = codec::base64::encode(buffer);
            }

            ifs.seekg(0, std::ios::beg);
            fsize = ifs.tellg();
            ifs.seekg(0, std::ios::end);
            fsize = ifs.tellg() - fsize;

            LOGI << "    size: " << fsize << " B";
            break;
        default:
            ASSERT(0);
        }
    }

    return j;
}

int main(int argc, char *argv[]) {
    log::init("compile_assets.log");

    scopes::plibsys guard;

    LOGI << "Compiling assets...";
    auto j = _compile_assets("assets");
    std::ofstream ofs("assets.psar", std::ios::binary);
    auto cbor = json::to_cbor(j);
    ofs.write(reinterpret_cast<const char *>(cbor.data()), cbor.size());
    LOGI << "Compiled " << cbor.size() << " B";

    return 0;
}
