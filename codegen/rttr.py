from __future__ import annotations
import abc
import cog
import dataclasses
import mako.template
import re
import textwrap
import typing

T = typing.TypeVar("T")


class Builder(typing.Generic[T]):
    def __init__(self) -> None:
        self._draft = {}

    def __getattr__(self, item: str) -> typing.Callable[[typing.Any], Builder[T]]:
        _T = typing.get_args(self.__orig_class__)[0]

        try:
            field = [field for field in dataclasses.fields(_T) if field.name == item][0]

            def builder(value: field.type) -> Builder[T]:
                self._draft[field.name] = value
                return self

            return builder
        except IndexError:
            raise RuntimeError(f"'{item}' was not found in {_T}")

    def build(self) -> T:
        _T = typing.get_args(self.__orig_class__)[0]

        obj = _T(**self._draft)
        self._draft.clear()

        return obj


def builder(cls: typing.Type[T]) -> typing.Type[T]:
    def builder() -> Builder[typing.Type[T]]:
        return Builder[cls]()

    setattr(cls, "builder", builder)
    return cls


@builder
@dataclasses.dataclass
class RttrMethod:
    @builder
    @dataclasses.dataclass
    class Overload:
        return_type: typing.Optional[str] = None
        args: typing.List[str] = dataclasses.field(default_factory=lambda: [])

    name: str
    namespace: typing.Optional[str] = None
    overloads: typing.List[Overload] = dataclasses.field(default_factory=lambda: [])
    child: bool = False

    def __str__(self) -> str:
        return re.sub(
            r"\)\s*;$",
            ");",
            re.sub(
                r"(\n\s*\n)+",
                "\n",
                mako.template.Template(
                    textwrap.dedent(
                        """\
                        <%
                            qualified = f"{f'{data.namespace}::' if data.namespace is not None else ''}"
                            qualified_name = f"{qualified}{data.name}"
                        %>
                        % if len(data.overloads) != 0:
                            % for index, overload in enumerate(data.overloads):
                                <%
                                    select_overload = f"rttr::select_overload<{overload.return_type}({', '.join(overload.args)})>(&{qualified_name})"
                                %>
                                % if not data.child and index == 0:
                            rttr::registration::method("${data.name}", ${select_overload})
                                % else:
                                .method("${data.name}", ${select_overload})
                                % endif
                            % endfor
                        % else:
                            %if not data.child:
                            rttr::registration::method("${data.name}", &${qualified_name})
                            % else:
                                .method("${data.name}", &${qualified_name})
                            % endif
                        % endif
                        % if not data.child:
                                ;
                        % endif
                        """
                    )
                ).render(data=self),
            ).lstrip("\n"),
        )


@builder
@dataclasses.dataclass
class RttrProperty:
    Accessor = typing.NewType("Accessor", str)
    Getter = typing.NewType("Getter", str)
    Setter = typing.NewType("Setter", str)

    name: str
    namespace: typing.Optional[str] = None
    getter: typing.Optional[Getter] = None
    setter: typing.Optional[Setter] = None
    readonly: bool = False
    child: bool = False

    def __str__(self) -> str:
        if self.getter is None and self.setter is not None:
            raise RuntimeError("Cannot specify setter without a getter")

        return re.sub(
            r"\)\s*;$",
            ");",
            re.sub(
                r"(\n\s*\n)+",
                "\n",
                mako.template.Template(
                    textwrap.dedent(
                        """\
                        <%
                            qualified = f"{f'{data.namespace}::' if data.namespace is not None else ''}"
                            qualified_name = f"{qualified}{data.name}"
                            qualified_getter = f"{qualified}{data.getter}"
                            qualified_setter = f"{qualified}{data.setter}"
                        %>
                        % if data.getter is None and data.setter is None:
                            <%
                                property_type = f"property{'_readonly' if data.readonly else ''}"
                            %>
                            % if not data.child:
                            rttr::registration::${property_type}("${data.name}", &${qualified_name})
                            % else:
                                .${property_type}("${data.name}", &${qualified_name})
                            % endif
                        % elif data.getter is not None and data.setter is None:
                            % if not data.child:
                            rttr::registration::property_readonly("${data.name}", &${qualified_getter})
                            % else:
                                .property_readonly("${data.name}", &${qualified_getter})
                            % endif
                        % else:
                            % if not data.child:
                            rttr::registration::property("${data.name}", &${qualified_getter}, &${qualified_setter})
                            % else:
                                .property("${data.name}", &${qualified_getter}, &${qualified_setter})
                            % endif
                        % endif
                        % if not data.child:
                                ;
                        % endif
                        """
                    )
                ).render(data=self),
            ).lstrip("\n"),
        )


@builder
@dataclasses.dataclass
class RttrEnum:
    name: str
    type: str
    namespace: typing.Optional[str] = None
    values: typing.List[str] = dataclasses.field(default_factory=lambda: [])
    child: bool = False

    def __str__(self) -> str:
        return re.sub(
            r"\)\s*;$",
            ");",
            re.sub(
                r"(\n\s*\n)+",
                "\n",
                mako.template.Template(
                    textwrap.dedent(
                        """\
                        <%
                            qualified = f"{f'{data.namespace}::' if data.namespace is not None else ''}"
                            qualified_name = f"{qualified}{data.name}"
                            qualified_type = f"{qualified}{data.type}"
                        %>
                        % if not data.child:
                            rttr::registration::enumeration<${qualified_type}>("${data.name}")(
                        % else:
                                .enumeration<${qualified_type}>("${data.name}")(
                        % endif
                        % for index, value in enumerate(data.values):
                            % if index + 1 < len(data.values):
                                % if not data.child:
                                rttr::value("${value}", ${qualified_type}::${value}),
                                % else:
                                    rttr::value("${value}", ${qualified_type}::${value}),
                                % endif
                            % else:
                                % if not data.child:
                                rttr::value("${value}", ${qualified_type}::${value})
                                % else:
                                    rttr::value("${value}", ${qualified_type}::${value})
                                % endif
                            % endif
                        % endfor
                        % if not data.child:
                            );
                        % else:
                                )
                        % endif
                        """
                    )
                ).render(data=self),
            ).lstrip("\n"),
        )


@builder
@dataclasses.dataclass
class RttrClass:
    @builder
    @dataclasses.dataclass
    class Constructor:
        args: typing.List[str] = dataclasses.field(default_factory=lambda: [])

    name: str
    type: str
    namespace: typing.Optional[str] = None
    constructors: typing.List[Constructor] = dataclasses.field(
        default_factory=lambda: []
    )
    methods: typing.List[RttrMethod] = dataclasses.field(default_factory=lambda: [])
    properties: typing.List[RttrProperty] = dataclasses.field(
        default_factory=lambda: []
    )
    enumerations: typing.List[RttrEnum] = dataclasses.field(default_factory=lambda: [])

    def __str__(self) -> str:
        return re.sub(
            r"\)\s*;$",
            ");",
            re.sub(
                r"(\n\s*\n)+",
                "\n",
                mako.template.Template(
                    textwrap.dedent(
                        """\
                        <%!
                            import dataclasses
                        %>
                        <%
                            qualified = f"{f'{data.namespace}::' if data.namespace is not None else ''}"
                            qualified_name = f"{qualified}{data.name}"
                            qualified_type = f"{qualified}{data.type}"
                        %>
                            rttr::registration::class_<${qualified_type}>("${data.name}")
                        % for constructor in data.constructors:
                                .constructor<${", ".join(constructor.args)}>()
                        % endfor
                        % for method in data.methods:
                                <%
                                    qualified_namespace = f"{f'{qualified_type}::{method.namespace}' if method.namespace is not None else f'{qualified_type}'}"
                                %>
                        ${str(dataclasses.replace(method, namespace=qualified_namespace, child=True))}
                        % endfor
                        % for property in data.properties:
                                <%
                                    qualified_namespace = f"{f'{qualified_type}::{property.namespace}' if property.namespace is not None else f'{qualified_type}'}"
                                %>
                        ${str(dataclasses.replace(property, namespace=qualified_namespace, child=True))}
                        % endfor
                        % for enumeration in data.enumerations:
                                <%
                                    qualified_namespace = f"{f'{qualified_type}::{enumeration.namespace}' if enumeration.namespace is not None else f'{qualified_type}'}"
                                %>
                        ${str(dataclasses.replace(enumeration, namespace=qualified_namespace, child=True))}
                        % endfor
                                ;
                        """
                    )
                ).render(data=self),
            ).lstrip("\n"),
        )


@builder
@dataclasses.dataclass
class Rttr:
    methods: typing.List[RttrMethod] = dataclasses.field(default_factory=lambda: [])
    properties: typing.List[RttrProperty] = dataclasses.field(
        default_factory=lambda: []
    )
    enumerations: typing.List[RttrEnum] = dataclasses.field(default_factory=lambda: [])
    classes: typing.List[RttrClass] = dataclasses.field(default_factory=lambda: [])

    def dump(self) -> None:
        cog.outl(str(self))

    def __str__(self) -> str:
        return re.sub(
            r"\)\s*;$",
            ");",
            re.sub(
                r"(\n\s*\n)+",
                "\n",
                mako.template.Template(
                    textwrap.dedent(
                        """\
                        // NOLINTBEGIN
                        // clang-format off
                        RTTR_REGISTRATION {
                        % for method in data.methods:
                        ${str(method)}
                        % endfor
                        % for property in data.properties:
                        ${str(property)}
                        % endfor
                        % for enumeration in data.enumerations:
                        ${str(enumeration)}
                        % endfor
                        % for class_ in data.classes:
                        ${str(class_)}
                        % endfor
                        }
                        // clang-format on
                        // NOLINTEND
                        """
                    )
                ).render(data=self),
            ).strip("\n"),
        )
