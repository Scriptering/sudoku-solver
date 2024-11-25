#include "grid.h"
#include "cell.h"
#include "point.h"

#include<iostream>
#include<cassert>

const Cell* Grid::get_cell(Point p) const
{
    assert(0 <= p.col && p.col <= 9 && "x out of range");
    assert(0 <= p.row && p.row <= 9 && "y out of range");
    assert(m_cells[index(p)] && "null cell");

    return m_cells[index(p)].get();
}

Point Grid::find_cell(const Cell* cell) const
{
    for (int row{}; row < 9; row++)
    {
        for (int col{}; col < 9; col++)
        {
            if (cell == get_cell({ row, col }))
                return { row, col };
        }
    }

    return { -1, -1 };
}

void Grid::add_cell(int x)
{
    m_cells.push_back(std::make_unique<Cell>(x));
}

void Grid::print() const
{
    for (int i{}; i < 9; i++)
    {
        for (int j{}; j < 9; j++)
        {
            const Cell* cell{ get_cell({i, j}) };

            std::cout << cell;

            if (j == 2 || j == 5)
                std::cout << '|';
        }
        std::cout << '\n';

        if (i == 2 || i == 5)
        {
            std::cout << "-----------\n";
        }
    }
    std::cout << "\n\n";
}

void Grid::print_row(int row) const
{
    for (auto* cell : get_row(row))
    {
        std::cout << cell;
    }
}
void Grid::print_col(int col) const
{
    for (auto* cell : get_col(col))
    {
        std::cout << cell;
    }
}
void Grid::print_box(int box) const
{
    for (auto* cell : get_box(box))
    {
        std::cout << cell;
    }
}

std::vector<Cell*> Grid::get_row(int row)
{
    std::vector<Cell*> cells{};

    for (int col{}; col < 9; col++)
    {
        cells.push_back(get_cell({ row, col }));
    }

    return cells;
}

std::vector<Cell*> Grid::get_col(int col)
{
    std::vector<Cell*> cells{};

    for (int row{}; row < 9; row++)
    {
        cells.push_back(get_cell({ row, col }));
    }

    return cells;
}

std::vector<Cell*> Grid::get_box(int box)
{
    std::vector<Cell*> cells{};

    int col_start{ 3 * (box % 3) };
    int row_start{ 3 * (box / 3) };

    for (int col{ col_start }; col < col_start + 3; col++)
    {
        for (int row{ row_start }; row < row_start + 3; row++)
        {
            cells.push_back(get_cell({ row, col }));
        }
    }

    return cells;
}

std::vector<const Cell*> Grid::get_row(int row) const
{
    std::vector<const Cell*> cells{};

    for (int col{}; col < 9; col++)
    {
        cells.push_back(get_cell({ row, col }));
    }

    return cells;
}

std::vector<const Cell*> Grid::get_col(int col) const
{
    std::vector<const Cell*> cells{};

    for (int row{}; row < 9; row++)
    {
        cells.push_back(get_cell({ row, col }));
    }

    return cells;
}

std::vector<const Cell*> Grid::get_box(int box) const
{
    std::vector<const Cell*> cells{};

    int col_start{ 3 * (box / 3) };
    int row_start{ 3 * (box % 3) };

    for (int col{ col_start }; col < col_start + 3; col++)
    {
        for (int row{ row_start }; row < row_start + 3; row++)
        {
            cells.push_back(get_cell({ row, col }));
        }
    }

    return cells;
}