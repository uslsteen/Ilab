#include "lfu.h"


int main()
{
    int hits = 0;
    int capacity, num_of_calls = 0;
    int res = 0;
    FILE* in, * out;

    if (CUR_MODE == RELEASE)
    {
        if ((in = fopen("/home/anon/ilab/Cache/lfu_algoritm/tests_for_lfu/input.txt", "r")) == nullptr)
        {
            printf("Error in open file \"input.txt\"\n");
            return 0;
        }

        if ((out = fopen("/home/anon/ilab/Cache/lfu_algoritm/tests_for_lfu/output.txt", "w")) == nullptr)
        {
            printf("Error in open \"output.txt\"\n");
            return 0;
        }

        res = fscanf(in, "%d", &capacity);
        assert(res == 1);
        assert(capacity > 0);

        res = fscanf(in, "%d", &num_of_calls);
        assert(res == 1);
    }
    else if (CUR_MODE == DEBUG)
    {
        std::cout << "Input capacity of cache:" << std::endl;
        std::cin >> capacity;

        std::cout << "Input num of calls:" << std::endl;
        std::cin >> num_of_calls;
    }

    Cache_t<Cache_item<int>, int> cache(capacity);

    if (CUR_MODE == DEBUG)
        std::cout<< "Input your request:" << std::endl;


    for (int i = 0; i < num_of_calls; ++i)
    {
        int page = 0;

        if (CUR_MODE == DEBUG)
        {
            std::cin >> page;
            assert(std::cin.good());
        }
        else if (CUR_MODE == RELEASE)
        {
            res = fscanf(in, "%d", &page);
            assert(res == 1);
        }

        if (cache.Look_up(page))
            hits += 1;
    }

    if (CUR_MODE == DEBUG)
        std::cout << "Hits = " << hits << std::endl;
    else if (CUR_MODE == RELEASE)
        fprintf(out, "Cache hits: %d\n", hits);
}







