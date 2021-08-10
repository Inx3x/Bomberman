#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <fstream>

using namespace std;

struct StudentInfo
{
	char* Name;
	int Index;

	int Kor;
	int Eng;
	int Math;
};

enum SUBJECT {
	KOR,
	ENG,
	MATH
};

bool KorComp(const StudentInfo& left, const StudentInfo& right)
{
	return left.Kor > right.Kor;
};

list<StudentInfo> StudentList;

map<SUBJECT, list<StudentInfo>> StudentMap;

void LoadDate();

int main(void)
{
	LoadDate();

	StudentMap.insert(make_pair(KOR, StudentList));
	//과목별로 넣으란게 먼말이죠?ㅠ
	
	StudentList.sort(KorComp);

	for (list<StudentInfo>::iterator iter = StudentList.begin();
		iter != StudentList.end(); ++iter)
	{
		cout << iter->Index << " : " << iter->Name << endl;
		cout << "국어 점수 : " << iter->Kor << endl;
		cout << "영어 점수 : " << iter->Eng << endl;
		cout << "수학 점수 : " << iter->Math << endl << endl;
	}

	return 0;
}

void LoadDate()
{
	//** 에디터를 불러온다.
	FILE* pFileCSV = fopen("StudenInfoList.csv", "r");

	//** 파일을 완전이 읽어온다.
	while (!feof(pFileCSV))
	{
		StudentInfo Info;

		char buffer[128] = "";

		fscanf(pFileCSV, "%d,%d,%d,%d,%s",
			&Info.Index, &Info.Kor, &Info.Eng, &Info.Math, buffer);


		//** 읽어온 문자열을 포인터에 맞게 변경한다.
		Info.Name = new char[4];
		strcpy(Info.Name, buffer);

		//** 리스트에 추가한다.
		StudentList.push_back(Info);
	}

	//** 파일을 닫는다.
	fclose(pFileCSV);
}