#include "PrototypeManager.h"
#include "Object.h"

//Object* pObjList[3];

list<Object*> pObjList;

void InitObject(string _key) {
	Object* pObj = PrototypeManager::GetInstance()->FineObject(_key);

	if (!pObj) {
		COORD pos = { (SHORT)50, (SHORT)15 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		cout << "복제할 원본 객체가 없습니다." << endl;

		return;
	}
	/*
	for (int i = 0; i < 3; i++)
	{
		pObjList[i] = pObj->Clone();
		pObjList[i]->Initialize();
		pObjList[i]->SetIndex(i+1);
	}
	*/
	for (int i = 0; i < 3; i++)
	{
		pObjList.push_back(pObj->Clone());
	}
	int count = 0;
	for (list<Object*>::iterator iter = pObjList.begin(); iter != pObjList.end();iter++)
	{
		(*iter)->Initialize();
		(*iter)->SetIndex(++count);
	}
}
int main() {
	PrototypeManager::GetInstance()->Initialize();

	InitObject("Object");
	/*
	for (int i = 0; i < 3; i++)
	{
		if (pObjList[i])	pObjList[i]->Render(i);
	}
	*/
	int count = 0;
	for (list<Object*>::iterator iter = pObjList.begin(); iter != pObjList.end(); iter++)
	{
		if ((*iter))	(*iter)->Render(count++);
	}
	/*
	for (int i = 0; i < 3; i++)
	{
		if (pObjList[i]) {
			delete pObjList[i];
			pObjList[i] = nullptr;
		}
	}
	*/
	for (list<Object*>::iterator iter = pObjList.begin(); iter != pObjList.end(); iter++)
	{
		if ((*iter)) {
			delete (*iter);
			(*iter) = nullptr;
		}
	}
	pObjList.clear();

	return 0;
}

/**********************
 * 초기 구문
 * 변경사항에 대한 구문
 * 출력 구문
 * 삭제
***********************/
