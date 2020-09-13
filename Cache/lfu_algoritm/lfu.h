//
// Created by anon on 13.09.2020.
//
#ifndef __LFU_H__
#define __LFU_H__

#include <iostream>
#include <cassert>
#include <list>
#include <unordered_map>
#include <vector>

enum MODE
{
    DEBUG = 1,
    RELEASE = 0
};


#define MODE DEBUG

struct Cache_item
{
    int elem; // it should be template type
    int freq;  // param of frequency calls cache_item
};


//template <typename T, typename KeyT = int>
class Cache_t
{

private:
    std::list<Cache_item> cache_;

    size_t cap;

    // typedef for iterators of map and list

    typedef std::list<Cache_item>::iterator ListIt;
    typedef std::unordered_map<int, ListIt>::iterator HashIt;

    // structure map, which connect value_type (should be template) and iterator on list
    std::unordered_map<int, ListIt> hash_;

public:

    Cache_t(size_t size) : cap(size)
    {}

    ~Cache_t()
    {
        cap = 0;
    }


    bool Look_up(const int elem);

private:
    auto Find_min_used();

    bool Delete_from_cache(ListIt min_used_elem);

    struct Cache_item Cache_item_construct(int elem);
};


auto Cache_t::Find_min_used()
{
    ListIt iter = cache_.end();
    ListIt min_iter = iter;
    int min_freq = iter->freq;

    for (; iter != cache_.begin(); --iter)
    {
        if (iter->freq < min_freq)
            min_iter = iter;
    }

    return min_iter;
}

bool Cache_t::Delete_from_cache(ListIt min_used_elem)
{
    ListIt check_it = cache_.erase(min_used_elem);
    hash_.erase(min_used_elem->elem);

#if MODE == DEBUG

    std::cout << "Debug cout in delete from cache" << std::endl;
    std::cout<< "Elem = " << check_it->elem << " Freq = " << check_it->freq << std::endl;
#endif

    return true;
}


bool Cache_t::Look_up(const int elem)
{
    HashIt hit = hash_.find(elem);

    //if hit doesnt exist in map or freq == 0 (it means that elem existed in list in past)
    if (hit == hash_.end() || (hit->second->freq == 0))
    {
        if (cache_.size() == cap)
        {
            ListIt min_used_elem = Find_min_used();


            //Delete_from_cache();
            if (!Delete_from_cache(min_used_elem))
            {
                printf("Error in deleting from cache!\n");
                abort();
            }

        }

        struct Cache_item new_item = {elem, 1};

        cache_.push_front(new_item);
        hash_[elem] = cache_.begin();

#if MODE == DEBUG

        ListIt iter = cache_.begin();
        std::cout << "Elem = " << iter->elem << " Freq = " << iter->freq << "\n";
#endif

        return false;
    }
    //else if hit exist in map =>

    hit->second->freq++;

#if MODE == DEBUG

    std::cout << "Elem = " << hit->second->elem << " Freq = " << hit->second->freq << "\n";
#endif

    return true;
}

#endif //__LFU_H__
