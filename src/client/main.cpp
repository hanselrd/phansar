#include <phansar/common/histogram.hpp>
#include <phansar/common/log.hpp>
#include <phansar/common/python.hpp>
#include <phansar/common/system.hpp>

#include <phansar/vendor/fmt.hpp>
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
static void trace_log_callback(int _msg_type, const char * _fmt, va_list _args) {
    auto buf = std::array<char, BUF_SIZE>{};
    std::vsnprintf(buf.data(), buf.size(), _fmt, _args);

    if (phansar::common::log::instance() != nullptr) {
        switch (_msg_type) {
        case LOG_TRACE:
            phansar::common::log::instance()->print(phansar::common::log::level::trace,
                                                    "<raylib>",
                                                    1,
                                                    "{}",
                                                    buf.data());
            break;
        case LOG_DEBUG:
            phansar::common::log::instance()->print(phansar::common::log::level::debug,
                                                    "<raylib>",
                                                    1,
                                                    "{}",
                                                    buf.data());
            break;
        case LOG_INFO:
            phansar::common::log::instance()->print(phansar::common::log::level::info,
                                                    "<raylib>",
                                                    1,
                                                    "{}",
                                                    buf.data());
            break;
        case LOG_WARNING:
            phansar::common::log::instance()->print(phansar::common::log::level::warning,
                                                    "<raylib>",
                                                    1,
                                                    "{}",
                                                    buf.data());
            break;
        case LOG_ERROR:
            phansar::common::log::instance()->print(phansar::common::log::level::error,
                                                    "<raylib>",
                                                    1,
                                                    "{}",
                                                    buf.data());
            break;
        case LOG_FATAL:
            phansar::common::log::instance()->print(phansar::common::log::level::critical,
                                                    "<raylib>",
                                                    1,
                                                    "{}",
                                                    buf.data());
            break;
        }
    }
}

auto main(int _argc, char * _argv[]) -> int {
    phansar::common::system::init(_argc, _argv);

    SetTraceLogCallback(&trace_log_callback);

    const auto screen_width  = int{800};
    const auto screen_height = int{600};

    InitWindow(screen_width, screen_height, "Phansar");

    GuiLoadStyle("_deps/raygui_git-src/styles/jungle/jungle.rgs");

    auto camera     = Camera{};
    camera.position = Vector3{4.F, 2.F, 4.F};
    camera.target   = Vector3{0.F, 1.8F, 0.F};
    camera.up       = Vector3{0.F, 1.F, 0.F};
    camera.fovy     = 60.F;
    camera.type     = CAMERA_PERSPECTIVE;

    SetCameraMode(camera, CAMERA_FIRST_PERSON);

    SetTargetFPS(60);

    auto hist_fps = phansar::common::histogram<int>{"FPS", "frames per second", 5};

    while (! WindowShouldClose()) {
        hist_fps.push(GetFPS());

        UpdateCamera(&camera);

        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);

        DrawPlane(Vector3{0.F, 0.F, 0.F}, Vector2{32.F, 32.F}, LIGHTGRAY);
        DrawCube(Vector3{-16.F, 2.5F, 0.F}, 1.F, 5.F, 32.F, BLUE);
        DrawCube(Vector3{16.F, 2.5F, 0.F}, 1.F, 5.F, 32.F, LIME);
        DrawCube(Vector3{0.F, 2.5F, -16.F}, 32.F, 5.F, 1.F, RED);
        DrawCube(Vector3{0.F, 2.5F, 16.F}, 32.F, 5.F, 1.F, GOLD);

        EndMode3D();

        DrawRectangle(10, 10, 250, 70, Fade(SKYBLUE, 0.5F));
        DrawRectangleLines(10, 10, 250, 70, BLUE);

        DrawText(fmt::format("Position: ({}, {}, {})",
                             camera.position.x,
                             camera.position.y,
                             camera.position.z)
                     .c_str(),
                 20,
                 20,
                 10,
                 WHITE);
        DrawText(
            fmt::format("Target: ({}, {}, {})", camera.target.x, camera.target.y, camera.target.z)
                .c_str(),
            20,
            40,
            10,
            WHITE);
        DrawText(fmt::format("Up: ({}, {}, {})", camera.up.x, camera.up.y, camera.up.z).c_str(),
                 20,
                 60,
                 10,
                 WHITE);

        /* DrawText("Phansar", screen_width / 3, screen_height / 3, 20, LIGHTGRAY); */

        /* if (GuiButton({(float)screen_width / 4, (float)screen_height / 4, 100, 30}, */
        /*               GuiIconText(RICON_HAND_POINTER, "Click Me"))) { */
        /*     LOGI("Clicked"); */
        /* } */

        EndDrawing();
    }

    CloseWindow();

    phansar::common::system::shutdown();

    return 0;
}
