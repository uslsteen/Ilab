#include "lfu.h"


int main()
{
    int hits = 0;
    int capacity, num_of_calls = 0;

    if (CUR_MODE == DEBUG)
        std::cout << "Input capacity of cache:" << std::endl;


    std::cin >> capacity;

    if (CUR_MODE == DEBUG)
        std::cout << "Input num of calls:" << std::endl;


    std::cin >> num_of_calls;

    Cache_t<Cache_item<int>, int> cache(capacity);

    if (CUR_MODE == DEBUG)
        std::cout<< "Input your request:" << std::endl;


    for (int i = 0; i < num_of_calls; ++i)
    {
        int page = 0;
        std::cin >> page;

        assert(std::cin.good());


    if (cache.Look_up(page))
            hits += 1;
    }

    std::cout << "Hits = " << hits << std::endl;
}







