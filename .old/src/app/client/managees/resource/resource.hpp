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

#ifndef APP_CLIENT_MANAGEES_RESOURCE_RESOURCE_HPP
#define APP_CLIENT_MANAGEES_RESOURCE_RESOURCE_HPP

#include <memory>
#include <string_view>

namespace client {
namespace managees {
template <class T> class resource {
public:
    template <class... Args> void load(std::string_view path, Args &&... args);
    void store(std::shared_ptr<T> res);
    T *get() const;

private:
    std::shared_ptr<T> _res;
};
} // namespace managees
} // namespace client

#include "resource.tpp"

#endif
