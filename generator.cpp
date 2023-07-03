#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "Liquids.h"

int random(int from, int to)
{
    static std::random_device dev;
    static std::mt19937 gen(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(from, to - 1);
    return dist(gen);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Input required\n");
        return 1;
    }

    int K = std::stoi(argv[1]);
    std::cout << K << '\n';

    std::vector<std::vector<int>> liqs(K);
    for (int i = 0; i < K; i++)
    {
        liqs[i] = std::vector<int>(TUBE_CAPACITY, i);
    }

    std::vector<std::vector<int>> tubes(K);

    while (!liqs.empty())
    {
        int liq = random(0, liqs.size());
        int tube = random(0, tubes.size());

        tubes[tube].push_back(liqs[liq].back());
        liqs[liq].pop_back();
        if (liqs[liq].empty())
        {
            liqs.erase(liqs.begin() + liq);
        }

        if (tubes[tube].size() == TUBE_CAPACITY)
        {
            for (const auto& part : tubes[tube])
            {
                #ifdef NUMBERS
                std::cout << part << ' ';
                #else
                std::cout << LIQUIDS[part] << ' ';
                #endif
            }
            std::cout << '\n';

            tubes.erase(tubes.begin() + tube);
        }
    }

    return 0;
}