#ifndef GRID_H
#define GRID_H

#include "cell.h"
#include "point.h"

#include<vector>

class Grid
{
private:
    std::vector<std::unique_ptr<Cell>> m_cells{};
public:
    std::size_t index(Point p) const
    {
        return static_cast<std::size_t>(p.row * 9 + p.col);
    }
    int point_to_box(Point p) const { return 3 * (p.row / 3) + (p.col / 3); }

    const Cell* get_cell(Point p) const;
    Point find_cell(const Cell* cell) const;

    std::vector<Cell*> get_col(int col);
    std::vector<Cell*> get_row(int row);
    std::vector<Cell*> get_box(int box);

    std::vector<const Cell*> get_col(int col) const;
    std::vector<const Cell*> get_row(int row) const;
    std::vector<const Cell*> get_box(int box) const;

    Cell* get_cell(Point p) { return const_cast<Cell*>(const_cast<const Grid*>(this)->get_cell(p)); }

    void add_cell(int x = Cell::unset);
    bool is_cell_set(Point p) const { return get_cell(p)->is_set(); }

    void print() const;
    void print_row(int row) const;
    void print_col(int col) const;
    void print_box(int box) const;
};

#endif