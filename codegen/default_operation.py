from __future__ import annotations
import cog
import enum
import typing


class DefaultOperation(enum.Enum):
    CONSTRUCTOR = enum.auto()
    COPY_CONSTRUCTOR = enum.auto()
    COPY_ASSIGNMENT = enum.auto()
    MOVE_CONSTRUCTOR = enum.auto()
    MOVE_ASSIGNMENT = enum.auto()
    DESTRUCTOR = enum.auto()


def declarations(
    name: str,
    constructor: bool = True,
    copy_constructor: bool = True,
    copy_assignment: bool = True,
    move_constructor: bool = True,
    move_assignment: bool = True,
    destructor: bool = True,
) -> None:
    output = ""
    output += "    // NOLINTBEGIN\n"
    output += "    // clang-format off\n"

    if constructor:
        output += f"    {name}();\n"
    if copy_constructor:
        output += f"    {name}(const {name} & _other);\n"
    if copy_assignment:
        output += f"    auto operator=(const {name} & _other) -> {name} &;\n"
    if move_constructor:
        output += f"    {name}({name} && _other) noexcept;\n"
    if move_assignment:
        output += f"    auto operator=({name} && _other) noexcept -> {name} &;\n"
    if destructor:
        output += f"    virtual ~{name}();\n"

    output += "    // clang-format on\n"
    output += "    // NOLINTEND"

    cog.outl(output)


def definition(
    name: str,
    default_operation: DefaultOperation,
    qualified_name: typing.Optional[str] = None,
    templates: typing.Optional[typing.List[str]] = None,
) -> None:
    output = ""
    output += "// NOLINTBEGIN\n"
    output += "// clang-format off\n"

    _name = qualified_name if qualified_name is not None else name

    for template in templates:
        output += f"{template}\n"

    if default_operation == DefaultOperation.CONSTRUCTOR:
        output += f"{_name}::{name}()\n"
    if default_operation == DefaultOperation.COPY_CONSTRUCTOR:
        output += f"{_name}::{name}(const {name} & _other)\n"
    if default_operation == DefaultOperation.COPY_ASSIGNMENT:
        output += f"auto {_name}::operator=(const {name} & _other) -> {_name} &\n"
    if default_operation == DefaultOperation.MOVE_CONSTRUCTOR:
        output += f"{_name}::{name}({name} && _other) noexcept\n"
    if default_operation == DefaultOperation.MOVE_ASSIGNMENT:
        output += f"auto {_name}::operator=({name} && _other) noexcept -> {_name} &\n"
    if default_operation == DefaultOperation.DESTRUCTOR:
        output += f"{_name}::~{name}()\n"

    output += "// clang-format on\n"
    output += "// NOLINTEND"

    cog.outl(output)
