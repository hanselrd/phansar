/**
 *  This file is part of Phansar.
 *
 *  Copyright (C) 2019  Hansel De La Cruz
 *
 *  Phansar is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Phansar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with Phansar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "rtti.hpp"
#include "../bitmasks/permissions/permissions.hpp"
#include "../utils/log/log.hpp"
#include <rttr/registration>

namespace common::rtti {
void init() {
    LOGI("common rtti initialized");
}
} // namespace common::rtti

RTTR_REGISTRATION {
    rttr::registration::enumeration<common::bitmasks::permissions>("common::bitmasks::permissions")(
        rttr::value("NONE", common::bitmasks::permissions::NONE),
        rttr::value("VETERAN", common::bitmasks::permissions::VETERAN),
        rttr::value("DONOR", common::bitmasks::permissions::DONOR),
        rttr::value("INTERN", common::bitmasks::permissions::INTERN),
        rttr::value("ADVISOR", common::bitmasks::permissions::ADVISOR),
        rttr::value("MODERATOR", common::bitmasks::permissions::MODERATOR),
        rttr::value("ADMINISTRATOR", common::bitmasks::permissions::ADMINISTRATOR),
        rttr::value("OWNER", common::bitmasks::permissions::OWNER),
        rttr::value("ROOT", common::bitmasks::permissions::ROOT),
        rttr::metadata(common::rtti::metadata::module, "common.bitmasks"),
        rttr::metadata(common::rtti::metadata::name, "permissions"));
}
