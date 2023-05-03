#pragma once

string currentPath = ".\\Students";

#include <conio.h>
#include <windows.h>

#include "printers.h"
#include "directory_functions.h"
#include "object_functions.h"

class InputMenu {
public:
	static string Run(string message) {
		string inputString = "";
		int key = 0;
		bool reload = true;
		system(CLEAR_COMMAND);
		PrintOneParam(message + inputString);
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
				if (inputString.length() <= 30 && (key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z' || key == '-' || key <= '9' && key >= '0')) {
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
		PrintOneParam(message);
		int key = 0;
		while (true) {
			key = _getch();
			if (key == ESC || key == ENTER) {
				break;
			}
		}
	}
};

class MainChooseMenu {
public:
	static void Run(string object) {

		int selectedOption = 0;
		int pressedKey = 0;
		bool isExit = false;

		List<string>& backupParams = GetNewInstituteParams(currentPath, object);
		List<string>& params = GetNewInstituteParams(currentPath, object);

		params[0] = GREEN + params[0] + RESET;

		int identicalButtonsNumber = params.Length() - 2;

		while (true) {
			system(CLEAR_COMMAND);

			PrintParams(params, backupParams, "Choose " + object, identicalButtonsNumber);

			pressedKey = _getch();

			switch (pressedKey) {

			case ESC:
				isExit = true;
				break;
			case ARROW_DOWN:
				params[selectedOption] = backupParams[selectedOption];
				selectedOption += 1;
				selectedOption %= backupParams.Length();
				params[selectedOption] = GREEN + params[selectedOption] + RESET; // Make Button Selecteds
				break;
			case ARROW_UP:
				params[selectedOption] = backupParams[selectedOption];
				if (selectedOption == 0) {
					selectedOption = backupParams.Length() - 1;
				}
				else {
					selectedOption -= 1;
					selectedOption %= backupParams.Length();
				}
				params[selectedOption] = GREEN + params[selectedOption] + RESET;
				break;
			case ENTER:
				if (selectedOption < identicalButtonsNumber) {
					if (object == "institute") {
						currentPath += "\\" + backupParams[selectedOption];
						MainChooseMenu::Run("group");
						RestoreCurrentPath();
					} else {
						InfoMenu::Run("GOOD");
					}
				} else {
					string tempObject = InputMenu::Run("Enter the name of the new " + object + " : ").c_str();

					if (tempObject != "{{ESC}}" && tempObject.length() > 0) {
						MakeDirectory(currentPath + "\\" + tempObject);

						// Params Reset
						backupParams = GetNewInstituteParams(currentPath, object);
						params = GetNewInstituteParams(currentPath, object);
						params[0] = GREEN + params[0] + RESET;
						selectedOption = 0;

						identicalButtonsNumber = params.Length() - 2;

						InfoMenu::Run("Successfully added" + object);
					}

				}
				break;
			}

			if (isExit) {
				system(CLEAR_COMMAND);

				delete& backupParams;
				delete& params;

				break;
			}
		}
	}
};
