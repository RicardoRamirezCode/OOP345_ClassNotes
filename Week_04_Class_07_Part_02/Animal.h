#ifndef ANIMAL_H
#define ANIMAL_H

class Animal
{
public:
	
	virtual void move() = 0;		// since each derived class of animal will have a different way of moving

	void eat();
};

#endif // !ANIMAL_H


