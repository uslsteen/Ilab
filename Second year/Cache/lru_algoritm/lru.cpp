#include <iostream>
#include <cassert>
#include <list>
#include <unordered_map>
#include <vector>


// assume T::id of type KeyT
//template <typename T, typename KeyT = int>
class Cache_t
{
private:
    size_t sz_;
    std::list<int> cache_;

    typedef std::list<int>::iterator ListIt;

    std::unordered_map<int, ListIt> hash_;

public:

    Cache_t(size_t size) : sz_(size)
    {}

    bool lookup(const int elem);

private:
    bool full() const;
};



bool Cache_t::lookup(const int elem)
{
    auto hit = hash_.find(elem);
    if (hit == hash_.end())
    {
        if (full())
        {
            hash_.erase(cache_.back());
            cache_.pop_back();
        }
        cache_.push_front(elem);
        hash_[elem] = cache_.begin();
        return false;
    }

    auto eltit = hit->second;

    if (eltit != cache_.begin())
        cache_.splice(cache_.begin(), cache_, eltit, std::next(eltit));

    return true;
}


bool Cache_t::full() const
{
    return (cache_.size() == sz_);
}


int main()
{
    int hits = 0;
    int m, n = 0;


    std::cin >> m >> n;

    Cache_t cache(m);

    for (int i = 0; i < n; ++i)
    {
        int p;
        std::cin >> p;
        assert(std::cin.good());
        if (cache.lookup(p))
            hits += 1;
    }

    std::cout << hits << "\n";
}
