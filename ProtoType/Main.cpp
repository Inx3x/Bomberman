#include "PrototypeManager.h"
#include "Object.h"


Object* pObjList[3];

void InitObject(string _Key)
{
	//** PrototypeManager ���� ���� ��ü�� ã�ƿ�.
	Object* pObj = PrototypeManager::GetInstance()->FineObject(_Key);

	//** ã������ ��ü�� ���ٸ�...
	if (pObj == nullptr)
	{
		//** ���� �޽����� ����ϰ�...
		COORD Pos = { (SHORT)50, (SHORT)15 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
		cout << "������ ���� ��ü�� �����ϴ�." << endl;

		// ** �Լ� ����.
		return;
	}


	// ** ������ü�� ���������� �����ߴٸ�...
	// ** pObjList �� �ʱ�ȭ
	for (int i = 0; i < 3; ++i)
	{
		// ** ������ ���� ��ü�� ���纻�� �Ѱ���
		pObjList[i] = pObj->Clone();


		// ** �׸��� ���纻�� �ʱ�ȭ��.
		pObjList[i]->Initialize();

		// ** ���纻�� �ε������� ����.
		pObjList[i]->SetIndex(i + 1);
	}
}



int main(void)
{
	//** PrototypeManager �ʱ�ȭ (�ʱ�ȭ�� ����Ǹ� ������ü�� �����Ѵ�.)
	PrototypeManager::GetInstance()->Initialize();

	//** �ʱ�ȭ
	InitObject("Object");

	//** ���
	for (int i = 0; i < 3; ++i)
		if (pObjList[i])
			pObjList[i]->Render(i);	

	//** ����
	for (int i = 0; i < 3; ++i)
	{
		if (pObjList[i])
		{
			delete pObjList[i];
			pObjList[i] = nullptr;
		}
	}
	
	return 0;
}


/**********************
 * �ʱ� ����
 * ������׿� ���� ����
 * ��� ����
 * ����
***********************/
