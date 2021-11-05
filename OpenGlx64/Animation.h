#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>
#include <string>

#include "model.h"
#include "Entity.h"

using namespace std;

class Animation
{
private:
	vector<string>animation;
	int animIter = 0;
	vector<Model>animModels;
	int counter = 0;
	int frame;

public:
	Animation(vector<string>& s, int m_frame = 10);
	~Animation();

public:
	void animate(Entity& myEntity);
	void setAnimation(vector<string>& s);
	void setAnimModel();
};


#endif // !ANIMATION_H
