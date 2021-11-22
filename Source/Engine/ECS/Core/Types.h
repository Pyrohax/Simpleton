#pragma once

#include <bitset>
#include <uuid.h>

using UID = uuids::uuid::value_type;
const int MAX_ENTITIES = 100;
using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;
