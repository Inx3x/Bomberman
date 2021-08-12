#include "PrototypeManager.h"
#include "Object.h"

PrototypeManager* PrototypeManager::instance = nullptr;
PrototypeManager::PrototypeManager()
{
}

PrototypeManager::~PrototypeManager()
{
}

void PrototypeManager::Initialize()
{
	Transform transinfo;
	transinfo.position = Vector3(0.0f, 0.0f);

	prototypelist["Object"] = new Object(transinfo);
}

Object* PrototypeManager::FineObject(string _str)
{
	map<string, Object*>::iterator iter = prototypelist.find(_str);

	if(iter == prototypelist.end())		return nullptr;

	return iter->second;
}
