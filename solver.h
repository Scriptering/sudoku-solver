#ifndef SOLVER_H
#define SOLVER_H

#include "grid.h"
#include "cell.h"
#include "point.h"
#include<string_view>

class Solver
{
private:
    Grid m_grid{};

public:
    void create_grid(std::string_view grid);
    void print() const { m_grid.print(); }
    void print_row(int row) const { m_grid.print_row(row); }
    void print_col(int col) const { m_grid.print_col(col); }
    void print_box(Point p) const { m_grid.print_box(m_grid.point_to_box(p)); }

    void set_cell(Cell* cell, int value);

    void clear_bits();
    void clear_bits(const Cell* cell);
    void clear_bits(int x, std::vector<Cell*> cells);

    void set_singles();
    void set_lonely_bits();
    void set_lonely_bits(int x, std::vector<Cell*> cells);

    bool is_complete() const;
    void solve(bool print_steps);

};

#endif