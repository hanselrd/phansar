#include <phansar/common.hpp>

#define RAYGUI_SUPPORT_ICONS
#include <hedley.h>
#include <raygui.h>
#include <raylib.h>
#include <ricons.h>

#include <array>
#include <cstring>

#define BUF_SIZE 512

HEDLEY_PRINTF_FORMAT(2, 0)
static void trace_log_callback(int msg_type, const char * fmt, va_list args) {
    auto buf = std::array<char, BUF_SIZE>{};
    std::vsnprintf(buf.data(), sizeof(buf), fmt, args);

    switch (msg_type) {
    case LOG_DEBUG:
        LOGD("{}", buf.data());
        break;
    case LOG_INFO:
        LOGI("{}", buf.data());
        break;
    case LOG_WARNING:
        LOGW("{}", buf.data());
        break;
    case LOG_ERROR:
        LOGE("{}", buf.data());
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

    while (! WindowShouldClose()) {
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

    phansar::common::system::shutdown();

    return 0;
}
