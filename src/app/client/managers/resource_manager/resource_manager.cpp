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

#include "resource_manager.hpp"
#include <common/archives/psar_archive/psar_archive.hpp>
#include <common/extlibs/codec/codec.hpp>
#include <common/utils/assert/assert.hpp>
#include <common/utils/log/log.hpp>
#include <fstream>
#include <string>
#include <unordered_map>

namespace client {
namespace managers {
namespace resource_manager {
namespace {
auto _json = common::extlibs::json{};
auto _cache =
    std::unordered_map<std::string, std::pair<detail::resource_type, std::shared_ptr<void>>>{};

void _load() {
    if (!_json.is_null()) {
        return;
    }

    auto ifs = std::ifstream{"assets.psar", std::ios::binary};
    auto pa = common::archives::psar_archive{};
    _json = pa.load(ifs).flatten();
}

std::vector<std::uint8_t> _get_bytes(std::string_view path) {
    _load();
    auto bytes =
        common::extlibs::codec::base64::decode(_json[std::string{path}].get<std::string>());
    LOGD << path << ": " << bytes.size() << " bytes";
    return bytes;
}

common::extlibs::json _get_json(std::string_view path) {
    _load();
    auto json = _json[std::string{path}];
    LOGD << path << ": " << json.dump(4) << " characters";
    return json;
}
} // namespace

namespace detail {
void load(std::string_view path, resource_type rt) {
    if (_cache.count(std::string{path}) > 0) {
        LOGW << path << " has already been loaded";
        return;
    }

    auto ptr = std::shared_ptr<void>{};

    switch (rt) {
    case resource_type::JSON:
        ptr = std::make_shared<common::extlibs::json>(_get_json(path));
        break;
    case resource_type::SDL_SURFACE: {
        auto bytes = _get_bytes(path);
        auto rw = SDL_RWFromConstMem(bytes.data(), bytes.size());
        ptr = std::shared_ptr<SDL_Surface>{IMG_Load_RW(rw, true), &SDL_FreeSurface};
        ASSERT(ptr);
    } break;
    case resource_type::MIX_MUSIC:
    case resource_type::TTF_FONT:
        ASSERT(0);
        break;
    }

    _cache[std::string{path}] = std::make_pair(rt, ptr);
}

std::shared_ptr<void> get(std::string_view path, resource_type rt) {
    if (_cache.count(std::string{path}) == 0) {
        load(path, rt);
    }

    auto res = _cache[std::string{path}];
    if (res.first == rt) {
        return res.second;
    }

    return std::shared_ptr<void>{};
}
} // namespace detail
} // namespace resource_manager
} // namespace managers
} // namespace client
