#include <cstdio>
#include <iostream>

#include <SDL3/SDL.h>

#include "Reader.hpp"
#include "Renderer.hpp"

namespace
{

constexpr int kWindowW = 1000;
constexpr int kWindowH = 1000;

struct App
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool running = true;

    Match match;  // game state, copied from the reader thread every frame

    // TODO(task 6): view state: which frame is shown (cursor), paused or live.
    // TODO(task 7): playback speed (turns per second) and a time accumulator.
};

void handleEvents(App& app)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT)
            app.running = false;

        if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)
            app.running = false;

        // TODO(task 6): Space / Left / Right / Home / End.
        // TODO(task 7): Up / Down change the speed.
    }
}

void update(App& app, const Reader& reader, double dt)
{
    size_t before = app.match.frames.size();
    reader.sync(app.match);
    if (app.match.frames.size() != before)
        std::fprintf(stderr, "frames received: %zu\n", app.match.frames.size());

    // TODO(task 7): move the cursor forward at `speed` turns per second.
    (void)dt;
}

void render(App& app)
{
    // clear the screen with colors::background, then present it.
    SDL_SetRenderDrawColor(app.renderer, colors::background.r, colors::background.g, colors::background.b, colors::background.a);
    SDL_RenderClear(app.renderer);

    drawHud(app.renderer, app.match, app.match.frames.size() - 1);

    if (!app.match.frames.empty())
    {
        int outW = 0;
        int outH = 0;
        SDL_GetCurrentRenderOutputSize(app.renderer, &outW, &outH);

        SDL_FRect board_area{0.0, kHudHeight, static_cast<float>(outW), static_cast<float>(outH - kHudHeight)};

        drawBoard(app.renderer, app.match.frames.back(), board_area);
    }

    SDL_RenderPresent(app.renderer);
}

}  // namespace

int main()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    App app;
    SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE;
    if (!SDL_CreateWindowAndRenderer("Filler", kWindowW, kWindowH, flags,
                                     &app.window, &app.renderer))
    {
        SDL_Log("Window/renderer creation failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_SetWindowMinimumSize(app.window, 300, 300);

    Reader reader(std::cin);

    // game loop
    Uint64 last = SDL_GetTicksNS();
    while (app.running)
    {
        Uint64 now = SDL_GetTicksNS();
        double dt = static_cast<double>(now - last) / 1e9;  // seconds
        last = now;

        handleEvents(app);
        update(app, reader, dt);
        render(app);

        SDL_Delay(16);  // ~60 FPS. TODO(task 8): replace with VSync.
    }

    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
    return 0;
}
