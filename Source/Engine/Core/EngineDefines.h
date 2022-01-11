#pragma once

#include <bitset>
#include <uuid.h>

#define MAX_ENTITIES 100
#define MAX_COMPONENTS 32

using UID = uuids::uuid::value_type;
using ComponentType = uuids::uuid::value_type;
using EntitySignature = std::bitset<MAX_COMPONENTS>;
