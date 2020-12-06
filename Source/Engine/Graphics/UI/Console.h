#pragma once

#include "Widget.h"

class ImguiWrapper;

namespace UI
{
	class Console : public Widget
	{
	public:
		Console(ImguiWrapper* aWrapper);
		~Console();

		void Tick() override;

	private:

	};
}
