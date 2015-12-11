#include "CollisionHandler.h"
#include "Util.h"

CollisionHandler::CollisionHandler()
{

}

bool CollisionHandler::isCollidable(int x, int y) const
{
	UNUSED(x);

	return y > 15;
}

