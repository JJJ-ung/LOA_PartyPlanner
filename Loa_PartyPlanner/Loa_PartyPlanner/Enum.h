#pragma once

enum type_synergy
{
	NONE = 0,
	CRI_UP,
	DEF_DOWN,
	DMG_UP,
	ATT_UP,
	BACK_HEAD,
	SUP
};

#define 치적 CRI_UP
#define 방깍 DEF_DOWN
#define 피증 DMG_UP
#define 공증 ATT_UP
#define 백헤드 BACK_HEAD
#define 서폿 SUP

typedef struct tagCharacter
{
	tagCharacter() {}
	tagCharacter(std::string str, float f, type_synergy e)
		:owner(str), score(f), synergy(e) {}

	std::string owner;
	float score;
	type_synergy synergy;
}CHARA;
