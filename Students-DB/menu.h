#pragma once

#include <conio.h>
#include <windows.h>

#include "printers.h"

string currentPath = "./Students";

class InputMenu {
public:
	static string Run(string message) {
		string inputString = "";
		int key = 0;
		bool reload = true;
		system(CLEAR_COMMAND);
		PrintParam(message + inputString);
		while (true) {
			key = _getch();
			switch (key)
			{
			case (ESC):
				inputString = "{{ESC}}";
				return inputString;
			case (ENTER):
				return inputString;
				break;
			case (BACKSPACE):
				if (inputString.length() > 0) {
					ClearLastLetter(message + inputString);
					inputString = inputString.substr(0, inputString.length() - 1);
				}
				break;
			default:
				if (inputString.length() <= 30 && (key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z')) {
					inputString += string(1, key);
					AddNewLetter(key);
					break;
				}
			}
		}
	}
};

class InfoMenu {
public:
	static void Run(string message) {
		system(CLEAR_COMMAND);
		PrintParam(message);
		int key = 0;
		while (true) {
			key = _getch();
			if (key == ESC || key == ENTER) {
				break;
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
				string temp = InputMenu::Run("Enter the name of the new institution : ").c_str();

				if (temp != "{{ESC}}") {
					params.Append(temp);
					InfoMenu::Run("Secsess");
				}

				break;
			}

			if (isExit) {
				system(CLEAR_COMMAND);
				break;
			}
		}
	}
};
