#include "lfu.h"

int main()
{
    int hits = 0;
    int capacity, num_of_calls = 0;

    std::cout << "Insert capacity of cache:" << std::endl;
    std::cin >> capacity;

    std::cout << "Insert num of calls:" << std::endl;
    std::cin >> num_of_calls;

    Cache_t cache(capacity);

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







