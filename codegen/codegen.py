import cog
import dataclasses
import typing


def enum(name: str, constants: typing.List[str], pybind: bool = False) -> None:
    if pybind:
        cog.outl("namespace pybind {")
        cog.outl(f"inline void pybind_{name}(pybind11::module & _m) {{")
        cog.outl(f'    py::enum_<{name}>(_m, "{name}")')
        for index, constant in enumerate(constants):
            if index + 1 < len(constants):
                cog.outl(f'        .value("{constant}", {name}::{constant})')
            else:
                cog.outl(f'        .value("{constant}", {name}::{constant});')
        cog.outl("}")
        cog.outl("} // namespace pybind")


@dataclasses.dataclass
class StructField:
    name: str
    readonly: bool = False


def struct(
    name: str, type: str, fields: typing.List[StructField], pybind: bool = False
) -> None:
    if pybind:
        cog.outl("namespace pybind {")
        cog.outl(f"inline void pybind_{name}(pybind11::module & _m) {{")
        cog.outl(f'    py::class_<{type}>(_m, "{name}")')
        cog.outl(f"        .def(py::init<>())")
        for field in fields:
            cog.outl(
                f'        .def_read{"only" if field.readonly else "write"}("{field.name}", &{type}::{field.name})'
            )
        cog.outl(
            f"""        .def("__repr__", [](const {type} & _o) {{
            return fmt::format("<{name} object at {{}} with {{}} byte(s)>",
                               static_cast<const void *>(&_o),
                               sizeof(_o));
        }});"""
        )
        cog.outl("}")
        cog.outl("} // namespace pybind")


def struct_template(
    templates: typing.List[typing.Tuple[str, str]],
    fields: typing.List[StructField],
    pybind: bool = False,
) -> None:
    if pybind:
        for name, type in templates:
            struct(name, type, fields, pybind)


@dataclasses.dataclass
class ClassField:
    name: str
    readonly: bool = False


@dataclasses.dataclass
class ClassMethod:
    name: str
    args: typing.List[str] = dataclasses.field(default_factory=lambda: [])
    const: bool = False


def class_(
    name: str,
    type: str,
    constructors: typing.List[typing.List[str]],
    items: typing.List[typing.Union[ClassField, ClassMethod]],
    pybind: bool = False,
) -> None:
    if pybind:
        cog.outl("namespace pybind {")
        cog.outl(f"inline void pybind_{name}(pybind11::module & _m) {{")
        cog.outl(f'    py::class_<{type}>(_m, "{name}")')
        if len(constructors) == 0:
            cog.outl(f"        .def(py::init<>())")
        else:
            for constructor in constructors:
                cog.outl(f"        .def(py::init<{', '.join(constructor)}>())")
        for item in items:
            if isinstance(item, ClassField):
                cog.outl(
                    f'        .def_read{"only" if item.readonly else "write"}("{item.name}", &{type}::{item.name})'
                )
            elif isinstance(item, ClassMethod):
                cog.outl(
                    f'        .def("{item.name}", py::overload_cast<{", ".join(item.args)}>(&{type}::{item.name}{", py::const_" if item.const else ""}))'
                )
        cog.outl(
            f"""        .def("__repr__", [](const {type} & _o) {{
            return fmt::format("<{name} object at {{}} with {{}} byte(s)>",
                               static_cast<const void *>(&_o),
                               sizeof(_o));
        }});"""
        )
        cog.outl("}")
        cog.outl("} // namespace pybind")


def class_template(
    templates: typing.List[typing.Tuple[str, str]],
    constructors: typing.List[typing.List[str]],
    items: typing.List[typing.Union[ClassField, ClassMethod]],
    pybind: bool = False,
) -> None:
    if pybind:
        for name, type in templates:
            class_(name, type, constructors, items, pybind)
