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

#define ġ�� CRI_UP
#define ��� DEF_DOWN
#define ���� DMG_UP
#define ���� ATT_UP
#define ����� BACK_HEAD
#define ���� SUP

typedef struct tagCharacter
{
	tagCharacter() {}
	tagCharacter(std::string str, float f, type_synergy e)
		:owner(str), score(f), synergy(e) {}

	std::string owner;
	float score;
	type_synergy synergy;
}CHARA;
