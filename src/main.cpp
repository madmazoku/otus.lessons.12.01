// otus.lessons.12.01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/program_options.hpp>
#include <iostream>

#ifdef __unix__
#include "../bin/version.h"
#else
#include "in.version.h"
#endif

#include "sparse_matrix.h"

void do_matrix();

int main(int argc, char** argv)
{
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
    ("help,h", "print usage message")
    ("version,v", "print version number");

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
    } else if (vm.count("version")) {
        std::cout << "Build version: " << build_version() << std::endl;
        std::cout << "Boost version: " << (BOOST_VERSION / 100000) << '.' << (BOOST_VERSION / 100 % 1000) << '.' << (BOOST_VERSION % 100) << std::endl;
    } else {

        do_matrix();

    }

#ifndef __unix__
    getchar();
#endif

    return 0;
}

void do_matrix()
{
    sparse_matrix<2,int, 0> sm;
    for(size_t n = 0; n <= 9; ++n) {
        sm[n][n] = n;
        sm[n][9-n] = 9-n;
    }

    for(size_t y = 1; y <= 8; ++y) {
        for(size_t x = 1; x <= 8; ++x) {
            if(x != 1)
                std::cout << ' ';
            std::cout << sm[x][y];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "matrix size: " << sm.size() << std::endl;
    std::cout << std::endl;

    for(auto e : sm) {
        size_t x, y;
        std::tie(x, y) = e.first;
        std::cout << "matrix[" << x << ", " << y << "] = " << e.second << std::endl;
    }
}