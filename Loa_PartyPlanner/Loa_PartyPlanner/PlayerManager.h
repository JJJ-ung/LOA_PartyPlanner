#pragma once
//#include "Character.h"
class Character;
class PlayerManager
{
	DECLARE_SINGLETON(PlayerManager)

private:
	PlayerManager();
	~PlayerManager();

public:
	HRESULT Init_PlayerMgr();
	HRESULT Add_Character();
	HRESULT Render_CharacterList();

public:
	HRESULT Start_CharacterParty();
	HRESULT Make_CharacterParty(float fLevel, int iCnt, bool bCheck);

public:
	HRESULT Save_PlayerMap();

private:
	map<string, list<Character*>> m_mapPlayers;
};

