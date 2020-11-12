#pragma once

class Renderer
{
public:
	virtual ~Renderer() = default;

	virtual void Initialize() = 0;
	virtual void Update(double aDeltaTime) = 0;
	virtual void Terminate() = 0;
};
