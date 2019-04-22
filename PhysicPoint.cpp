#include "pch.h"
#include "PhysicPoint.h"




PhysicPoint::~PhysicPoint()
{
}


bool PhysicPoint::onCollisionWall() {
	if (Position.x > 2 || Position.x < -2 || Position.y > 2 || Position.y < -2)
	{
		return true;
	}
	return false;
}


void PhysicPoint::AddForce(glm::vec2 Force) {

	this->Position += Force;
}