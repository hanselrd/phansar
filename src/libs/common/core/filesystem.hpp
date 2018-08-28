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
