#pragma once
#include "Headers.h"

class DoubleBuffer
{
private:
	static DoubleBuffer* m_pInstance;
public:
	static DoubleBuffer* GetInstance()
	{
		if (m_pInstance == NULL)
			m_pInstance = new DoubleBuffer;

		return m_pInstance;
	}
private:
	int		m_iBufferIndex;		// 버퍼 Index
	HANDLE	m_HBuffer[2];		// HANDLE

	// 핸들은 구체적인 어떤 대상을 구분하기 위해 붙여진 유일한 번호. 
	// 운영 체제가 부여하는 중복되지 않는 정수값.
	// 기존에는 object나 structure 등의 포인터를 직접 다뤘으나 포인터 값의 처리
	// 위험성 때문에 객체를 지칭하는데 포인터를 쓰지 않고 번호를 쓴 것이다.
public:
	void CreateBuffer(const int& _width, const int& _height); // 버퍼 생성
	void WriteBuffer(int x, int y, char* _str, int _color = 15/*디폴트 매개변수*/);           // 버퍼 쓰기 (문자열)
	void WriteBuffer(int x, int y, int _ivalue, int _color = 15/*디폴트 매개변수*/); // 버퍼 쓰기 (정수)
	void FlippingBuffer();                                  // 버퍼 전환
	void ClearBuffer();                                     // 버퍼 지우기
	void DestroyBuffer();                                   // 버퍼 해제

private:
	bool MyCloseHandle(HANDLE& hFile);         // 안전하게 CloseHandle 처리
	void SetColor(int color);
private:
	DoubleBuffer();
public:
	~DoubleBuffer();
};
