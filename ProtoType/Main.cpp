#include "PrototypeManager.h"
#include "Object.h"


Object* pObjList[3];

void InitObject(string _Key)
{
	//** PrototypeManager 에서 원본 객체를 찾아옴.
	Object* pObj = PrototypeManager::GetInstance()->FineObject(_Key);

	//** 찾으려는 객체가 없다면...
	if (pObj == nullptr)
	{
		//** 오류 메시지를 출력하고...
		COORD Pos = { (SHORT)50, (SHORT)15 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
		cout << "복제할 원본 객체가 없습니다." << endl;

		// ** 함수 종료.
		return;
	}


	// ** 원형객체를 정상적으로 참조했다면...
	// ** pObjList 를 초기화
	for (int i = 0; i < 3; ++i)
	{
		// ** 참조된 원형 객체의 복사본을 넘겨줌
		pObjList[i] = pObj->Clone();


		// ** 그리고 본사본을 초기화함.
		pObjList[i]->Initialize();

		// ** 복사본의 인덱스값을 변경.
		pObjList[i]->SetIndex(i + 1);
	}
}



int main(void)
{
	//** PrototypeManager 초기화 (초기화가 진행되면 원형객체를 생성한다.)
	PrototypeManager::GetInstance()->Initialize();

	//** 초기화
	InitObject("Object");

	//** 출력
	for (int i = 0; i < 3; ++i)
		if (pObjList[i])
			pObjList[i]->Render(i);	

	//** 삭제
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
 * 초기 구문
 * 변경사항에 대한 구문
 * 출력 구문
 * 삭제
***********************/
