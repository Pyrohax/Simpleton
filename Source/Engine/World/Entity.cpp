#include "Entity.h"

#include "../Core/Assert.h"
#include "Component.h"
#include "EntityFactory.h"

Entity::Entity(const std::string& aName, EntityFactory* anEntityFactory)
	: myName(aName)
	, myEntityFactory(anEntityFactory)
{
	std::random_device randomDevice;
	auto seedData = std::array<int, std::mt19937::state_size> {};
	std::generate(std::begin(seedData), std::end(seedData), std::ref(randomDevice));
	std::seed_seq seedSequence(std::begin(seedData), std::end(seedData));
	std::mt19937 mersenneTwisterGenerator(seedSequence);
	uuids::uuid_random_generator randomGenerator { mersenneTwisterGenerator };

	myUID = randomGenerator();
	Assert(myUID.is_nil(), "Generated UID is nil");
	Assert(myUID.as_bytes().size() != 16, "Generated UID size is faulty");
	Assert(myUID.version() != uuids::uuid_version::random_number_based, "Generated UID version is faulty");
	Assert(myUID.variant() != uuids::uuid_variant::rfc, "Generated UID variant is faulty");
}

Entity::~Entity()
{
}

void Entity::AddComponent(Component* aComponent)
{
	myEntityFactory->AddComponent(myUID, aComponent);
}
