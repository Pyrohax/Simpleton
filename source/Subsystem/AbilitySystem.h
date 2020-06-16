#pragma once
#include <unordered_map>
#include <functional>

#include "../Utility/TypeDefines.h"

class EntityComponentSystem;

enum class AbilityTag
{
	Any = 0,
	Player
};

class Ability
{
public:
	Ability(std::vector<AbilityTag> anAffectTags, std::vector<AbilityTag> anIgnoreTags, std::function<void(void)> anEffect, bool anAffectOverridesIgnore = false)
		: myAffectTags(anAffectTags)
		, myIgnoreTags(anIgnoreTags)
		, myEffect(anEffect)
		, myAffectOverridesIgnore(anAffectOverridesIgnore)
	{};

	// Affect tabs indicate that an effect should apply if there's a tag of the same type on it. Ignore tags indicate an entity should be ignored if the tags match.
	std::vector<AbilityTag> myAffectTags;
	std::vector<AbilityTag> myIgnoreTags;

	std::function<void(void)> myEffect;

	// If true, when an affect tag matches, immediately apply the effect without caring about the ignore tags.
	bool myAffectOverridesIgnore;
};

class AbilitySystem
{
public:
	AbilitySystem(EntityComponentSystem* anECS) : myEntityComponentSystem(anECS) {};
	
	bool StartAbilityOnEntity(const Ability& anAbility, const UniqueID aTargetEntity);

	bool AddTag(const AbilityTag aTag, const UniqueID anEntityID);
	bool HasTag(const AbilityTag aTag, const UniqueID anEntityID);

private:
	EntityComponentSystem* myEntityComponentSystem;
	std::unordered_map<UniqueID, std::vector<AbilityTag>*> myTagsTable;
};

