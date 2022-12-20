#include <SDL.h>
#include <catch2/catch.hpp>
#include <iostream>

TEST_CASE("vendor::sdl2", "[vendor][sdl2]") {
  REQUIRE(SDL_Init(SDL_INIT_VIDEO) == 0);

  SDL_Window * window = SDL_CreateWindow(
      "phansar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
  if (window == nullptr) {
    std::cout << SDL_GetError() << "\n";
  }
  REQUIRE(window != nullptr);

  SDL_Renderer * renderer = SDL_CreateRenderer(
      window, -1, 0 /*SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC*/);
  if (renderer == nullptr) {
    std::cout << SDL_GetError() << "\n";
  }
  REQUIRE(renderer != nullptr);

#if 0
  while (true) {

  };
#endif

  SDL_DestroyRenderer(renderer);

  SDL_DestroyWindow(window);

  SDL_Quit();
}
