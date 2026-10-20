#pragma once

#include <atomic>
#include <istream>
#include <memory>
#include <mutex>
#include <thread>

#include "Match.hpp"

// Reads the VM output on a background thread, so the game loop never blocks
// waiting for input
class Reader
{
public:
    explicit Reader(std::istream& in);
    ~Reader();
    Reader(const Reader&) = delete;
    Reader& operator=(const Reader&) = delete;

    // Copies whatever is new since the last call into `out` (frames are
    // appended, never copied twice). Cheap to call every frame.
    void sync(Match& out) const;

    // True once the VM closed the pipe (the game is over)
    bool done() const { return shared_->done; }

private:
    // Owned jointly with the thread, so it stays valid even if the thread is
    // still blocked in a read when the Reader is destroyed.
    struct Shared
    {
        std::mutex mutex;
        Match match;
        std::atomic<bool> done{false};
    };

    std::shared_ptr<Shared> shared_;
    std::thread thread_;
};
