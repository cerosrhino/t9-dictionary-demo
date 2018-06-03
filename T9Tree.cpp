#include "T9Tree.h"

const char T9Tree::NUMERIC_ASCII_OFFSET = '0';

Digit T9Tree::digits[10] = {
    Digit(),
    Digit(),
    Digit('a', 'c'),
    Digit('d', 'f'),
    Digit('g', 'i'),
    Digit('j', 'l'),
    Digit('m', 'o'),
    Digit('p', 's'),
    Digit('t', 'v'),
    Digit('w', 'z')
};
