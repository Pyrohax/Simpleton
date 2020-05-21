#pragma once
#include "../Element/Component.h"

class ModelComponent : public Component
{
public:
	ModelComponent() {};
	~ModelComponent() {};

	bool Update() { return true; };
	void Destroy() {};

private:
	
};