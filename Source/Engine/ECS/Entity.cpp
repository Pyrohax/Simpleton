#include "Entity.h"

#include "../Core/Assert.h"

Entity::Entity(const std::string& aName)
	: myName(aName)
{
	std::random_device rd;
	auto seed_data = std::array<int, std::mt19937::state_size> {};
	std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
	std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
	std::mt19937 generator(seq);
	uuids::uuid_random_generator gen{ generator };

	myUID = gen();
	Assert(myUID.is_nil(), "Generated UID is nil");
	Assert(myUID.as_bytes().size() != 16, "Generated UID size is faulty");
	Assert(myUID.version() != uuids::uuid_version::random_number_based, "Generated UID version is faulty");
	Assert(myUID.variant() != uuids::uuid_variant::rfc, "Generated UID variant is faulty");
}

Entity::~Entity()
{
}
