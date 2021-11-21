#include "PhysicsSystem.h"

#include "../../World/TransformComponent.h"
#include "../Core/Coordinator.h"

extern Coordinator gCoordinator;

void PhysicsSystem::Update()
{
	/*for (auto const& entity : myEntities)
	{
		auto& transform = gCoordinator.GetComponent<TransformComponent>(entity);
		glm::vec3 position = transform.GetPosition();
		position += 1.0f * aDeltaTime;
		transform.SetPosition(position);
	}*/
}
