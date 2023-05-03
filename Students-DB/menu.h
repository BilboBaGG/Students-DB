#pragma once

#include <conio.h>
#include <windows.h>

#include "printers.h"

string currentPath = "./Students";

class CreateNewInstituteMenu {
public:
	static void Run() {
		string inputString = "";
		char key = 0;
		while (true) {
			system(CLEAR_COMMAND);
			PrintParam("Enter the name of the new institution (30 symbols max) : " + inputString);
			key = _getch();
			switch (key)
			{
			default:
				if (inputString.length() <= 30 && (key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z')) {
					inputString += string(1, key);
					break;
				}
			}
		}
	}
};

class MainMenu {
public:
	static void Run() {
		
		int selectedOption = 0;
		int pressedKey = 0;
		bool isExit = false;

		List<string> params;
		params.Append("asd");

		while (true) {
			system(CLEAR_COMMAND);

			PrintParams(params);
			cout << currentPath << endl;

			pressedKey = _getch();

			switch (pressedKey) {

			case ESC:
				isExit = true;
				break;

			case ARROW_DOWN:
				selectedOption += 1;
				selectedOption %= params.Length();
				break;
			case ARROW_UP:
				selectedOption -= 1;
				selectedOption %= params.Length();
				break;
			case ENTER:
				// Next menu
				CreateNewInstituteMenu::Run();
				break;
			}

			if (isExit) {
				system(CLEAR_COMMAND);
				break;
			}
		}
	}
};
