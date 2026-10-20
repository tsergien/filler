#include "Parser.hpp"

#include <cstdio>

namespace
{

bool startsWith(const std::string& s, const char* prefix)
{
    return s.rfind(prefix, 0) == 0;
}

// "$$$ exec p1 : [players/carli.filler]" -> "carli"
std::string playerName(const std::string& line)
{
    auto open = line.find('[');
    auto close = line.find(']', open);
 
    if (open == std::string::npos || close == std::string::npos)
        return "?";
 
    std::string path = line.substr(open + 1, close - open - 1);
    auto slash = path.rfind('/');
    if (slash != std::string::npos)
        path = path.substr(slash + 1);
    auto dot = path.find('.');
    return path.substr(0, dot);
}

}  // namespace

void Parser::feed(const std::string& line)
{
    if (skipHeader_)
    {
        skipHeader_ = false;
        return;
    }
    if (rowsLeft_ > 0)
    {
        addRow(line);
        return;
    }
    if (startsWith(line, "Plateau"))
        startBoard(line);
    else if (startsWith(line, "$$$ exec p1"))
        match_.p1 = playerName(line);
    else if (startsWith(line, "$$$ exec p2"))
        match_.p2 = playerName(line);
    else if (startsWith(line, "== O fin:") || startsWith(line, "== X fin:"))
    {
        int score = 0;
        std::sscanf(line.c_str() + 9, "%d", &score);
        if (!match_.finalScore)
            match_.finalScore.emplace(0, 0);
        if (line[3] == 'O')
            match_.finalScore->first = score;
        else
            match_.finalScore->second = score;
    }
    // Everything else ("Piece ...", "<got (O): ...", banners) is ignored.
}

void Parser::startBoard(const std::string& line)
{
    pending_ = Frame{};
    // "Plateau 15 17:" means 15 rows (h) and 17 columns (w).
    if (std::sscanf(line.c_str(), "Plateau %d %d", &pending_.h, &pending_.w) != 2
        || pending_.h <= 0 || pending_.w <= 0)
        return;
    pending_.cells.reserve(static_cast<size_t>(pending_.w * pending_.h));
    rowsLeft_ = pending_.h;
    skipHeader_ = true;
}

void Parser::addRow(const std::string& line)
{
    // "003 ..O.......X" : 3-digit row number and a space, then the cells.
    for (int x = 0; x < pending_.w; ++x)
    {
        size_t i = 4 + static_cast<size_t>(x);
        char c = i < line.size() ? line[i] : '.';
        pending_.cells.push_back(c);
        if (c == 'O' || c == 'o')
            ++pending_.cellsO;
        else if (c == 'X' || c == 'x')
            ++pending_.cellsX;
    }
    if (--rowsLeft_ == 0)
        match_.frames.push_back(std::move(pending_));
}
