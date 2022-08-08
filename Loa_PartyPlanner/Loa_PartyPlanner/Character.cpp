#include "Framework.h"
#include "Character.h"
#include "SynergyManager.h"

Character::Character()
{
}

Character::~Character()
{
}

HRESULT Character::Init_Character(string classname, type_synergy synergy, float level, int acc, int tripod)
{
	m_strClassName = classname;
	m_eSynergyType = synergy;
	m_fItemLevel = level;
	m_iAccCount = acc;
	m_iTripodCount = tripod;

	m_fCharacterScore = m_fItemLevel + (m_iAccCount * ACC_SCORE) + (m_iTripodCount * TRIPOD_SCORE);

	return NOERROR;
}

HRESULT Character::Save_CharacterData(ofstream& fout)
{
	if (!fout)
		return E_FAIL;

	fout << m_strClassName << " " << m_eSynergyType << " " << m_fItemLevel << " " << m_iAccCount << " " << m_iTripodCount << endl;
	return NOERROR;
}

void Character::Render_CharacterData()
{
	cout << " ▶ " << m_strClassName << " ( " << SynergyManager::GetInstance()->Convert_SynergyName(m_eSynergyType) << " ) - 레벨 : " << m_fItemLevel << ", 각인 : ";
	for (int i = 0; i < m_iAccCount; ++i)
		cout << "3";
	cout << ", 트포작 점수 : " << m_iTripodCount << endl;
}

Character* Character::Create(string classname, type_synergy synergy, float level, int acc, int tripod)
{
	Character* p = new Character;
	if(FAILED(p->Init_Character(classname, synergy, level, acc, tripod)))
	{
		SafeDelete(p);
		return nullptr;
	}
	return p;
}
