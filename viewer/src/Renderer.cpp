#include "Renderer.hpp"

#include <algorithm>
#include <array>
#include <iterator>
#include <vector>

void drawBoard(SDL_Renderer* renderer, const Frame& frame, const SDL_FRect &area)
{
    if (frame.w <= 0 || frame.h <= 0 || area.w <= 0.0f || area.h <= 0.0f)
        return;

    constexpr float margin_k = 0.9f;  // leave some margin around the board
    const float cell_size_w = std::floor(margin_k * static_cast<float>(area.w) / frame.w);
    const float cell_size_h = std::floor(margin_k * static_cast<float>(area.h) / frame.h);
    const float cell_size = std::min(cell_size_w, cell_size_h);

    const float offset_x = std::floor(area.x + (area.w - cell_size_w * frame.w) / 2.0f);
    const float offset_y = std::floor(area.y + (area.h - cell_size_h * frame.h) / 2.0f);
    const float gap = cell_size > 6.0f ? 1.0f : 0.0f;

    const SDL_Color palette[] = {colors::empty, colors::p1, colors::p1Last,
                                 colors::p2, colors::p2Last};
    std::array<std::vector<SDL_FRect>, std::size(palette)> buckets;

    for (int y = 0; y < frame.h; ++y)
    {
        for (int x = 0; x < frame.w; ++x)
        {
            std::size_t bucket;
            switch (frame.at(x, y))
            {
                case '.': bucket = 0; break;
                case 'O': bucket = 1; break;
                case 'o': bucket = 2; break;
                case 'X': bucket = 3; break;
                case 'x': bucket = 4; break;
                default: continue;  // skip unknown characters
            }
            buckets[bucket].push_back({offset_x + x * cell_size_w, offset_y + y * cell_size_h,
                                       cell_size_w - gap, cell_size_h - gap});
        }
    }

    for (std::size_t i = 0; i < buckets.size(); ++i)
    {
        if (buckets[i].empty())
            continue;
        const SDL_Color& c = palette[i];
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
        SDL_RenderFillRects(renderer, buckets[i].data(),
                            static_cast<int>(buckets[i].size()));
    }
}

void drawHud(SDL_Renderer* renderer, const Match& match, std::size_t cursor)
{
    SDL_SetRenderScale(renderer, 2.0f, 2.0f);
    
    float x_0 = 4, row_1 = 4;
    float x_1 = x_0 + 8 * 8; // "Player: "
    float x_2 = x_1 + match.p1.size() * 8 + 3 * 8; // name + " | "
    float row_2 = row_1 + 12;

    std::string p1_points = match.frames.size() <= cursor ? "0" : std::to_string(match.frames[cursor].cellsO);
    std::string p2_points = match.frames.size() <= cursor ? "0" : std::to_string(match.frames[cursor].cellsX);

    SDL_SetRenderDrawColor(renderer, colors::text.r, colors::text.g, colors::text.b, colors::text.a);
    SDL_RenderDebugText(renderer, x_0, row_1, "Player: ");
    SDL_RenderDebugText(renderer, x_0, row_2, "Cells : ");
    
    SDL_SetRenderDrawColor(renderer, colors::p1.r, colors::p1.g, colors::p1.b, colors::p1.a);
    SDL_RenderDebugText(renderer, x_1, row_1, match.p1.c_str());
    SDL_RenderDebugText(renderer, x_1, row_2, p1_points.c_str());
    
    SDL_SetRenderDrawColor(renderer, colors::text.r, colors::text.g, colors::text.b, colors::text.a);
    SDL_RenderDebugText(renderer, x_1 + match.p1.size() * 8, row_1, " | ");
    SDL_RenderDebugText(renderer, x_1 + match.p1.size() * 8, row_2, " | ");
    
    SDL_SetRenderDrawColor(renderer, colors::p2.r, colors::p2.g, colors::p2.b, colors::p2.a);
    SDL_RenderDebugText(renderer, x_2, row_1, match.p2.c_str());
    SDL_RenderDebugText(renderer, x_2, row_2, p2_points.c_str());
    
    if (match.finalScore)
    {
        float row_3 = row_2 + 12;
        std::string final_score = "Final score: " + std::to_string(match.finalScore->first) + " - " + std::to_string(match.finalScore->second);
        SDL_SetRenderDrawColor(renderer, colors::text.r, colors::text.g, colors::text.b, colors::text.a);
        SDL_RenderDebugText(renderer, x_0, row_3, final_score.c_str());
    }
    
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
}
