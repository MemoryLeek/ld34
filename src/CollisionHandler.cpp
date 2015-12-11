#include "CollisionHandler.h"
#include "Util.h"

CollisionHandler::CollisionHandler()
{

}

bool CollisionHandler::isCollidable(int x, int y) const
{
	UNUSED(x);

	return (x < 15 && y > 10) || y > 15;
}

