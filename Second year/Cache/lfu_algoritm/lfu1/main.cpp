#include "lfu.h"


void Pretty_simple_test();

std::string Check_Console_Args(int argc, char** argv);

int Download_test(std::string& name_of_in_file, std::vector<int>& pages, int& cap_of_cache, int& num_of_calls);

int main(int argc, char** argv)
{
    int cap_of_cache = 0, num_of_calls = 0;

    if (CUR_MODE == DEBUG)
    {
      std::cout << "Very simple test by hand" << "\n";
      Pretty_simple_test();
    }

    //std::string name_of_in_file = Check_Console_Args(argc, argv);
    std::vector<int> pages;
    std::string name_of_in_file = "/home/anon/ilab/Cache/lfu_algoritm/lfu1/tests/lfu_test8.txt";

    Download_test(name_of_in_file, pages, cap_of_cache, num_of_calls);
    assert(cap_of_cache > 0);

    if (cap_of_cache == 0)
    {
        std::cout << "Something went wrond and you downloaded cap_of_cache == 0\n";
        std::cout << "Is this a bug or a feature?\nCheck your tests in file" << name_of_in_file;

        return 0;
    }
    else
    {
        Cache_t<int> cache(cap_of_cache);

        int hits = cache.Test_processing(pages, num_of_calls);

        std::cout << "Test from file\n";
        std::cout << "Cache hits = " << hits << "\n";
    }

    return 0;
}



//! Function for testing lfu by simple tests

void Pretty_simple_test()
{
    int hits = 0;
    Cache_t<int> cache(3);

    if (cache.Look_up(1))
        hits++;

    if (cache.Look_up(2))
        hits++;

    if (cache.Look_up(3))
        hits++;

    if (cache.Look_up(3))
        hits++;

    if (cache.Look_up(2))
        hits++;

    if (cache.Look_up(1))
        hits++;

    std::cout << "Cache hits = " << hits << "\n";
}

//! Function checking console arguments

std::string Check_Console_Args(int argc, char** argv)
{
    std::string name_of_in_file;

    if (argc == 1)
    {
        std::cout << "Please, input name of your in_file?\n";
        std::cout << "For example \"input1.txt\".\n";

        std::cin >> name_of_in_file;
    }
    else
        name_of_in_file = argv[1];

    return name_of_in_file;
}

//! Function downloading test

int Download_test(std::string& name_of_in_file, std::vector<int>& pages, int& cap_of_cache, int& num_of_calls)
{
    std::ifstream test_file(name_of_in_file);

    if (!test_file.is_open())
    {
        std::cout << "Error with opening file" << name_of_in_file << "\n";
        return 0;
    }

    test_file >> cap_of_cache >> num_of_calls;

    pages.resize(num_of_calls);

    for (int i = 0; i < num_of_calls; ++i)
        test_file >> pages[i];

    test_file.close();
}
