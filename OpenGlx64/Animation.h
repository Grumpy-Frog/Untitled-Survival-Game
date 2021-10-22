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
	Animation(vector<string>& s,int m_frame = 10)
	{
		setAnimation(s);
		this->frame = m_frame;
	}
	~Animation()
	{
		this->animation.clear();
		this->animModels.clear();
	}

	void animate(Entity &myEntity)
	{
		if (this->counter >= this->frame)
		{
			myEntity.setModel(&animModels[this->animIter]);
			this->animIter++;
			if (this->animIter >= this->animModels.size())
			{
				this->animIter = 1;
			}
			this->counter = 0;
		}
		else
		{
			this->counter++;
		}
	}


public:
	void setAnimation(vector<string>& s)
	{
		this->animation = s;
	}

	void setAnimModel()
	{
		for (int i = 0; i < this->animation.size(); i++)
		{
			Model temp(animation[i]);
			this->animModels.push_back(temp);
		}
		//cout << animModels.size() << endl;
	}
};


#endif // !ANIMATION_H
