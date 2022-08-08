#pragma once
class SynergyManager
{
	DECLARE_SINGLETON(SynergyManager)

private:
	SynergyManager();
	~SynergyManager();

public:
	HRESULT Init_SynergyMgr();
	string Get_FullName(string name);

public:
	type_synergy Find_CharaSynergy(string strClassName);
	string Convert_SynergyName(type_synergy eType);

private:
	map<string, type_synergy> m_mapSynergy;
	map<string, string> m_mapFullName;
};

