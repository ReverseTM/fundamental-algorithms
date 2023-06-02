#ifndef BIG_INT_H
#define BIG_INT_H

class big_int
{

private:



public:

    virtual big_int * add(big_int const * const summand) = 0;

    virtual big_int * subtract(big_int const * const subtrahend) = 0;

public:

    virtual bool lower_than(big_int const * const other) const = 0;

    virtual bool greater_than(big_int const * const other) const = 0;

    virtual bool lower_than_or_equal_to(big_int const * const other) const = 0;

    virtual bool greater_than_or_equal_to(big_int const * const other) const = 0;

    virtual bool equals(big_int const * const other) const = 0;

    virtual bool not_equals(big_int const * const other) const = 0;

public:

    big_int * sum(big_int const * const summand) const;

    big_int * subtraction(big_int const * const subtrahend) const;


public:

    big_int * operator+=(big_int const * const summand);
    big_int * operator+(big_int const * const summand);

    big_int * operator-=(big_int const * const subtrahend);
    big_int * operator-(big_int const * const subtrahend);

    bool operator<(big_int const * const other);
    bool operator>(big_int const * const other);
    bool operator<=(big_int const * const other);
    bool operator>=(big_int const * const other);

    bool operator==(big_int const * const other);
    bool operator!=(big_int const * const other);

};


#endif //BIG_INT_H
