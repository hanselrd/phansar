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

#include <cef_app.h>
#include <cef_client.h>
#include <cef_life_span_handler.h>
#include <cef_load_handler.h>
#include <cef_render_handler.h>
#include <common/utils/log/log.hpp>
#include <wrapper/cef_helpers.h>

class MyApp : public CefApp {
public:
private:
    IMPLEMENT_REFCOUNTING(MyApp);
};

int main(int argc, char *argv[]) {
    common::utils::log::init("cef_test.log");

    auto main_args = CefMainArgs{argc, argv};

    auto app = CefRefPtr<MyApp>{new MyApp};

    auto exit_code = CefExecuteProcess(main_args, app.get(), nullptr);
    if (exit_code >= 0) {
        return exit_code;
    }

    auto settings = CefSettings{};

    CefInitialize(main_args, settings, app.get(), nullptr);

    CefRunMessageLoop();

    CefShutdown();

    return 0;
}
