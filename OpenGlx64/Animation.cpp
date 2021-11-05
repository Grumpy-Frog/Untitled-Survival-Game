#include "Animation.h"

Animation::Animation(vector<string>& s, int m_frame)
{
	setAnimation(s);
	this->frame = m_frame;
}

Animation::~Animation()
{
	this->animation.clear();
	this->animModels.clear();
}

void Animation::animate(Entity& myEntity)
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

void Animation::setAnimation(vector<string>& s)
{
	this->animation = s;
}


void Animation::setAnimModel()
{
	for (int i = 0; i < this->animation.size(); i++)
	{
		Model temp(animation[i]);
		this->animModels.push_back(temp);
	}
	//cout << animModels.size() << endl;
}