#include <iostream>
#include <Windows.h>
#include <list>
#include <map>
#include <string>

using namespace std;

struct Vector3
{
	float x, y;

	Vector3() {}

	Vector3(float _x, float _y) : x(_x), y(_y) {}
};


struct Transform
{
	Vector3 Position;
	Vector3 Scale;
};


class Object
{
private:
	string str;
	Transform TransInfo;
public:
	void Initialize()
	{
		str = "->";
		TransInfo.Position = Vector3(4.0f, 15.0f);
	}

	int Update()
	{
		TransInfo.Position.x++;

		if (TransInfo.Position.x >= 100)
			return 1;

		return 0;
	}

	void Render()
	{
		COORD Pos = { (SHORT)TransInfo.Position.x, (SHORT)TransInfo.Position.y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
		cout << str << endl;
	}
public:
	Object() { }
	~Object() { }
};


bool check = false;
int Count = 0;


void Output(float _x, float _y, string _str);




int main(void)
{
	//** 실제 사용한 오브젝트 (랜더링 될 오브젝트 리스트)
	list<Object*> EnableList;

	//** 사용을 마친 오브젝트 리스트 (랜더링 되지 않음)
	list<Object*> DesableList;


	while (true)
	{
		system("cls");

		//** 총알이 발사될 위치.
		Output(2, 15, "◎");

		check = false;

		//** 키 입력 이벤트 확인
		if (GetAsyncKeyState(VK_RETURN))
			//** 한번만 입력받기위함.
			check = true;


		//** 입력이 되었다면..
		if (check)
		{
			//** DesableList 에 여분의 오브젝트가 있는지 확인 하고 없다면...
			if (DesableList.empty())
			{
				//** 5개의 오브젝트를 추가 생성한 후...
				for (int i = 0; i < 5; ++i)
					DesableList.push_back(new Object);
			}

			//** 추가 생성된 오브젝트 하나를 선택.
			list<Object*>::iterator iter = DesableList.begin();


			//** 초기화 에 필요한 구문 작성.
			(*iter)->Initialize();

			//** 사용할 리스트에 추가.
			EnableList.push_back((*iter));

			//** 현재 리스트에서 삭제.
			DesableList.pop_front();
		}


		for (list<Object*>::iterator iter = EnableList.begin();
			iter != EnableList.end();)
		{
			int iResult = (*iter)->Update();
			(*iter)->Render();

			if (iResult == 1)
			{
				//** 현재 리스트에서 삭제.
				DesableList.push_back((*iter));

				//** 사용할 리스트에 추가.
				iter = EnableList.erase(iter);
			}
			else
				++iter;
		}

		string Buffer = "DesableList : " + to_string(DesableList.size());
		Output(10, 1, Buffer);

		Sleep(50);
	}



	//** DesableList 전제 삭제
	for (list<Object*>::iterator iter = DesableList.begin();
		iter != DesableList.end(); ++iter)
	{
		delete (*iter);
		(*iter) = NULL;
	}
	DesableList.clear();


	//** EnableList 전제 삭제
	for (list<Object*>::iterator iter = EnableList.begin();
		iter != EnableList.end(); ++iter)
	{
		delete (*iter);
		(*iter) = NULL;
	}
	EnableList.clear();

	return 0;
}

void Output(float _x, float _y, string _str)
{
	COORD Pos = { (SHORT)_x, (SHORT)_y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	cout << _str << endl;
}