//
// Created by Patrick Russell on 2018/09/25.
//

#ifndef BOMBERMAN_PIPE_HPP
#define BOMBERMAN_PIPE_HPP


#include "VisibleGameObject.hpp"

class Pipe: public VisibleGameObject
{
public:
	Pipe();
	Pipe(Pipe const & src);
	~Pipe();
	Pipe(Model_Texture & texture, float x, float y);
	BoundingBox getBoundingBox();
};


#endif //BOMBERMAN_PIPE_HPP
