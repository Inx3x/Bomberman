#include <iostream>
#include <Windows.h>
#include <list>
#include <map>

using namespace std;


struct ObjectPool
{
	int Key;
	int Value;
	bool Active;

	ObjectPool() : Key(0), Value(0), Active(false) { }

	ObjectPool(int _Key, int _Value, bool _Active)
		: Key(_Key), Value(_Value), Active(_Active) { }
};


bool check = false;
int Count = 0;

int main(void)
{
	list<ObjectPool*> ObjectPoolList;

	while (true)
	{
		system("cls");

		check = false;

		if (GetAsyncKeyState(VK_RETURN))
			check = true;


		if (check)
		{
			if (ObjectPoolList.empty())
			{
				ObjectPoolList.push_back(
					new ObjectPool(Count++, 0, false));
			}
			else
			{
				for (list<ObjectPool*>::iterator iter = ObjectPoolList.begin(); iter != ObjectPoolList.end(); ++iter)
				{
					if (!(*iter)->Active)
					{
						(*iter)->Active = true;
						(*iter)->Value = 0;
						(*iter)->Key = 0;
						break;
					}
				}
			}
		}




		for (list<ObjectPool*>::iterator iter = ObjectPoolList.begin();
			iter != ObjectPoolList.end(); ++iter)
		{
			if ((*iter)->Active)
			{
				(*iter)->Value++;
				cout << (*iter)->Key << " : "
					<< (*iter)->Value << endl << endl;

				if ((*iter)->Value >= 50)
				{
					(*iter)->Active = false;
				}
			}
		}

		Sleep(50);
	}





	for (list<ObjectPool*>::iterator iter = ObjectPoolList.begin();
		iter != ObjectPoolList.end(); ++iter)
	{
		delete (*iter);
		(*iter) = NULL;
	}
	ObjectPoolList.clear();


	return 0;
}