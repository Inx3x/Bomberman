#pragma once
#include "Headers.h"
class Object
{
private:
	string str;
	Transform transinfo;

public:
	Object();
	Object(const Transform& _transinfo) : transinfo(_transinfo) {}
	~Object();

	void Initialize();
	int Update();
	void Render();

	Object* Clone() { return new Object(*this); }

	void SetIndex(int _index) { transinfo.index = _index; }
};

