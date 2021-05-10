#include <phansar/common/bindings.hpp>
#include <phansar/common/helpers.hpp>
#include <phansar/vendor/fmt.hpp>
#include <phansar/vendor/rangev3.hpp>

namespace phansar::common::bindings {
rttr_visitor::rttr_visitor(py::module & _module) : m_module{_module} {}
} // namespace phansar::common::bindings

namespace rttr {
void to_json(nlohmann::ordered_json & _json, const instance & _obj) {
    const auto write = phansar::common::helpers::y_combinator(
        [](auto &&                                             _write,
           const std::variant<rttr::instance, rttr::variant> & _v,
           nlohmann::ordered_json &                            _json) -> void {
            if (std::holds_alternative<rttr::instance>(_v)) {
                auto obj = std::get<rttr::instance>(_v).get_type().get_raw_type().is_wrapper()
                               ? std::get<rttr::instance>(_v).get_wrapped_instance()
                               : std::get<rttr::instance>(_v);

                for (const auto & prop : obj.get_derived_type().get_properties()) {
                    if (prop.get_metadata("no_serialize")) {
                        continue;
                    }

                    auto var = prop.get_value(std::get<rttr::instance>(_v));
                    if (! var) {
                        continue;
                    }

                    _write(var, _json[std::string{prop.get_name()}]);
                }

                for (const auto & meth : obj.get_derived_type().get_methods()) {
                    if (meth.get_metadata("no_serialize")) {
                        continue;
                    }

                    if (! meth.get_metadata("arguments")) {
                        continue;
                    }

                    auto args = meth.get_metadata("arguments")
                                    .get_value<std::map<std::string, std::vector<rttr::variant>>>();
                    for (const auto & item : args) {
                        _write(meth.invoke_variadic(obj,
                                                    item.second |
                                                        ranges::to<std::vector<rttr::argument>>()),
                               _json[fmt::format("{}s", std::string{meth.get_name()})][item.first]);
                    }
                }
            } else if (std::holds_alternative<rttr::variant>(_v)) {
                const auto & var = std::get<rttr::variant>(_v);
                if (var.get_type().is_arithmetic()) {
                    if (var.get_type() == rttr::type::get<bool>()) {
                        _json = var.to_bool();
                    } else if (var.get_type() == rttr::type::get<uint8_t>()) {
                        _json = var.to_uint8();
                    } else if (var.get_type() == rttr::type::get<uint16_t>()) {
                        _json = var.to_uint16();
                    } else if (var.get_type() == rttr::type::get<uint32_t>()) {
                        _json = var.to_uint32();
                    } else if (var.get_type() == rttr::type::get<uint64_t>()) {
                        _json = var.to_uint64();
                    } else if (var.get_type() == rttr::type::get<int8_t>()) {
                        _json = var.to_int8();
                    } else if (var.get_type() == rttr::type::get<int16_t>()) {
                        _json = var.to_int16();
                    } else if (var.get_type() == rttr::type::get<int32_t>()) {
                        _json = var.to_int32();
                    } else if (var.get_type() == rttr::type::get<int64_t>()) {
                        _json = var.to_int64();
                    } else if (var.get_type() == rttr::type::get<float>() ||
                               var.get_type() == rttr::type::get<double>() ||
                               var.get_type() == rttr::type::get<long double>()) {
                        _json = var.to_double();
                    }
                } else if (var.get_type().is_enumeration()) {
                    _json = var.to_string();
                } else if (var.get_type() == rttr::type::get<std::string>()) {
                    _json = var.to_string();
                } else if (var.is_sequential_container()) {
                    _json = nlohmann::ordered_json{};
                    for (const auto & item : var.create_sequential_view()) {
                        _json.push_back(nullptr);
                        _write(item.extract_wrapped_value(), _json.back());
                    }
                } else if (var.is_associative_container()) {
                    auto view = var.create_associative_view();
                    _json     = nlohmann::ordered_json{};
                    for (const auto & item : view) {
                        if (view.is_key_only_type()) {
                            _json.push_back(nullptr);
                            _write(item.first.extract_wrapped_value(), _json.back());
                        } else {
                            _write(item.second.extract_wrapped_value(),
                                   _json[item.first.extract_wrapped_value().to_string()]);
                        }
                    }
                } else if (auto type = var.get_type().is_wrapper()
                                           ? var.get_type().get_wrapped_type()
                                           : var.get_type();
                           ! type.get_properties().empty()) {
                    auto obj = var.get_type().get_raw_type().is_wrapper()
                                   ? rttr::instance{var}.get_wrapped_instance()
                                   : rttr::instance{var};
                    _write(obj, _json);
                }
            }
        });

    write(_obj, _json);
}
} // namespace rttr
