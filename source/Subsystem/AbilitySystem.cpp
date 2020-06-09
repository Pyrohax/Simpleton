#include "AbilitySystem.h"
#include "EntityComponentSystem.h"

bool AbilitySystem::StartAbilityOnEntity(Ability anAbility, const UniqueID aTargetEntity)
{
	Entity* affectedEntity = myEntityComponentSystem->GetEntity(aTargetEntity);
	if (!affectedEntity || !anAbility.myEffect)
		return false;

	bool affectTagsMatch = false;
	for (auto tag : anAbility.myAffectTags)
	{
		if (HasTag(tag, aTargetEntity))
		{
			if (anAbility.myAffectOverridesIgnore)
			{
				anAbility.myEffect();
				return true;
			}
			affectTagsMatch = true;
			break;
		}
	}

	if (!affectTagsMatch)
		return false;

	for (auto tag : anAbility.myIgnoreTags)
	{
		if (HasTag(tag, aTargetEntity))
		{
			return false;
		}
	}

	anAbility.myEffect();
	return true;
}

bool AbilitySystem::AddTag(const AbilityTag aTag, const UniqueID anEntityID)
{
	std::vector<AbilityTag>* abilityTagList = myTagsTable[anEntityID];
	if (!abilityTagList)
	{
		myTagsTable.emplace(anEntityID, nullptr);
		myTagsTable[0] = new std::vector<AbilityTag>{ aTag };
		return true;
	}

	bool alreadyAffected = false;
	for (auto& i : *abilityTagList)
	{
		if (i == aTag)
		{
			alreadyAffected = true;
			break;
		}
	}

	if (alreadyAffected)
		return false;

	abilityTagList->push_back(aTag);
	return true;
}

bool AbilitySystem::HasTag(const AbilityTag aTag, const UniqueID anEntityID)
{
	std::vector<AbilityTag>* abilityTagList = myTagsTable[anEntityID];
	if (!abilityTagList)
		return false;

	bool alreadyAffected = false;
	for (auto& i : *abilityTagList)
	{
		if (i == aTag)
		{
			return true;
		}
	}
	return false;
}