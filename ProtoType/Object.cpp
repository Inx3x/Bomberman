#include "Object.h"

Object::Object() {

}
Object::~Object() {

}

void Object::Initialize() {
	str = "Object";
	transinfo.position = Vector3(0.0f, 0.0f);
	transinfo.index = 0;
}

int Object::Update() {
	return 0;
}

void Object::Render() {
	COORD pos = { (SHORT)transinfo.position.x, (SHORT)transinfo.position.y + transinfo.index };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	cout << transinfo.index << " : " << str << endl;
}