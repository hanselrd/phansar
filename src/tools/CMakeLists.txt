#
# This file is part of Phansar.
#
# Copyright (C) 2018  Hansel De La Cruz
#
# Phansar is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Phansar is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
#

project(tools)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tools)

set(libs
    ${CMAKE_PROJECT_NAME}-common)

function(add_tool tool)
    add_executable(${tool}
        ${tool}.cpp)

    target_link_libraries(${tool}
        ${libs})

    target_compile_options(${tool} PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wextra>
        $<$<CXX_COMPILER_ID:MSVC>:/Wall>)
endfunction()

add_tool(box2d_test)
# add_tool(cef_test)
add_tool(compile_assets)
add_tool(optional_json)
add_tool(rttr_test)
add_tool(variant_json)
