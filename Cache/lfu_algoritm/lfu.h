//
// Created by anon on 17.09.2020.
//
#ifndef _NEW_LFU_H_
#define _NEW_LFU_H_


#include <iostream>
#include <cassert>
#include <list>
#include <unordered_map>
#include <vector>

enum MODES
{
    DEBUG = 1,
    RELEASE = 0,
    NO_PAGE = -1
};

#pragma warning (disable:4996)


const int CUR_MODE = DEBUG;
const int FIRST = 1;
const int NOT_FIRST = 2;


template <typename KeyT>
struct Freq_node;

template <typename KeyT>
struct Cache_item;

template <typename KeyT>
using FreqIt = typename std::list<Freq_node<KeyT>>::iterator;

template <typename KeyT>
struct Cache_item
{
    KeyT elem;
    FreqIt<KeyT> Freq_head;

    Cache_item(const KeyT value, FreqIt<KeyT> head) : elem(value),
        Freq_head(head)
    {}
};

template <typename KeyT>
struct Freq_node
{
    std::list<Cache_item<KeyT>> item_list;
    const int freq_value;

    Freq_node(const int value) : freq_value(value)
    {
    }
};



//! Class for lfu_algorithm
template <typename T, typename KeyT>
class Cache_t
{
private:

    std::list<Freq_node<KeyT>> Freq_list;

    size_t cap;

    using ListIt = typename std::list<Cache_item<KeyT>>::iterator;
    using HashIt = typename std::unordered_map<KeyT, ListIt>::iterator;

    std::unordered_map<KeyT, ListIt> hash_tab;

public:

    //! Constructor of class
    Cache_t(size_t size) : cap(size),
        Freq_list()
    {}

    //! Distructor of class
    ~Cache_t()
    {
        cap = 0;
    }


public:
    //! Function for checking the existence of an item in the cache
    bool Look_up(const KeyT elem)
    {
        HashIt hit = hash_tab.find(elem);

        //if hit doesnt exist in map
        if (hit == hash_tab.end())
        {
            if (hash_tab.size() == cap)
            {
                if (!Find_least_used())
                {
                    std::cout << "Error in find_least_used func\n";
                    abort();
                }
                //comments and debug
            }

            if (!Insert_new_item(elem))
            {
                std::cout << "Error in insert_new_item func\n";
                abort();
            }

            /*
            if (CUR_MODE == DEBUG)
            {
                ListIt iter = cache.begin();
                std::cout << "Elem = " << iter->elem << " Freq = " << iter->freq << "\n";
            }
             */
            return false;
        }
        //else if hit exist in map =>

        Retie_cache_item(hit->second);
        /*
                if (CUR_MODE == DEBUG)
                    std::cout << "Elem = " << hit->second->elem << " Freq = " << hit->second->freq << "\n";
        */
        return true;
    }


private:

    bool Insert_new_item(const KeyT elem)
    {
        FreqIt<KeyT> freq_head = Freq_list.begin();

        //Checking for insertion new freq_node
        if (Freq_list.empty() || freq_head->freq_value != 1)
            Freq_list.push_front(Freq_node<KeyT>(1));

        //Insertion new item in item_list
        Freq_list.begin()->item_list.push_front(Cache_item<KeyT>(elem, Freq_list.begin()));

        //insertion to hash_table
        ListIt new_item = Freq_list.begin()->item_list.begin();
        hash_tab[elem] = new_item;

        return true;
    }


    bool Delete_least_used(ListIt min_used_item, FreqIt<KeyT> min_freq_node)
    {
        hash_tab.erase(min_used_item->elem);

        ListIt check_item = min_freq_node->item_list.erase(min_used_item);

        if ((min_freq_node->item_list.begin() == min_freq_node->item_list.end()) & (min_freq_node->freq_value != 1))
        {
            FreqIt<KeyT> freq_check = Freq_list.erase(min_freq_node);
        }

        return true;
    }

    //! Function for finding least used cache_items
    bool Find_least_used()
    {
        FreqIt<KeyT> min_freq_node = Freq_list.begin();
        ListIt min_used_item = min_freq_node->item_list.begin();

        Delete_least_used(min_used_item, min_freq_node);

        return true;
    }



    bool Retie_cache_item(ListIt item_it)
    {
        FreqIt<KeyT> current_freq = item_it->Freq_head;
        FreqIt<KeyT> next_current_freq = ++current_freq;
        --current_freq;

        if ((next_current_freq != Freq_list.end() && (current_freq->freq_value + 1) == (next_current_freq->freq_value)))
        {
            if (!Add_and_delete_item(current_freq, next_current_freq, item_it))
            {
                std::cout << "Error in add and delete func\n";
                abort();
            }
        }
        else
        {
            FreqIt<KeyT> real_next_freq = Freq_list.insert(next_current_freq, Freq_node<KeyT>(current_freq->freq_value + 1));

            if (!Add_and_delete_item(current_freq, real_next_freq, item_it))
            {
                std::cout << "Error in add and delete func\n";
                abort();
            }
        }

        return true;
    }

    bool Add_and_delete_item(FreqIt<KeyT> cur_freq, FreqIt<KeyT> next_freq, ListIt it)
    {
        struct Cache_item<KeyT> new_item(it->elem, next_freq);

        hash_tab.erase(it->elem);
        cur_freq->item_list.erase(it);

        next_freq->item_list.push_front(new_item);
        hash_tab[new_item.elem] = next_freq->item_list.begin();

        return true;
    }

    //! Function for deleting item from the cache and map
    /*
    bool Delete_from_cache(ListIt min_used_elem)
    {
        if (CUR_MODE == DEBUG)
        {
            std::cout << "Debug cout in delete from cache" << std::endl;
            std::cout << "Elem = " << check_it->elem << " Freq = " << check_it->freq << std::endl;
        }
        return true;
    }
     */
};

#endif //_NEW_LFU_H_





