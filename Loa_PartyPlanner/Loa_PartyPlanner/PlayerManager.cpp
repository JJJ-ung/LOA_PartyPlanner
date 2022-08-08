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
	cout << " * ���̺� ���� �ε� �õ�" << endl;

	string path = PathToString();
	path.append("\\Player_List.dat");

	locale::global(locale("Korean"));
	ifstream fin(path);
	if(!fin)
	{
		cout << " * ���̺� ������ �������� �ʽ��ϴ�" << endl;
		cout << " * ���̺� ������ �����մϴ�" << endl;

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
				cout << " * ERROR : �ùٸ��� ���� ĳ���� ����" << endl;
				return E_FAIL;
			}
			lst.emplace_back(pChara);
		}
		m_mapPlayers.insert({ name, lst });
	}

	cout << " * ���̺� ���� �ε� ����" << endl;

	return NOERROR;
}

HRESULT PlayerManager::Add_Character()
{
	string name = "";
	list<Character*> lst;

	system("cls");

	cout << endl;
	cout << BORDER << endl;
	cout << " - ĳ������ ������ �Է����ּ��� (�ٸ� �̸����� ����ϸ� ���ο� ������� ��ϵ˴ϴ�)" << endl;
	cout << BORDER << endl;
	cout << " >> ";
	cin >> name;

	cout << endl;
	auto p = m_mapPlayers.find(name);
	if (p == m_mapPlayers.end())
	{
		cout << " * ã�� ���Ͽ����ϴ�. " << endl;
		m_mapPlayers.insert({ name, lst });
		p = m_mapPlayers.find(name);
		if (p == m_mapPlayers.end())
		{
			cout << " * ERROR : ��� �߰� ����" << endl;
			return E_FAIL;
		}
		cout << " * ���ο� ����� �߰��Ͽ����ϴ�." << endl;
	}
	else
	{
		cout << " * " << name << " : ���� " << p->second.size() << " ĳ���� ��ϵǾ� �ֽ��ϴ�." << endl;
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
		cout << " * " << name << "���� ���ο� ĳ���͸� ����մϴ�." << endl;
		cout << " * ���ǻ��� : �Է��϶�°� ���� �ٸ��� �Է��ϸ� ���α׷� �����ϴ�. " << endl;
		cout << BORDER << endl;
		cout << " - ĳ������ ������ �Է����ּ��� (��ü�� ����, ���� ���̴� �͸�)" << endl;
		cout << " - ��) �������� = ����, ����� = ����" << endl;
		cout << BORDER << endl;
		cout << " >> ";
		cin >> classname;

		t = SynergyManager::GetInstance()->Find_CharaSynergy(classname);
		if (t == NONE)
		{
			cout << " * �ùٸ��� ���� �������Դϴ�. �ٽ� �Է����ּ���." << endl;
			continue;
		}
		cout << BORDER << endl;
		classname = SynergyManager::GetInstance()->Get_FullName(classname);
		cout << " * " << classname << " - �ó��� :  " << SynergyManager::GetInstance()->Convert_SynergyName(t) << endl;
		cout << BORDER << endl;
		cout << endl;
		system("pause");

		system("cls");
		cout << BORDER << endl;
		cout << " * " << name << "���� " << classname << " ��� �� " << endl;
		cout << BORDER << endl;
		cout << " - ĳ������ ������ ������ �Է����ּ��� " << endl;
		cout << BORDER << endl;
		cout << " >> ";
		cin >> level;

		system("cls");
		cout << BORDER << endl;
		cout << " * " << name << "���� " << classname << " ��� �� " << endl;
		cout << BORDER << endl;
		cout << " - ĳ������ ���� 3 ������ �Է����ּ��� " << endl;
		cout << " - ��) 33333 = 5, 33331 = 4" << endl;
		cout << BORDER << endl;
		cout << " >> ";
		cin >> acc;

		system("cls");
		cout << BORDER << endl;
		cout << " * " << name << "���� " << classname << " ��� �� " << endl;
		cout << BORDER << endl;
		cout << " - ĳ������ Ʈ���� ������ �Է����ּ��� (�ִ� 5, �ּ� 0)" << endl;
		cout << " - ��) �Ϻ��ؿ�= 5, �� �س��� �ߴµ�.. = 3, �׵��� ���� ����� = 0" << endl;
		cout << BORDER << endl;
		cout << " >> ";
		cin >> tripod;

		break;
	}

	system("cls");
	Character* chara = Character::Create(classname, t, level, acc, tripod);
	if(!chara)
	{
		cout << " * ERROR : ĳ���� ��Ͽ� �����Ͽ����ϴ�." << endl;
		return E_FAIL;
	}

	cout << endl;
	cout << BORDER << endl;

	p->second.emplace_back(chara);
	cout << " * ĳ���͸� ����Ͽ����ϴ�." << endl;
	cout << " * ���� ���¸� �����մϴ�." << endl;

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
		cout << " * �ƹ� ĳ���͵� ��ϵǾ����� �ʽ��ϴ�." << endl;
		cout << BORDER << endl;
		return NOERROR;
	}

	for (auto pair : m_mapPlayers)
	{
		cout << BORDER << endl;
		cout << " * " << pair.first << "���� ĳ���� ��Ȳ " << endl;
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
	cout << " * ��Ƽ ���� ������ �����մϴ�." << endl;
	if (m_mapPlayers.empty())
	{
		cout << " * �ƹ� ĳ���͵� ��ϵǾ����� �ʽ��ϴ�." << endl;
		cout << " * ĳ���͸� ����ϰ� �ٽ� �õ����ּ���." << endl;
		cout << BORDER << endl;
		return NOERROR;
	}

	cout << BORDER << endl;
	float level = 0.f;
	int players = 0;
	string input = "";
	cout << " * ������ ���� ������? " << endl;
	cout << " ��) ��ũ����ư[�븻] = 1475 " << endl;
	cin >> level;
	cout << endl;
	cout << " * ������ �ο� ������? " << endl;
	cout << " ��) �ƺ근���� = 8 " << endl;
	cin >> players;
	cout << endl;
	cout << " * Ʈ��������� ������ ����մϱ�? (Y/N) " << endl;
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
		cout << " * Ʈ�������� ������ ���� ������ ������ �ջ��մϴ�." << endl;

	cout << " * �����͸� �߷����ϴ�. " << endl;

	list<CHARA> lstDealer;
	list<CHARA> lstSupport;

	for(auto p : m_mapPlayers)
	{
		for(auto chara : p.second)
		{
			if(bCheck)
			{
				if (chara->m_eSynergyType == ����)
					lstSupport.emplace_back(CHARA(p.first, chara->m_fCharacterScore, chara->m_eSynergyType));
				else
					lstDealer.emplace_back(CHARA(p.first, chara->m_fCharacterScore, chara->m_eSynergyType));
			}
			else
			{
				if (chara->m_eSynergyType == ����)
					lstSupport.emplace_back(CHARA(p.first, chara->m_fItemLevel, chara->m_eSynergyType));
				else
					lstDealer.emplace_back(CHARA(p.first, chara->m_fItemLevel, chara->m_eSynergyType));
			}
		}
	}

	cout << " * ��� ������ ��� ������ ����մϴ�." << endl;
	if(bCheck)
		cout << " * ���� Ʈ�������� ������ " << TRIPOD_SCORE << "��, ���� ������ " << ACC_SCORE << "�� �����Ǿ��ֽ��ϴ�." << endl;

	float fAverageAll = 0.f;
	for(auto p : lstDealer)
	{
		fAverageAll += p.score;
	}
	fAverageAll /= lstDealer.size();

	cout << " * ��� ������ ��� ������ " << fAverageAll << "�� �Դϴ�." << endl;
	cout << " * �� ������ �������� ��Ƽ ������ �����մϴ�." << endl;

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
				cout << " * ERROR : ���忡 �����߽��ϴ�." << endl;
				return E_FAIL;
			}
		}
	}

	cout << " * ���� ���� ! " << endl;
	return NOERROR;
}
