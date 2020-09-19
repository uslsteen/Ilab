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
#include <fstream>
#include <string>



enum MODES
{
    DEBUG = 1,
    RELEASE = 0
};

#pragma warning (disable:4996)

const int CUR_MODE = DEBUG;

//! Decloration of freq_node structure
template <typename KeyT>
struct Freq_node;

//! Decloration of cache_item structure
template <typename KeyT>
struct Cache_item;

//! typedef for iterator of std::list<Freq_node>
template <typename KeyT>
using FreqIt = typename std::list<Freq_node<KeyT>>::iterator;


//! Definition of cache_item structure
template <typename KeyT>
struct Cache_item
{
    KeyT elem;
    FreqIt<KeyT> Freq_head;

    Cache_item(const KeyT value, FreqIt<KeyT> head) : elem(value),
        Freq_head(head)
    {}
};

//! Definition of Freq_node structure
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
template <typename KeyT>
class Cache_t
{
private:

    //! List of freq_node for lfu algoritm
    std::list<Freq_node<KeyT>> Freq_list;

    size_t cap;

    //typedef for std::list
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

    //! Function for testing lfu algoritm
    //! @param[in] pages - vector of elems of request from user (for example any page)
    //! @param[in] num_of_calls
    //! @return quantity of hit
    int Test_processing(std::vector<int>& pages, int num_of_calls)
    {
        int hits = 0;

        for (int i = 0; i < num_of_calls; ++i)
        {
            if (Look_up(pages[i]))
                hits++;
        }

        return hits;
    }


    //! Function for checking the existence of an item in the cache
    //! @param[in] elem - elem of request from user (for example any page)
    //! @return true if cache hits happened
    //! @return false if elem doesn't exist in cache
    bool Look_up(const KeyT elem)
    {
        HashIt hit = hash_tab.find(elem);

        //if hit doesnt exist in map
        if (hit == hash_tab.end())
        {
            if (hash_tab.size() == cap)
            {
                ListIt min_used_item = Find_least_used();
                Delete_least_used(min_used_item, min_used_item->Freq_head);
            }

            if (!Insert_new_item(elem))
            {
                std::cout << "Error in insert_new_item func\n";
                abort();
            }

            return false;
        }

        //else if hit exist in map =>
        Retie_freq_node(hit->second);

        return true;
    }


    //! Block for private methods of class Cahte_t
private:


    //! Function for insertion new item in cache
    //! @param[in] elem - elem of request from user (for example any page)
    //! @return func executed without errors
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


    //! Function for deleting item from cache
    //! @param[in] elem - elem of request from user (for example any page)
    //! @return func executed without errors
    bool Delete_least_used(ListIt min_used_item, FreqIt<KeyT> min_freq_node)
    {
        hash_tab.erase(min_used_item->elem);

        ListIt check_item = min_freq_node->item_list.erase(min_used_item);

        if ((min_freq_node->item_list.begin() == min_freq_node->item_list.end()))
        {
            FreqIt<KeyT> freq_check = Freq_list.erase(min_freq_node);
        }

        return true;
    }

    //! Function for finding least used cache_items
    //! @return func executed without errors
    ListIt Find_least_used()
    {
        FreqIt<KeyT> min_freq_node = Freq_list.begin();
        ListIt min_used_item = min_freq_node->item_list.begin();

        return min_used_item;
        //Delete_least_used(min_used_item, min_freq_node);

        //return true;
    }



    //! Function for retie freq_node
    //! @param[in] item_it - iterator on list of cache_item, which helped retie current list
    //! @return func executed without errors
    bool Retie_freq_node(ListIt item_it)
    {
        FreqIt<KeyT> current_freq = item_it->Freq_head;
        FreqIt<KeyT> next_current_freq = ++current_freq;
        --current_freq;

        if ((next_current_freq != Freq_list.end() && (current_freq->freq_value + 1) == (next_current_freq->freq_value)))
        {
            if (!Retie_cache_item(current_freq, next_current_freq, item_it))
            {
                std::cout << "Error in add and delete func\n";
                abort();
            }
        }
        else
        {
            FreqIt<KeyT> real_next_freq = Freq_list.insert(next_current_freq, Freq_node<KeyT>(current_freq->freq_value + 1));

            if (!Retie_cache_item(current_freq, real_next_freq, item_it))
            {
                std::cout << "Error in add and delete func\n";
                abort();
            }
        }

        return true;
    }

    //! Function for retie cache_item
    //! @param[in] item_it - iterator on list of cache_item, which helped retie current list
    //! @param[in] cur_freq - iterator on list of freq_node
    //! @param[in] next_freq - next iterator(after cur_freq) on list of freq_node
    //! @return func executed without errors
    bool Retie_cache_item(FreqIt<KeyT> cur_freq, FreqIt<KeyT> next_freq, ListIt item_it)
    {
        struct Cache_item<KeyT> new_item(item_it->elem, next_freq);

        hash_tab.erase(item_it->elem);
        cur_freq->item_list.erase(item_it);

        next_freq->item_list.push_front(new_item);
        hash_tab[new_item.elem] = next_freq->item_list.begin();

        return true;
    }
};

#endif //_NEW_LFU_H_
