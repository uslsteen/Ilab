#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <ctime>

struct queries_t
{
    int frst, scnd;
};

using std::cout;
using std::cin;
using std::vector;

enum MODES_OF_CODEGEN
{
    RANDOM,
    IN_GRADUATE,
    QUANT = 4,
    DELTA = 2
};

const int MODE = RANDOM;

int main()
{
    int req_size = 0, quer_size = 0, max_req = 0, quer_fst = 0, quer_scnd = 0, req = 1, i = 0;

    //cout << "Input max value of req:\n";
    cin >> max_req;

    //cout << "Input size of requests:\n";
    cin >> req_size;

    //cout << "Input size of queiries:\n";
    cin >> quer_size;

    vector<int> reqs;
    vector<queries_t> quers;
    reqs.resize(req_size); quers.resize(quer_size);

    srand(clock());

    cout << req_size << "\n";

    switch(MODE)
    {
        case RANDOM:

            for (int i = 0; i < req_size; ++i)
            {
                reqs[i] = (rand() % max_req) + 1;
                cout << reqs[i] << " ";
            }


            cout << "\n" << quer_size << "\n";

            for (int i = 0; i < quer_size; ++i)
            {
                quers[i].frst = (rand() % max_req) + 1;
                quers[i].scnd = (rand() % max_req) + 1;

                if (quers[i].frst > quers[i].scnd)
                    std::swap(quers[i].frst, quers[i].scnd);

                else if (quers[i].frst == quers[i].scnd && quers[i].scnd != max_req)
                    quers[i].scnd++;

                else if (quers[i].frst == quers[i].scnd && quers[i].scnd == max_req)
                {
                    quers[i].scnd--;
                    quers[i].frst -= DELTA;

                }
                else if (quers[i].frst == quers[i].scnd)
                {
                  quers[i].scnd--;
                  quers[i].frst -= DELTA;
                }

                cout << quers[i].frst << " " << quers[i].scnd << " ";
            }

            break;

        case IN_GRADUATE:

            quer_size = 1;

            for (int i = 0; i < req_size; ++i, req+=QUANT)
            {
                reqs[i] = req;
                cout << reqs[i] << " ";
            }

            quer_fst = (rand() % max_req) + 1;
            quer_scnd = (rand() % max_req) + 1;

            if (quer_fst > quer_scnd)
                std::swap(quer_fst, quer_scnd);

            else if (quer_fst == quer_scnd && quer_scnd != max_req)
                quers[i].scnd++;

            cout << "\n" << quer_size << "\n";
            cout << quer_fst << " " << quer_scnd << " ";

            break;
    }
}
