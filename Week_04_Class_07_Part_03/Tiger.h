#ifndef TIGER_H
#define TIGER_H

#include "Animal.h"
class Tiger :
    public Animal
{
    // need to make concrete class so need to offer implemenation of move()
    void move() override;

    // this eat now shadows the base class implemenation of eat()
    // this eat in Tiger is a completely new function and shadows the function eat() of base class
    void eat();

    // override means virtual; no virtual no override
    // same prototype would be shadowing


    // Part 02
    Animal* clone() override;

    // Part 03
    bool operator==(const Animal& obj) const override;

};

#endif // !TIGER_H


