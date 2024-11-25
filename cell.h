#ifndef CELL_H
#define CELL_H

#include<bitset>
#include<iostream>
#include"myfuncs.h"

using value_t = int;

class Cell
{
public:
    static const int unset{ -1 };

private:

    value_t m_value{ unset };
    std::bitset<9> m_bits{ std::bitset<9>{}.set() };

public:
    Cell() = default;
    Cell(value_t value)
        : m_value{ value }
    {
    }

    value_t get_value() const { return m_value; }
    value_t get_value_bit() const;

    bool is_set() const { return m_value != unset; }
    void set(int value) { m_value = value; }

    void remove_bit(int i) { m_bits.reset(i_to_s(i)); };

    std::bitset<9>& get_bits() { return m_bits; }
    bool has_bit(int bit) const { return m_bits.test(static_cast<std::size_t>(bit)); }
    int get_bit_count() const { return s_to_i(m_bits.count()); }

    friend std::ostream& operator<<(std::ostream& out, const Cell* cell);
};

#endif