#include "Framework.h"
#include "SynergyManager.h"

IMPLEMENT_SINGLETON(SynergyManager)

SynergyManager::SynergyManager()
{
	m_mapFullName.insert({ "배마", "배틀마스터" });
	m_mapFullName.insert({ "창술", "창술사" });
	m_mapFullName.insert({ "데헌", "데빌헌터" });
	m_mapFullName.insert({ "데몬헌터", "데빌헌터" });
	m_mapFullName.insert({ "레몬버터", "데빌헌터" });
	m_mapFullName.insert({ "알카", "아르카나" });
	m_mapFullName.insert({ "건슬", "건슬링어" });
	m_mapFullName.insert({ "기상", "기상술사" });
	m_mapFullName.insert({ "블래", "블래스터" });
	m_mapFullName.insert({ "섬너", "서머너" });
	m_mapFullName.insert({ "디트", "디스트로이어" });
	m_mapFullName.insert({ "충모닉", "데모닉" });
	m_mapFullName.insert({ "억모닉", "데모닉" });
	m_mapFullName.insert({ "호크", "호크아이" });
	m_mapFullName.insert({ "인파", "인파이터" });
	m_mapFullName.insert({ "소서", "소서리스" });
	m_mapFullName.insert({ "기공", "기공사" });
	m_mapFullName.insert({ "스카", "스카우터" });
	m_mapFullName.insert({ "블레", "블레이드" });
	m_mapFullName.insert({ "홀나", "홀리나이트" });
	m_mapFullName.insert({ "도아가", "도화가" });
}

SynergyManager::~SynergyManager()
{
	m_mapSynergy.clear();
}

HRESULT SynergyManager::Init_SynergyMgr()
{
	locale::global(locale("Korean"));

	string path = PathToString();
	path.append("\\Synergy_List.dat");

	ifstream fin(path);
	if (!fin)
	{
		cout << " * ERROR : 시너지 데이터 확인 실패" << endl;
		return E_FAIL;
	}

	int synergy = 0;
	string name = "";
	while(true)
	{
		fin >> name >> synergy;

		if (fin.eof())
			break;

		m_mapSynergy.insert({ name, (type_synergy)synergy });
	}

	cout << " * 시너지 데이터 확인 성공 " << endl;

	fin.close();

	return NOERROR;
}

string SynergyManager::Get_FullName(string name)
{
	auto p = m_mapFullName.find(name);
	if (p == m_mapFullName.end())
		return name;
	return p->second;
}

type_synergy SynergyManager::Find_CharaSynergy(string strClassName)
{
	auto iter = m_mapSynergy.find(strClassName);

	if(iter == m_mapSynergy.end())
	{
		cout << " * 해당 직업을 찾을 수 없습니다." << endl;
		return NONE;
	}

	return iter->second;
}

string SynergyManager::Convert_SynergyName(type_synergy eType)
{
	switch (eType)
	{
	case 치적:
		return "치적";
	case 방깍:
		return "방깍";
	case 피증 :
		return "피증";
	case 공증:
		return "공증";
	case 백헤드:
		return "백헤드";
	case 서폿:
		return "서포터";
	default:
		return "없음";
	}
}

