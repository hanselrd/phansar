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
#include <common/archives/psar_archive.hpp>
#include <common/core/assert.hpp>
#include <common/core/codec.hpp>
#include <common/core/log.hpp>
#include <fstream>
#include <unordered_map>

namespace client {
namespace managers {
namespace resource_manager {
namespace {
common::core::json _json;
std::unordered_map<std::string, std::pair<internal::resource_type, std::shared_ptr<void>>> _cache;

void _load() {
    if (!_json.is_null()) {
        return;
    }

    std::ifstream ifs("assets.psar", std::ios::binary);
    common::archives::psar_archive pa;
    _json = pa.load(ifs).flatten();
}

std::vector<std::uint8_t> _get_bytes(const std::string &path) {
    _load();
    auto bytes = common::core::codec::base64::decode(_json[path].get<std::string>());
    LOGD << path << ": " << bytes.size() << " bytes";
    return bytes;
}

common::core::json _get_json(const std::string &path) {
    _load();
    auto json = _json[path];
    LOGD << path << ": " << json.dump(4) << " characters";
    return json;
}
} // namespace

namespace internal {
void load(const std::string &path, resource_type rt) {
    if (_cache.count(path) > 0) {
        LOGW << path << " has already been loaded";
        return;
    }

    std::shared_ptr<void> ptr;

    switch (rt) {
    case resource_type::JSON:
        ptr = std::make_shared<common::core::json>(_get_json(path));
        break;
    case resource_type::SDL_SURFACE: {
        auto bytes = _get_bytes(path);
        auto rw = SDL_RWFromConstMem(bytes.data(), bytes.size());
        ptr = std::shared_ptr<SDL_Surface>(IMG_Load_RW(rw, true), &SDL_FreeSurface);
        ASSERT(ptr);
    } break;
    case resource_type::MIX_MUSIC:
    case resource_type::TTF_FONT:
        ASSERT(0);
        break;
    }

    _cache[path] = std::make_pair(rt, ptr);
}

std::shared_ptr<void> get(const std::string &path, resource_type rt) {
    if (_cache.count(path) == 0) {
        load(path, rt);
    }

    auto res = _cache[path];
    if (res.first == rt) {
        return res.second;
    }

    return std::shared_ptr<void>();
}
} // namespace internal
} // namespace resource_manager
} // namespace managers
} // namespace client
