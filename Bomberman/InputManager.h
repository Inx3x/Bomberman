#pragma once
#include "Headers.h"
class InputManager
{
private:
	static InputManager* m_pInstance;

	InputManager();

	ULONG m_ulKey;

public:
	static InputManager* GetInstance() {
		if (m_pInstance == NULL)	m_pInstance = new InputManager;
		return m_pInstance;
	}
	ULONG GetKey() const { return m_ulKey; }
	void CheckKey();
	~InputManager();
};

