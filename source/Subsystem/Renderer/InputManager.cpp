#include "InputManager.h"

#include <algorithm>

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

bool InputManager::GetIsKeyDown(int key) const
{
    bool result = false;
    std::map<int, bool>::const_iterator iterator = myKeys.find(key);
    if (iterator == myKeys.end())
        return false;

    return iterator->second;
}

void InputManager::OnKeyAction(int aKey, int /*aScancode*/, bool IsKeyDown, int /*aMode*/)
{
    myKeys.insert(std::pair<int, bool>(aKey, IsKeyDown));
}
