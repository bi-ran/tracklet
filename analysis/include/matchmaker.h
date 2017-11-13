#ifndef MATCHMAKER_H
#define MATCHMAKER_H

#include <unordered_map>
#include <tuple>

namespace std {
    template <>
    struct hash< std::tuple<int, int, int> > {
        std::size_t operator()(const std::tuple<int, int, int>& k) const {
            return std::hash<int>()(std::get<0>(k)) ^ std::hash<int>()(std::get<1>(k)) ^ std::hash<int>()(std::get<2>(k));
        }
    };
}

class matchmaker {
  public:
    matchmaker() {};
    ~matchmaker() {};

    void set(int run, int lumi, int event, int64_t entry) {
        mmap.insert(std::make_pair(std::make_tuple(run, lumi, event), entry));
    }

    int64_t get(int run, int lumi, int event) {
        auto it = mmap.find(std::make_tuple(run, lumi, event));
        if (it == mmap.end()) { return -1; }
        else { return it->second; }
    }

  private:
    std::unordered_map<std::tuple<int, int, int>, int64_t> mmap;
};

#endif  /* MATCHMAKER_H */
