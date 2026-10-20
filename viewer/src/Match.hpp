#pragma once

#include <optional>
#include <string>
#include <utility>
#include <vector>

// One board snapshot, i.e. one "Plateau H W:" block printed by the VM.
struct Frame
{
    int w = 0;
    int h = 0;
    std::vector<char> cells;  // row-major, w * h: '.', 'O', 'o', 'X' or 'x'
    int cellsO = 0;           // cells covered by player 1 (O / o)
    int cellsX = 0;           // cells covered by player 2 (X / x)

    char at(int x, int y) const { return cells[static_cast<size_t>(y * w + x)]; }
};

// Everything the viewer knows about the game so far. This is the viewer's
// *game state*: it only grows, and the renderer only reads it.
struct Match
{
    std::string p1;                              // player names, e.g. "tsergien"
    std::string p2;
    std::vector<Frame> frames;                   // one per turn, in order
    std::optional<std::pair<int, int>> finalScore;  // (O, X) from "== O fin: N"
};
