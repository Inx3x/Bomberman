#include "InputManager.h"
InputManager* InputManager::m_pInstance = NULL;
InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::CheckKey()
{
	m_ulKey = 0;

	if(GetAsyncKeyState(VK_UP))			m_ulKey |= KEYID_UP;
	if(GetAsyncKeyState(VK_DOWN))		m_ulKey |= KEYID_DOWN;
	if(GetAsyncKeyState(VK_RIGHT))		m_ulKey |= KEYID_RIGHT;
	if(GetAsyncKeyState(VK_LEFT))		m_ulKey |= KEYID_LEFT;

	if(GetAsyncKeyState(VK_SPACE))		m_ulKey |= KEYID_SPACE;
	if(GetAsyncKeyState(VK_ESCAPE))		m_ulKey |= KEYID_ESCAPE;
	if(GetAsyncKeyState(VK_RETURN))		m_ulKey |= KEYID_RETURN;
}
