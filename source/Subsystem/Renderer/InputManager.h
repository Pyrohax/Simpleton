#pragma once

#include <map>

class InputManager
{
public:
    static InputManager& GetInstance()
    {
        static InputManager instance;
        return instance;
    }

    InputManager(InputManager const&) = delete;
    void operator=(InputManager const&) = delete;

    bool GetIsKeyDown(int key) const;
    void OnKeyAction(int aKey, int, bool IsKeyDown, int);

    void Clear() { myKeys.clear(); }

private:
    InputManager();
    ~InputManager();

private:
    std::map<int, bool> myKeys;
};
