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

enum MODES
{
    DEBUG = 1,
    RELEASE = 0
};


const int CUR_MODE = DEBUG;

//! structure for combining an element and its frequency
template <typename KeyT>
struct Cache_item
{
    KeyT elem; // it should be template type
    int freq;  // param of frequency calls cache_item
};


//! Class for lfu_algorithm
template <typename T, typename KeyT>
class Cache_t
{
private:

    std::list<T> cache;

    size_t cap;

    //! my old typedef
    //typedef std::list<T>::iterator ListIt;
    //typedef std::unordered_map<KeyT, ListIt>::iterator HashIt;

    using ListIt = typename std::list<T>::iterator;

    // structure map, which connect value_type (should be template) and iterator on list
    std::unordered_map<KeyT, ListIt> hash_tab;



public:

    //! Constructor of class
    Cache_t(size_t size) : cap(size)
    {}

    //! Distructor of class
    ~Cache_t()
    {
        cap = 0;
    }


    //! Function for checking the existence of an item in the cache
    bool Look_up(const KeyT elem)
    {
        auto hit = hash_tab.find(elem);

        //if hit doesnt exist in map or freq == 0 (it means that elem existed in list in past)
        if (hit == hash_tab.end() || (hit->second->freq == 0))
        {
            if (cache.size() == cap)
            {
                ListIt min_used_elem = Find_least_used();


                //Delete_from_cache();
                if (!Delete_from_cache(min_used_elem))
                {
                    printf("Error in deleting from cache!\n");
                    abort();
                }

            }

            T new_item = {elem, 1};

            cache.push_front(new_item);
            hash_tab[elem] = cache.begin();

            if (CUR_MODE == DEBUG)
            {
                ListIt iter = cache.begin();
                std::cout << "Elem = " << iter->elem << " Freq = " << iter->freq << "\n";
            }

            return false;
        }
        //else if hit exist in map =>

        hit->second->freq++;

        if (CUR_MODE == DEBUG)
            std::cout << "Elem = " << hit->second->elem << " Freq = " << hit->second->freq << "\n";

        return true;
    }


private:

    //! Function for finding least used cache_items
    auto Find_least_used()
    {
        ListIt iter = cache.begin();
        ListIt min_iter = iter;
        int min_freq = iter->freq;

        for (; iter != cache.end(); ++iter)
        {
            if (iter->freq < min_freq)
                min_iter = iter;
        }

        return min_iter;
    }

    //! Function for deleting item from the cache and map
    bool Delete_from_cache(ListIt min_used_elem)
    {
        ListIt check_it = cache.erase(min_used_elem);
        hash_tab.erase(min_used_elem->elem);

        if (CUR_MODE == DEBUG)
        {
            std::cout << "Debug cout in delete from cache" << std::endl;
            std::cout << "Elem = " << check_it->elem << " Freq = " << check_it->freq << std::endl;
        }

        return true;
    }
};


#endif //__LFU_H__
