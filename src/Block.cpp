#include <Error.hpp>
#include "Block.hpp"

Block::Block()
{
}

Block::Block(Model_Texture & texture, float x, float y, bool isBreakable): VisibleGameObject(texture, x, y, true, isBreakable)
{
	if (isBreakable)
		_type = breakableBlocks;
	else
		_type = unbreakableBlocks;
}

BoundingBox Block::getBoundingBox()
{
	if (!isLoaded())
		throw Error::AssetError("Block Object Not Loaded");

	BoundingBox box;
	box.x1 = _model.GetPosition().x - 0.32;
	box.x2 = box.x1 + 0.32;

	box.y1 = _model.GetPosition().z - 0.32;
	box.y2 = box.y1 + 0.32;

	return box;
}

Block::~Block()
{
}