#pragma once
#include "Animal.h"
class Duck :
    public Animal
{
public:
    void move() override;       // express intention that this is an override
    void eat();
    Animal* clone() override;
    bool operator==(const Animal& obj) const override;
};

