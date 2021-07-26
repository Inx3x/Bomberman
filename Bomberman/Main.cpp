#include "MainUpdate.h"

int main() {
	system("title Bomberman");
	system("mode con:cols=103 lines=51");

	MainUpdate Main;
	Main.Initialize();

	while (true)
	{
		Main.Update();
		Main.Render();
	}
	return 0;
}