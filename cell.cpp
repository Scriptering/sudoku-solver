#include "cell.h"
#include "myfuncs.h"

std::ostream& operator<<(std::ostream& out, const Cell* cell)
{
    if (cell->is_set())
        out << cell->get_value() + 1;
    else
        out << '?';

    return out;
}

value_t Cell::get_value_bit() const
{
    for (value_t s{}; s < 9; s++)
    {
        if (m_bits.test(i_to_s(s)))
        {
            return s;
        }
    }

    return 9;
}