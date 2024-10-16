#pragma once
#include <SupergoonEngine/prim/point.h>
#include <box2d/id.h>
#include <box2d/types.h>

#include <Supergoon/Vector2.hpp>

namespace Supergoon {
class Level;
class RigidbodyComponent {
   public:
	RigidbodyComponent(Level& level, gePoint size = gePoint{0, 0}, Vector2 loc = Vector2(0));
	~RigidbodyComponent();
	Vector2 Location();
	gePoint Size();
	void SetVelocity(Vector2 vel);
	void ApplyForceToBody(Vector2 force);

   private:
	gePoint _size;
	b2BodyId _body;
};
}  // namespace Supergoon
