#include "AbilitySystem.h"

bool AbilitySystem::StartAbilityOnEntity(const Ability& anAbility, const UniqueID aTargetEntity)
{
	/*const Entity* affectedEntity = myEntityComponentSystem->GetEntity(aTargetEntity);
	if (!affectedEntity || !anAbility.myEffect)
		return false;*/

	bool affectTagsMatch = false;
	
	for (const AbilityTag& tag : anAbility.myAffectTags)
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

	for (const AbilityTag& tag : anAbility.myIgnoreTags)
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
	for (const AbilityTag& tag : *abilityTagList)
	{
		if (tag == aTag)
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
	const std::vector<AbilityTag>* abilityTagList = myTagsTable[anEntityID];
	if (!abilityTagList)
		return false;

	for (const AbilityTag& tag : *abilityTagList)
	{
		if (tag == aTag)
		{
			return true;
		}
	}
	return false;
}