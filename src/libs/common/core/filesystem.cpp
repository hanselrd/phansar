#include "filesystem.hpp"

namespace common {
namespace core {
namespace filesystem {
file::file(const std::string &path) : _path(path) {
}

bool file::exists() const {
    return p_file_is_exists(_path.c_str());
}

bool file::remove() {
    return p_file_remove(_path.c_str(), nullptr);
}

directory_entry::directory_entry(const std::string &name, const directory_entry::type t)
    : _name(name), _type(t) {
}

const std::string &directory_entry::get_name() const {
    return _name;
}

directory_entry::type directory_entry::get_type() const {
    return _type;
}

directory::directory(const std::string &path)
    : _dir(p_dir_new(path.c_str(), nullptr), &p_dir_free), _path(path) {
}

bool directory::exists() const {
    return p_dir_is_exists(_path.c_str());
}

bool directory::remove() {
    return p_dir_remove(_path.c_str(), nullptr);
}

const std::string &directory::get_path() const {
    return _path;
}

std::shared_ptr<directory_entry> directory::next_entry() {
    auto entry = p_dir_get_next_entry(_dir.get(), nullptr);
    if (entry == nullptr) {
        return std::shared_ptr<directory_entry>();
    }

    auto dir_entry = std::make_shared<directory_entry>(
        entry->name, static_cast<directory_entry::type>(entry->type));

    p_dir_entry_free(entry);

    return dir_entry;
}

bool directory::rewind() {
    return p_dir_rewind(_dir.get(), nullptr);
}
} // namespace filesystem
} // namespace core
} // namespace common
