#include <phansar/common/histogram.hpp>
#include <phansar/common/log.hpp>
#include <phansar/common/python.hpp>
#include <phansar/common/system.hpp>

#include <phansar/vendor/hedley.hpp>
#include <phansar/vendor/pybind11.hpp>
#include <phansar/vendor/raygui.hpp>
#include <phansar/vendor/raylib.hpp>

#include <array>
#include <cstring>

#define BUF_SIZE 512

// NOLINTNEXTLINE(modernize-use-trailing-return-type)
PYBIND11_EMBEDDED_MODULE(phansar, m) {
    phansar::common::python::embed(m);
}

HEDLEY_PRINTF_FORMAT(2, 0)
static void trace_log_callback(int msg_type, const char * fmt, va_list args) {
    auto buf = std::array<char, BUF_SIZE>{};
    std::vsnprintf(buf.data(), buf.size(), fmt, args);

    switch (msg_type) {
    case LOG_TRACE:
        phansar::common::log::print("<raylib>",
                                    1,
                                    phansar::common::log::level::trace,
                                    "{}",
                                    buf.data());
        break;
    case LOG_DEBUG:
        phansar::common::log::print("<raylib>",
                                    1,
                                    phansar::common::log::level::debug,
                                    "{}",
                                    buf.data());
        break;
    case LOG_INFO:
        phansar::common::log::print("<raylib>",
                                    1,
                                    phansar::common::log::level::info,
                                    "{}",
                                    buf.data());
        break;
    case LOG_WARNING:
        phansar::common::log::print("<raylib>",
                                    1,
                                    phansar::common::log::level::warning,
                                    "{}",
                                    buf.data());
        break;
    case LOG_ERROR:
        phansar::common::log::print("<raylib>",
                                    1,
                                    phansar::common::log::level::error,
                                    "{}",
                                    buf.data());
        break;
    case LOG_FATAL:
        phansar::common::log::print("<raylib>",
                                    1,
                                    phansar::common::log::level::critical,
                                    "{}",
                                    buf.data());
        break;
    }
}

auto main(int argc, char * argv[]) -> int {
    phansar::common::system::init(argc, argv);

    SetTraceLogCallback(&trace_log_callback);

    const auto screen_width  = int{800};
    const auto screen_height = int{600};

    InitWindow(screen_width, screen_height, "Phansar");

    GuiLoadStyle("_deps/raygui_git-src/styles/jungle/jungle.rgs");

    auto ball_position = Vector2{(float)screen_width / 2, (float)screen_height / 2};

    const auto target_fps = int{60};

    SetTargetFPS(target_fps);

    const auto velocity = float{2.0F};

    auto hist_fps = phansar::common::histogram<int>{"FPS", "frames per second", 5};

    while (! WindowShouldClose()) {
        hist_fps.push(GetFPS());

        if (IsKeyDown(KEY_LEFT)) {
            ball_position.x -= velocity;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            ball_position.x += velocity;
        }
        if (IsKeyDown(KEY_UP)) {
            ball_position.y -= velocity;
        }
        if (IsKeyDown(KEY_DOWN)) {
            ball_position.y += velocity;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        const auto font_size = int{20};

        const auto ball_radius = float{50.0F};

        DrawText("Phansar", screen_width / 3, screen_height / 3, font_size, LIGHTGRAY);
        DrawCircleV(ball_position, ball_radius, MAROON);

        const auto button_width  = int{100};
        const auto button_height = int{30};

        if (GuiButton(
                {(float)screen_width / 4, (float)screen_height / 4, button_width, button_height},
                GuiIconText(RICON_HAND_POINTER, "Click Me"))) {
            LOGI("Clicked");
        }

        EndDrawing();
    }

    CloseWindow();

    hist_fps.log();

    phansar::common::system::shutdown();

    return 0;
}
