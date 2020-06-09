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
		if (tag == AbilityTag::Any || HasTag(tag, aTargetEntity))
		{
			affectTagsMatch = true;
			break;
		}
	}

	if (!affectTagsMatch)
		return false;
	
	if (anAbility.myAffectOverridesIgnore)
	{
		anAbility.myEffect();
		return true;
	}

	for (auto tag : anAbility.myIgnoreTags)
	{
		if (tag == AbilityTag::Any || HasTag(tag, aTargetEntity))
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

	bool alreadyTagged = false;
	for (auto& i : *abilityTagList)
	{
		if (i == aTag)
		{
			alreadyTagged = true;
			break;
		}
	}

	if (alreadyTagged)
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