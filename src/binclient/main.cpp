#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS

#include <array>
#include <common.hpp>
#include <cstring>
#include <raygui.h>
#include <raylib.h>

auto main(int argc, char * argv[]) -> int {
    common::system::init(argc, argv);

    SetTraceLogCallback([](int msg_type, const char * text, va_list args) {
        auto buf = std::array<char, 512>{};
        std::vsnprintf(buf.data(), sizeof(buf), text, args);

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
    });

    const auto screen_width  = int{800};
    const auto screen_height = int{600};

    InitWindow(screen_width, screen_height, "Phansar");

    GuiLoadStyle("_deps/raygui_git-src/styles/jungle/jungle.rgs");

    auto ball_position = Vector2{screen_width / 2, screen_height / 2};

    SetTargetFPS(60);

    while (! WindowShouldClose()) {
        if (IsKeyDown(KEY_LEFT)) {
            ball_position.x -= 2.0f;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            ball_position.x += 2.0f;
        }
        if (IsKeyDown(KEY_UP)) {
            ball_position.y -= 2.0f;
        }
        if (IsKeyDown(KEY_DOWN)) {
            ball_position.y += 2.0f;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Phansar", 190, 200, 20, LIGHTGRAY);
        DrawCircleV(ball_position, 50, MAROON);

        if (GuiButton({100, 100, 100, 30}, GuiIconText(RICON_HAND_POINTER, "Click Me"))) {
            LOGI("Clicked");
        }

        EndDrawing();
    }

    CloseWindow();

    common::system::shutdown();

    return 0;
}
