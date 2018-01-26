// otus.lessons.12.01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "sparse_matrix.h"

int main(int argc, char** argv)
{
    auto a = std::make_tuple(1, 2, 3);
    auto b = std::tuple_cat(a, std::make_tuple(4));

    std::cout << std::tuple_size<decltype(b)>() << std::endl;

    sparce_matrix<3, int, -1> sm;

    sm._matrix[std::make_tuple(2, 3, 1)] = 1;
    sm._matrix[std::make_tuple(3, 1, 2)] = 2;
    sm._matrix[std::make_tuple(1, 2, 3)] = 3;

    sm[5][6][4] = (sm[6][4][5] = sm[4][5][6] = 7) + 1;

    std::cout << "[4][5][6]: " << sm[4][5][6] << std::endl;
    std::cout << "[7][8][9]: " << sm[7][8][9] << std::endl;

    std::cout << "size: " << sm.size() << std::endl;
    sm[2][3][1] = -1;
    sm[3][1][2] = -1;
    std::cout << "size: " << sm.size() << std::endl;

    for (auto e : sm) {
        int x, y, z, t;
        std::tie(x, y, z) = e.first;
        t = e.second;
        std::cout << "x: " << x << "; y: " << y << "; z: " << z << "; t: " << t << std::endl;
    }

    getchar();
    return 0;
}

