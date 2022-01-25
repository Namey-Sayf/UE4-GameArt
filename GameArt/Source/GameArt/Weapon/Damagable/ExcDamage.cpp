#include "ExcDamage.h"

void ExcDamage::ApplyDamage(const FWParams& wParam, FLifeParams& npcParam)
{
	const auto health = npcParam.GetHealth() - wParam.GetDamage();
	npcParam.SetHealth(health);
}

