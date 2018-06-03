#pragma once

class Digit {
private:
    char lower;
    char upper;

public:
    Digit() : lower('\0'), upper('\0') {}
    Digit(char lower, char upper) : lower(lower), upper(upper) {}
    bool contains(char c)
    {
        return c >= lower && c <= upper;
    }

    bool isLessThan(char c)
    {
        return upper < c;
    }

    bool isGreaterThan(char c)
    {
        return lower > c;
    }
};
