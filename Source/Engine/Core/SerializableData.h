#pragma once

#include <memory>

class SerializableData : public std::enable_shared_from_this<SerializableData>
{
public:
	SerializableData() {};
	virtual ~SerializableData() = default;

	virtual void Serialize() = 0;
	virtual void Deserialize() = 0;
};
