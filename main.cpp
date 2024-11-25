#include<iostream>
#include<fstream>
#include<chrono>
#include<unordered_map>

#include "solver.h"

bool is_numeric(char c)
{
    return '1' <= c && c <= '9';
}

bool is_empty(char c)
{
    return c == '?';
}

std::string get_grid_string(std::ifstream& in)
{
    std::string values{};

    char c{};
    while (!in.eof())
    {
        in >> c;
        if (is_numeric(c))
            values += c;

        else if (is_empty(c))
            values += '0';
    }

    return values;
}

int main()
{
    std::ifstream in{ "test_sudokus/hard.txt" };

    if (!in) { return 1; }

    std::string values{ get_grid_string(in) };

    Solver solver{};
    solver.create_grid(values);
    solver.print();
    solver.solve(false);
    solver.print();

    return 0;
}