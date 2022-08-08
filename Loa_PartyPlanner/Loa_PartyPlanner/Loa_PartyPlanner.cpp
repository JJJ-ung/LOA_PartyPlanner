#include "Framework.h"
#include "SynergyManager.h"
#include "PlayerManager.h"

std::wstring_convert<convert_type, wchar_t> converter;

int main()
{
	cout << BORDER << endl;

	cout << " * 구동 시작 " << endl;

	if(FAILED(SynergyManager::GetInstance()->Init_SynergyMgr()))
		return 0;

	if (FAILED(PlayerManager::GetInstance()->Init_PlayerMgr()))
		return 0;

	cout << " * 구동 성공 " << endl;

	//system("pause");

	cout << BORDER << endl;

	int select;

	while(true)
	{
		system("cls");
		cout << BORDER << endl;
		cout << " 로아 파티 플래너 ver." << VER << endl;
		cout << " * 입력하라는거 외에 다른거 입력하면 프로그램 터집니다. " << endl;
		cout << BORDER << endl;
		cout << endl;
		cout << " 1. 파티 생성하기 " << endl;
		cout << endl;
		cout << " 2. 캐릭터 등록하기" << endl;
		cout << " 3. 등록 현황 확인하기 " << endl;
		cout << endl;
		cout << " 0. 프로그램 종료 " << endl;
		cout << endl;
		cout << BORDER << endl;
		cout << " >> ";
		cin >> select;

		switch (select)
		{
		case 0:
			return 0;
		case 1:
			PlayerManager::GetInstance()->Start_CharacterParty();
			system("pause");
			break;
		case 2:
			if(FAILED(PlayerManager::GetInstance()->Add_Character()))
			{
				cout << " ERROR : 오류 발생, 프로그램 종료합니다." << endl;
				return 0;
			}
			break;
		case 3:
			PlayerManager::GetInstance()->Render_CharacterList();
			system("pause");
			break;
		default:
			cout << " * 잘못된 입력값입니다. 다시 입력해주세요." << endl;
			system("pause");
		}
	}
}

