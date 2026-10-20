#pragma once

#include <cmath>
#include <cstddef>
#include <string>
#include <SDL3/SDL.h>

#include "Match.hpp"

constexpr float kHudHeight = 90.0f;

namespace colors
{
constexpr SDL_Color background{0x00, 0x00, 0x00, 0xff};
constexpr SDL_Color empty{0x8b, 0x8d, 0x8e, 0xff};      // '.'
constexpr SDL_Color p1{0x45, 0x95, 0xad, 0xff};         // 'O'  (BLUE)
constexpr SDL_Color p1Last{0xa6, 0xcd, 0xed, 0xff};     // 'o'  last piece (LIGHT_BLUE)
constexpr SDL_Color p2{0x96, 0x36, 0x5f, 0xff};         // 'X'  (PINK)
constexpr SDL_Color p2Last{0xe5, 0x9e, 0xbc, 0xff};     // 'x'  last piece (LIGHT_PINK)
constexpr SDL_Color text{0xff, 0xff, 0xff, 0xff};
}  // namespace colors

void drawBoard(SDL_Renderer* renderer, const Frame& frame, const SDL_FRect &area);

// Draws names, scores and playback info on top. `cursor` is the index of
// the frame being shown.
// return HUd height
void drawHud(SDL_Renderer* renderer, const Match& match, std::size_t cursor);
