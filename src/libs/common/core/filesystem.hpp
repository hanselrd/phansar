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

#ifndef COMMON_CORE_FILESYSTEM_HPP
#define COMMON_CORE_FILESYSTEM_HPP

#include <memory>
#include <plibsys.h>
#include <string>

namespace common {
namespace core {
namespace filesystem {
class file {
public:
    explicit file(const std::string &path);

    bool exists() const;
    bool remove();

private:
    std::string _path;
};

class directory_entry {
public:
    enum class type { DIRECTORY = 1, FILE, OTHER };

    explicit directory_entry(const std::string &name, const type t);

    const std::string &get_name() const;
    type get_type() const;

private:
    std::string _name;
    type _type;
};

class directory {
public:
    explicit directory(const std::string &path);

    bool exists() const;
    bool remove();
    const std::string &get_path() const;
    std::shared_ptr<directory_entry> next_entry();
    bool rewind();

private:
    std::shared_ptr<PDir> _dir;
    std::string _path;
};
} // namespace filesystem
} // namespace core
} // namespace common

#endif
