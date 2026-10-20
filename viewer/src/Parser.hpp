#pragma once

#include <string>

#include "Match.hpp"

// Turns the VM's stdout, one line at a time, into a Match.
// Pure logic, no SDL and no I/O, so it can be unit-tested with a log file.
class Parser
{
public:
    void feed(const std::string& line);  // one line, without the trailing '\n'
    const Match& match() const { return match_; }

private:
    void startBoard(const std::string& line);
    void addRow(const std::string& line);

    Match match_;
    Frame pending_;       // board being read
    int rowsLeft_ = 0;    // board rows still expected
    bool skipHeader_ = false;  // the "    0123..." line after "Plateau"
};
