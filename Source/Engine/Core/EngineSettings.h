#pragma once

#include "SerializableData.h"

#include <string>

class EngineSettings : public SerializableData
{
public:
    EngineSettings();
    ~EngineSettings();

    void Serialize() override;
    void Deserialize() override;

public:
    std::string myFilepath;
    std::string myVersion;
    int myDefaultViewportHeight;
    int myDefaultViewportWidth;
};
