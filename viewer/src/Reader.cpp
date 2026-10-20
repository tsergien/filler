#include "Reader.hpp"

#include <string>

#include "Parser.hpp"

Reader::Reader(std::istream& in)
    : shared_(std::make_shared<Shared>())
{
    thread_ = std::thread([shared = shared_, &in] {
        Parser parser;
        std::string line;
        size_t published = 0;

        while (std::getline(in, line))
        {
            parser.feed(line);
            const Match& m = parser.match();
            std::lock_guard<std::mutex> lock(shared->mutex);
            // Publish only what changed: new frames, names, final score.
            for (; published < m.frames.size(); ++published)
                shared->match.frames.push_back(m.frames[published]);
            shared->match.p1 = m.p1;
            shared->match.p2 = m.p2;
            shared->match.finalScore = m.finalScore;
        }
        shared->done = true;
    });
}

Reader::~Reader()
{
    // If the game is still running, the thread is stuck in getline() and
    // can't be interrupted portably; let it finish on its own (the process
    // is exiting anyway). Shared state is kept alive by the shared_ptr.
    if (shared_->done)
        thread_.join();
    else
        thread_.detach();
}

void Reader::sync(Match& out) const
{
    std::lock_guard<std::mutex> lock(shared_->mutex);
    const Match& in = shared_->match;

    for (size_t i = out.frames.size(); i < in.frames.size(); ++i)
        out.frames.push_back(in.frames[i]);
    out.p1 = in.p1;
    out.p2 = in.p2;
    out.finalScore = in.finalScore;
}
