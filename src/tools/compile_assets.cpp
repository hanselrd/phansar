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

#include <common/archives/archives.hpp>
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

    scopes::plibsys_scope guard;

    LOGI << "Compiling assets...";
    auto j = _compile_assets("assets");
    std::ofstream ofs("assets.psar", std::ios::binary);
    archives::psar_archive pa;
    pa.save(ofs, j);

    return 0;
}
