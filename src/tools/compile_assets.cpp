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

#include <common/archives/psar_archive/psar_archive.hpp>
#include <common/extlibs/codec/codec.hpp>
#include <common/extlibs/json/json.hpp>
#include <common/utils/log/log.hpp>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string_view>
#include <vector>

namespace fs = std::filesystem;

common::extlibs::json _compile_assets(std::string_view path) {
    auto json = common::extlibs::json{};

    for (const auto &p : fs::directory_iterator(path)) {
        LOGI("  {}", p.path().c_str());
        if (p.is_directory()) {
            json[p.path().filename()] = _compile_assets(p.path().c_str());
        } else if (p.is_regular_file()) {
            if (p.path().extension() == ".json") {
                auto ifs = std::ifstream{p.path()};
                ifs >> json[p.path().filename()];
            } else {
                auto ifs = std::ifstream{p.path(), std::ios::binary};
                auto buffer = std::vector<std::uint8_t>{(std::istreambuf_iterator<char>(ifs)),
                                                        (std::istreambuf_iterator<char>())};
                json[p.path().filename()] = common::extlibs::codec::base64::encode(buffer);
            }
        }
    }

    return json;
}

int main(int argc, char *argv[]) {
    common::utils::log::init("compile_assets.log");

    LOGI("Compiling assets...");
    auto json = _compile_assets("assets");
    auto ofs = std::ofstream{"assets.psar", std::ios::binary};
    auto pa = common::archives::psar_archive{};
    pa.save(ofs, json);

    return 0;
}
