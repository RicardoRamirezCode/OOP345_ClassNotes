#pragma once
#include "Tiger.h"
class MechanicalTiger :
    public Tiger
{
        
    // no need to write move() whatever Tiger does for move MechnicalTiger will as well

    // issue is that eat() is not needed here; it's mechanical and doesn't need to eat so we don't need that function
    // we can not remove members; when we inherit from a class we get everything from that class (except special functions)
    // this is an issue that can only be fixed in design

};

