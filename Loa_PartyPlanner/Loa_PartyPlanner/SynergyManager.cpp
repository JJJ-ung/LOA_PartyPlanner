#include "Framework.h"
#include "SynergyManager.h"

IMPLEMENT_SINGLETON(SynergyManager)

SynergyManager::SynergyManager()
{
	m_mapFullName.insert({ "�踶", "��Ʋ������" });
	m_mapFullName.insert({ "â��", "â����" });
	m_mapFullName.insert({ "����", "��������" });
	m_mapFullName.insert({ "��������", "��������" });
	m_mapFullName.insert({ "�������", "��������" });
	m_mapFullName.insert({ "��ī", "�Ƹ�ī��" });
	m_mapFullName.insert({ "�ǽ�", "�ǽ�����" });
	m_mapFullName.insert({ "���", "������" });
	m_mapFullName.insert({ "��", "������" });
	m_mapFullName.insert({ "����", "���ӳ�" });
	m_mapFullName.insert({ "��Ʈ", "��Ʈ���̾�" });
	m_mapFullName.insert({ "����", "�����" });
	m_mapFullName.insert({ "����", "�����" });
	m_mapFullName.insert({ "ȣũ", "ȣũ����" });
	m_mapFullName.insert({ "����", "��������" });
	m_mapFullName.insert({ "�Ҽ�", "�Ҽ�����" });
	m_mapFullName.insert({ "���", "�����" });
	m_mapFullName.insert({ "��ī", "��ī����" });
	m_mapFullName.insert({ "��", "���̵�" });
	m_mapFullName.insert({ "Ȧ��", "Ȧ������Ʈ" });
	m_mapFullName.insert({ "���ư�", "��ȭ��" });
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
		cout << " * ERROR : �ó��� ������ Ȯ�� ����" << endl;
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

	cout << " * �ó��� ������ Ȯ�� ���� " << endl;

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
		cout << " * �ش� ������ ã�� �� �����ϴ�." << endl;
		return NONE;
	}

	return iter->second;
}

string SynergyManager::Convert_SynergyName(type_synergy eType)
{
	switch (eType)
	{
	case ġ��:
		return "ġ��";
	case ���:
		return "���";
	case ���� :
		return "����";
	case ����:
		return "����";
	case �����:
		return "�����";
	case ����:
		return "������";
	default:
		return "����";
	}
}

