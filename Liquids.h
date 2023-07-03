#ifndef LIQUIDS_H
#define LIQUIDS_H

#include <iostream>

constexpr size_t TUBE_CAPACITY = 4;

const std::string LIQUIDS[] = {
    "LIGHTGREEN",
    "GREEN",
    "DARKGREEN",
    "LIGHTBLUE",
    "BLUE",
    "PURPLE",
    "PINK",
    "RED",
    "ORANGE",
    "YELLOW",
    "BROWN",
    "GREY",
    "WHITE",
};
const size_t LIQUIDS_NUM = sizeof(LIQUIDS) / sizeof(LIQUIDS[0]);

int getLiquidId(const std::string& name)
{
    for (int i = 0; i < LIQUIDS_NUM; i++)
    {
        if (name == LIQUIDS[i])
        {
            return i;
        }
    }
    return -1;
}

#endif // LIQUIDS_H