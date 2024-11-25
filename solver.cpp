#include "solver.h"
#include "point.h"

#include<cassert>

void Solver::create_grid(std::string_view values)
{
    for (char c : values)
    {
        value_t x{ static_cast<value_t>(c - '0') };

        if (x)
        {
            m_grid.add_cell(x - 1);
        }
        else
            m_grid.add_cell();
    }
}

void Solver::clear_bits()
{
    for (int row{}; row < 9; row++)
    {
        if (!(m_grid.get_cell({ 4, 1 })->has_bit(0)))
        {
            std::cout << static_cast<int>(m_grid.get_cell({ 0, 4 })->has_bit(0));
            row = static_cast<int>(row);
        }

        for (const auto* cell : m_grid.get_row(row))
        {
            if (cell->is_set())
                clear_bits(cell);
        }
    }
}

void Solver::clear_bits(const Cell* cell)
{
    if (!cell->is_set())
        return;

    if (cell->get_value() == 0)
    {
        i_to_s(5);
    }

    Point p{ m_grid.find_cell(cell) };

    clear_bits(cell->get_value(), m_grid.get_row(p.row));
    clear_bits(cell->get_value(), m_grid.get_col(p.col));
    clear_bits(cell->get_value(), m_grid.get_box(m_grid.point_to_box(p)));
}

void Solver::clear_bits(int x, std::vector<Cell*> cells)
{
    for (auto* cell : cells)
    {
        if (cell->is_set())
            continue;

        cell->remove_bit(x);
    }
}

void Solver::set_singles()
{
    for (int row{}; row < 9; row++)
    {
        for (auto* cell : m_grid.get_row(row))
        {
            if (cell->get_bit_count() == 1)
                set_cell(cell, cell->get_value_bit());
        }
    }
}

void Solver::set_lonely_bits()
{
    for (int x{}; x < 9; x++)
    {
        for (int row{}; row < 9; row++)
            set_lonely_bits(x, m_grid.get_row(row));

        for (int col{}; col < 9; col++)
            set_lonely_bits(x, m_grid.get_col(col));

        for (int box{}; box < 9; box++)
            set_lonely_bits(x, m_grid.get_box(box));
    }
}

void Solver::set_lonely_bits(int x, std::vector<Cell*> cells)
{
    int count{};
    Cell* to_set_cell{};

    for (Cell* cell : cells)
    {
        if (cell->is_set())
        {
            if (cell->get_value() == x)
                return;

            continue;
        }

        if (cell->has_bit(x))
        {
            count++;
            if (count > 1)
                return;

            to_set_cell = cell;
        }
    }

    if (!to_set_cell)
        return;

    set_cell(to_set_cell, x);
}

void Solver::set_cell(Cell* cell, int x)
{
    if (cell->is_set())
        return;

    cell->set(x);

    clear_bits(cell);
}

bool Solver::is_complete() const
{
    for (int row{}; row < 9; row++)
    {
        for (const auto* cell : m_grid.get_row(row))
        {
            if (!cell->is_set())
                return false;
        }
    }

    return true;
}

void Solver::solve(bool print_steps)
{
    const int max_loops{ 10 };

    clear_bits();

    for (int i{}; i < max_loops; i++)
    {
        if (is_complete())
            break;

        set_singles();
        set_lonely_bits();

        if (print_steps)
            print();
    }
}

