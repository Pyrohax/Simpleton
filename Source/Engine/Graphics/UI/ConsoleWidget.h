#pragma once

#include "Widget.h"

class ImguiWrapper;

namespace UI
{
	class ConsoleWidget : public Widget
	{
	public:
		ConsoleWidget(ImguiWrapper* aWrapper, const std::string& aTitle);
		~ConsoleWidget();

		void Tick() override;

	private:
		std::string myTitle;
	};
}
