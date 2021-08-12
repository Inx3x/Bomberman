#pragma once
#include "Headers.h"

class Object;
class PrototypeManager
{
private:
	PrototypeManager();

	static PrototypeManager* instance;

	map<string, Object*> prototypelist;

public:
	~PrototypeManager();

	static PrototypeManager* GetInstance() {
		if (instance == nullptr)	instance = new PrototypeManager;
		return instance;
	}

	void Initialize();
	Object* FineObject(string _str);
};

