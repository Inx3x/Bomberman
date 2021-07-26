#include "Logo.h"
#include "SceneManager.h"
#include "DoubleBuffer.h"

Logo::Logo()
{
}

Logo::~Logo()
{
	Release();
}

void Logo::Initialize()
{
	logo[0]  = (char*)"            ######";
	logo[1]  = (char*)"           #";
	logo[2]  = (char*)"          ###";
	logo[3]  = (char*)"    ###############";
	logo[4]  = (char*)"   #              ##";
	logo[5]  = (char*)"  #   #        #   ##";
	logo[6]  = (char*)" #    #        #    ##";
	logo[7]  = (char*)"#     #        #     ##";
	logo[8]  = (char*)"#     #        #     ##";
	logo[9]  = (char*)" #                  ##";
	logo[10] = (char*)"  #      ####      ##";
	logo[11] = (char*)"   #              ##";
	logo[12] = (char*)"    ###############";

	logo_Position = Vector3((float)((CONSOL_MAX_WIDTH - strlen(logo[7])) / 2), 8.0f);

	logo_Title[0] = (char*)"#####    ####   ##   ##  #####   ######  #####   ##   ##    ##    ##  ##";
	logo_Title[1] = (char*)"##  ##  ##  ##  ### ###  ##  ##  ##      ##  ##  ### ###   ####   ### ##";
	logo_Title[2] = (char*)"#####   ##  ##  #######  #####   #####   ##  ##  #######  ##  ##  ######";
	logo_Title[3] = (char*)"##  ##  ##  ##  ## # ##  ##  ##  ##      #####   ## # ##  ##  ##  ######";
	logo_Title[4] = (char*)"##  ##  ##  ##  ##   ##  ##  ##  ##      ## ##   ##   ##  ######  ## ###";
	logo_Title[5] = (char*)"#####    ####   ##   ##  #####   ######  ##  ##  ##   ##  ##  ##  ##  ##";

	logo_Title_Position = Vector3((float)((CONSOL_MAX_WIDTH - strlen(logo_Title[0])) / 2), 23.0f);
	logo_Title_Color = WHITE;

	stage_No = STAGE_1;

	Time = GetTickCount64();
	
	count_y = 0;
}

void Logo::Update()
{
	if (Time + 300 < GetTickCount64()) {
		logo_Title_Color = rand() % 15 + 1;
		Time = GetTickCount64();
	}

	if (GetAsyncKeyState(VK_RETURN)) {
		SceneManager::GetInstance()->SetScene(INTRO_STAGE);
	}
}

void Logo::Render()
{
	for (int i = 0; i < 13; i++) {
		DoubleBuffer::GetInstance()->WriteBuffer(
			logo_Position.x,
			logo_Position.y + i,
			logo[i]
		);
		if(i < 6){
			DoubleBuffer::GetInstance()->WriteBuffer(
				logo_Title_Position.x,
				logo_Title_Position.y + i,
				logo_Title[i],
				logo_Title_Color
			);
		}
	}
	char* text = "- PRESS ENTER -";
	DoubleBuffer::GetInstance()->WriteBuffer(
		(CONSOL_MAX_WIDTH - strlen(text)) / 2,
		33,
		text
	);
}

void Logo::Release()
{
}

