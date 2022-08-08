#pragma once
class Character
{
public:
	Character();
	~Character();

public:
	HRESULT Init_Character(string classname, type_synergy synergy, float level, int acc, int tripod);
	HRESULT Save_CharacterData(ofstream& fout);
	void Render_CharacterData();

public:
	string m_strClassName = "";
	type_synergy m_eSynergyType = NONE;

	float m_fItemLevel = 1415.f;
	int m_iAccCount = 0;
	int m_iTripodCount = 0;

#define ACC_SCORE 100.f
#define TRIPOD_SCORE 100.f
	float m_fCharacterScore = 0.f;

public:
	static Character* Create(string classname, type_synergy synergy, float level, int acc, int tripod);
};

