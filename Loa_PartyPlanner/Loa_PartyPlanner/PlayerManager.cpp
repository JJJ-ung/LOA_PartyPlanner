#include "Framework.h"
#include "PlayerManager.h"
#include "Character.h"
#include "SynergyManager.h"

IMPLEMENT_SINGLETON(PlayerManager)

PlayerManager::PlayerManager()
{
}

PlayerManager::~PlayerManager()
{
	for(auto p : m_mapPlayers)
	{
		for(auto chara : p.second)
		{
			SafeDelete(chara);
		}
		p.second.clear();
	}
	m_mapPlayers.clear();
}

HRESULT PlayerManager::Init_PlayerMgr()
{
	cout << " * 세이브 파일 로드 시도" << endl;

	string path = PathToString();
	path.append("\\Player_List.dat");

	locale::global(locale("Korean"));
	ifstream fin(path);
	if(!fin)
	{
		cout << " * 세이브 파일이 존재하지 않습니다" << endl;
		cout << " * 세이브 파일을 생성합니다" << endl;

		fin.close();

		locale::global(locale("Korean"));

		ofstream fout(path);

		fout.close();

		return NOERROR;
	}

	string name;
	int cnt;
	string classname;
	int synergy;
	float level;
	int tripod, acc;
	list<Character*> lst;
	Character* pChara = nullptr;

	while(true)
	{
		fin >> name >> cnt;

		if (fin.eof())
			break;

		lst.clear();
		for(int i = 0; i < cnt; ++i)
		{
			fin >> classname >> synergy >> level >> acc >> tripod;

			pChara = Character::Create(classname, (type_synergy)synergy, level, acc, tripod);
			if(!pChara)
			{
				cout << " * ERROR : 올바르지 않은 캐릭터 정보" << endl;
				return E_FAIL;
			}
			lst.emplace_back(pChara);
		}
		m_mapPlayers.insert({ name, lst });
	}

	cout << " * 세이브 파일 로드 성공" << endl;

	return NOERROR;
}

HRESULT PlayerManager::Add_Character()
{
	string name = "";
	list<Character*> lst;

	system("cls");

	cout << endl;
	cout << BORDER << endl;
	cout << " - 캐릭터의 주인을 입력해주세요 (다른 이름으로 등록하면 새로운 사람으로 등록됩니다)" << endl;
	cout << BORDER << endl;
	cout << " >> ";
	cin >> name;

	cout << endl;
	auto p = m_mapPlayers.find(name);
	if (p == m_mapPlayers.end())
	{
		cout << " * 찾지 못하였습니다. " << endl;
		m_mapPlayers.insert({ name, lst });
		p = m_mapPlayers.find(name);
		if (p == m_mapPlayers.end())
		{
			cout << " * ERROR : 사람 추가 실패" << endl;
			return E_FAIL;
		}
		cout << " * 새로운 사람을 추가하였습니다." << endl;
	}
	else
	{
		cout << " * " << name << " : 현재 " << p->second.size() << " 캐릭터 등록되어 있습니다." << endl;
	}

	system("pause");

	string classname;
	float level;
	int acc, tripod;
	type_synergy t;

	while(true)
	{
		system("cls");
		cout << endl;
		cout << BORDER << endl;
		cout << " * " << name << "님의 새로운 캐릭터를 등록합니다." << endl;
		cout << " * 주의사항 : 입력하라는거 말고 다른거 입력하면 프로그램 터집니다. " << endl;
		cout << BORDER << endl;
		cout << " - 캐릭터의 직업을 입력해주세요 (대체어 가능, 많이 쓰이는 것만)" << endl;
		cout << " - 예) 데빌헌터 = 데헌, 데모닉 = 충모닉" << endl;
		cout << BORDER << endl;
		cout << " >> ";
		cin >> classname;

		t = SynergyManager::GetInstance()->Find_CharaSynergy(classname);
		if (t == NONE)
		{
			cout << " * 올바르지 않은 직업명입니다. 다시 입력해주세요." << endl;
			continue;
		}
		cout << BORDER << endl;
		classname = SynergyManager::GetInstance()->Get_FullName(classname);
		cout << " * " << classname << " - 시너지 :  " << SynergyManager::GetInstance()->Convert_SynergyName(t) << endl;
		cout << BORDER << endl;
		cout << endl;
		system("pause");

		system("cls");
		cout << BORDER << endl;
		cout << " * " << name << "님의 " << classname << " 등록 중 " << endl;
		cout << BORDER << endl;
		cout << " - 캐릭터의 아이템 레벨을 입력해주세요 " << endl;
		cout << BORDER << endl;
		cout << " >> ";
		cin >> level;

		system("cls");
		cout << BORDER << endl;
		cout << " * " << name << "님의 " << classname << " 등록 중 " << endl;
		cout << BORDER << endl;
		cout << " - 캐릭터의 각인 3 개수를 입력해주세요 " << endl;
		cout << " - 예) 33333 = 5, 33331 = 4" << endl;
		cout << BORDER << endl;
		cout << " >> ";
		cin >> acc;

		system("cls");
		cout << BORDER << endl;
		cout << " * " << name << "님의 " << classname << " 등록 중 " << endl;
		cout << BORDER << endl;
		cout << " - 캐릭터의 트포작 유무를 입력해주세요 (최대 5, 최소 0)" << endl;
		cout << " - 예) 완벽해요= 5, 좀 해놓긴 했는데.. = 3, 그딴거 나는 몰루요 = 0" << endl;
		cout << BORDER << endl;
		cout << " >> ";
		cin >> tripod;

		break;
	}

	system("cls");
	Character* chara = Character::Create(classname, t, level, acc, tripod);
	if(!chara)
	{
		cout << " * ERROR : 캐릭터 등록에 실패하였습니다." << endl;
		return E_FAIL;
	}

	cout << endl;
	cout << BORDER << endl;

	p->second.emplace_back(chara);
	cout << " * 캐릭터를 등록하였습니다." << endl;
	cout << " * 현재 상태를 저장합니다." << endl;

	if (FAILED(Save_PlayerMap()))
		return E_FAIL;

	cout << BORDER << endl;

	system("pause");

	return NOERROR;
}

HRESULT PlayerManager::Render_CharacterList()
{
	system("cls");
	cout << endl;

	if (m_mapPlayers.empty())
	{
		cout << BORDER << endl;
		cout << " * 아무 캐릭터도 등록되어있지 않습니다." << endl;
		cout << BORDER << endl;
		return NOERROR;
	}

	for (auto pair : m_mapPlayers)
	{
		cout << BORDER << endl;
		cout << " * " << pair.first << "님의 캐릭터 현황 " << endl;
		for (auto p : pair.second)
		{
			p->Render_CharacterData();
		}
		cout << BORDER << endl;
	}

	return NOERROR;
}

HRESULT PlayerManager::Start_CharacterParty()
{
	system("cls");
	cout << endl;
	cout << BORDER << endl;
	cout << " * 파티 조합 구성을 시작합니다." << endl;
	if (m_mapPlayers.empty())
	{
		cout << " * 아무 캐릭터도 등록되어있지 않습니다." << endl;
		cout << " * 캐릭터를 등록하고 다시 시도해주세요." << endl;
		cout << BORDER << endl;
		return NOERROR;
	}

	cout << BORDER << endl;
	float level = 0.f;
	int players = 0;
	string input = "";
	cout << " * 보스의 레벨 제한은? " << endl;
	cout << " 예) 쿠크세이튼[노말] = 1475 " << endl;
	cin >> level;
	cout << endl;
	cout << " * 보스의 인원 제한은? " << endl;
	cout << " 예) 아브렐슈드 = 8 " << endl;
	cin >> players;
	cout << endl;
	cout << " * 트라이포드와 각인을 고려합니까? (Y/N) " << endl;
	cin >> input;

	bool b = false;
	if (input == "Y" || input == "y")
		b = true;

	return Make_CharacterParty(level, players, b);
}

HRESULT PlayerManager::Make_CharacterParty(float fLevel, int iCnt, bool bCheck)
{
	system("cls");

	if (bCheck)
		cout << " * 트라이포드 유무와 각인 유무를 점수에 합산합니다." << endl;

	cout << " * 서포터를 추려냅니다. " << endl;

	list<CHARA> lstDealer;
	list<CHARA> lstSupport;

	for(auto p : m_mapPlayers)
	{
		for(auto chara : p.second)
		{
			if(bCheck)
			{
				if (chara->m_eSynergyType == 서폿)
					lstSupport.emplace_back(CHARA(p.first, chara->m_fCharacterScore, chara->m_eSynergyType));
				else
					lstDealer.emplace_back(CHARA(p.first, chara->m_fCharacterScore, chara->m_eSynergyType));
			}
			else
			{
				if (chara->m_eSynergyType == 서폿)
					lstSupport.emplace_back(CHARA(p.first, chara->m_fItemLevel, chara->m_eSynergyType));
				else
					lstDealer.emplace_back(CHARA(p.first, chara->m_fItemLevel, chara->m_eSynergyType));
			}
		}
	}

	cout << " * 모든 딜러의 평균 점수를 계산합니다." << endl;
	if(bCheck)
		cout << " * 현재 트라이포드 점수는 " << TRIPOD_SCORE << "점, 각인 점수는 " << ACC_SCORE << "로 설정되어있습니다." << endl;

	float fAverageAll = 0.f;
	for(auto p : lstDealer)
	{
		fAverageAll += p.score;
	}
	fAverageAll /= lstDealer.size();

	cout << " * 모든 딜러의 평균 점수는 " << fAverageAll << "점 입니다." << endl;
	cout << " * 이 점수를 기준으로 파티 구성을 시작합니다." << endl;

	return NOERROR;
}

HRESULT PlayerManager::Save_PlayerMap()
{
	string path = PathToString();
	path.append("\\Player_List.dat");

	locale::global(locale("Korean"));
	ofstream fout(path);

	for (auto pair : m_mapPlayers)
	{
		fout << pair.first << " " << pair.second.size() << endl;

		for (auto p: pair.second)
		{
			if(FAILED(p->Save_CharacterData(fout)))
			{
				cout << " * ERROR : 저장에 실패했습니다." << endl;
				return E_FAIL;
			}
		}
	}

	cout << " * 저장 성공 ! " << endl;
	return NOERROR;
}
