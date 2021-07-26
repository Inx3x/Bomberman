#include "DoubleBuffer.h"


DoubleBuffer* DoubleBuffer::m_pInstance = NULL;

DoubleBuffer::DoubleBuffer(void) : m_iBufferIndex(0)
{

}

DoubleBuffer::~DoubleBuffer(void)
{

}

// 버퍼 생성
void DoubleBuffer::CreateBuffer(const int& _width, const int& _height)
{
	CONSOLE_CURSOR_INFO DeCursor;            // 콘솔창 깜박이는 커서
	COORD size = { (short)_width - 1, (short)_height - 1 };     // 버퍼 크기를 저장하는 구조체
	SMALL_RECT rect;                    // 창 크기를 저장하는 구조체


	rect.Left = 0;
	rect.Right = CONSOL_MAX_WIDTH;
	rect.Top = 0;
	rect.Bottom = CONSOL_MAX_HEIGHT;

	// 1번 버퍼 생성
	m_HBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(m_HBuffer[0], size);  // 버퍼 크기 설정
	SetConsoleWindowInfo(m_HBuffer[0], TRUE, &rect); // 창 크기 설정


	// 2번 버퍼 생성
	m_HBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(m_HBuffer[1], size);  // 버퍼 크기 설정
	SetConsoleWindowInfo(m_HBuffer[1], TRUE, &rect); // 창 크기 설정


	DeCursor.dwSize = 1;
	DeCursor.bVisible = FALSE;


	SetConsoleCursorInfo(m_HBuffer[0], &DeCursor); // 1번 버퍼에 깜박이는 커서 지움
	SetConsoleCursorInfo(m_HBuffer[1], &DeCursor); // 2번 버퍼에 깜박이는 커서 지움
}

// 버퍼 쓰기
void DoubleBuffer::WriteBuffer(int x, int y, char* _str, int _color)
{
	DWORD dw;                           // 좌표 저장 구조체
	COORD CursorPosition = { (short)x, (short)y };    // 좌표 설정

	// 좌표 이동
	SetConsoleCursorPosition(m_HBuffer[m_iBufferIndex], CursorPosition);

	SetColor(_color);

	// 버퍼에 쓰기
	WriteFile(m_HBuffer[m_iBufferIndex], _str, (DWORD)strlen(_str), &dw, NULL);
}

void DoubleBuffer::WriteBuffer(int x, int y, int _ivalue, int _color)
{
	DWORD dw;	// 좌표 저장 구조체
	COORD CursorPosition = { (short)x, (short)y };    // 좌표 설정

	// 좌표 이동
	SetConsoleCursorPosition(m_HBuffer[m_iBufferIndex], CursorPosition);

	char* cStr = NULL;

	cStr = new char[sizeof(int) + 1];
	_itoa(_ivalue, cStr, 10);

	SetColor(_color);
	// 버퍼에 쓰기
	WriteFile(m_HBuffer[m_iBufferIndex], cStr, (DWORD)strlen(cStr), &dw, NULL);
}

// 버퍼 전환
void DoubleBuffer::FlippingBuffer()
{
	// 버퍼 활성화. 버퍼의 내용을 한번에 출력
	SetConsoleActiveScreenBuffer(m_HBuffer[m_iBufferIndex]);
	m_iBufferIndex = !m_iBufferIndex; // 다음 버퍼 선택
}

// 버퍼 지우기
void DoubleBuffer::ClearBuffer()
{
	COORD Coor = { 0, 0 };  // 아래 함수를 위한 구조체
	DWORD dw;               // 아래 함수를 위한 구조체

	// 해당 버퍼의 Coor 좌표부터 ' '값을 채워서 지워진 것처럼 만들기
	FillConsoleOutputCharacter(m_HBuffer[m_iBufferIndex], ' ', CONSOL_MAX_WIDTH * CONSOL_MAX_HEIGHT, Coor, &dw);
}

// 버퍼 해제
void DoubleBuffer::DestroyBuffer()
{
	MyCloseHandle(m_HBuffer[0]);    // 1번 버퍼 해제
	MyCloseHandle(m_HBuffer[1]);    // 2번 버퍼 해제
	// (HANDLE이 지정한 정수값은 그대로. 해당 정수에 대한 HANDLE 커널만 삭제)
}

// 안전하게 CloseHandle을 처리하기 위해 MyCloseHandle 만듬
bool DoubleBuffer::MyCloseHandle(HANDLE& hFile)
{
	if (INVALID_HANDLE_VALUE != hFile)
	{
		hFile = INVALID_HANDLE_VALUE;
	}
	return false;
}

void DoubleBuffer::SetColor(int color)
{
	SetConsoleTextAttribute(m_HBuffer[m_iBufferIndex], color);
}
