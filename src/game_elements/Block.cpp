#include <Error.hpp>
#include "game_elements/Block.hpp"

Block::Block()
{
}

Block::Block(Block const & src)
{
	*this = src;
}

Block::Block(Model_Texture & texture, float x, float y, bool isBreakable): VisibleGameObject(texture, x, y, true, isBreakable)
{
	if (isBreakable)
		_type = breakableBlocks;
	else
		_type = unbreakableBlocks;
}

void Block::dying(float & elapsedTime)
{
	if(_timeTodie > 0)
	{
		_timeTodie -= elapsedTime;
		_model.Move(0, 0, -elapsedTime * _speed);
	}
	else
	{
		_isLoaded = false;
	}
}

void Block::Update(float & elapsedTime)
{
	if (_isDying)
		dying(elapsedTime);
}

BoundingBox Block::getBoundingBox()
{
	if (!isLoaded())
		throw Error::AssetError("Block Object Not Loaded");

	BoundingBox box;
	box.x1 = _model.GetPosition().x - 0.82;
	box.x2 = box.x1 + 0.82;

	box.y1 = _model.GetPosition().z - 0.82;
	box.y2 = box.y1 + 0.82;

	return box;
}

Block::~Block()
{
}