#pragma once
#include "LifeParams.h"
#include "WParams.h"


class ExcDamage
{
public:
	static void ApplyDamage(const FWParams& wParam, FLifeParams& npcParam);
};
