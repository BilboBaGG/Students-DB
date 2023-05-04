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
				inputString = ESCAPE_STRING;
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

class SelectParamMenu {
public:
	static string Run(string object, string header) {

		int selectedOption = 0;
		int pressedKey = 0;

		List<string>& backupParams = GetNewObjectParams(currentPath);
		List<string>& params = GetNewObjectParams(currentPath);

		params[0] = GREEN + params[0] + RESET;

		while (true) {
			system(CLEAR_COMMAND);

			PrintParams(params, backupParams, header);
			Sleep(SLEEP);

			pressedKey = _getch();

			switch (pressedKey) {

			case ESC:
				system(CLEAR_COMMAND);

				delete& backupParams;
				delete& params;

				return ESCAPE_STRING;
			case ARROW_DOWN:
				params[selectedOption] = backupParams[selectedOption];
				selectedOption += 1;
				selectedOption %= backupParams.Length();
				params[selectedOption] = GREEN + params[selectedOption] + RESET; 
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

				string selectedObject = backupParams[selectedOption];
				
				return selectedObject;
				break;
			}

		}
	}
};


class MainChooseMenu {
public:
	virtual void NextMenuRun(string selectedParam) = 0;
	virtual string SetObject() = 0;

	void Run() {
		string object = SetObject();
		int selectedOption = 0;
		int pressedKey = 0;
		bool isExit = false;

		List<string>& backupParams = GetNewObjectParamsWithExtraParams(currentPath, object);
		List<string>& params = GetNewObjectParamsWithExtraParams(currentPath, object);

		params[0] = GREEN + params[0] + RESET;

		int identicalButtonsNumber = params.Length() - 2;

		while (true) {
			system(CLEAR_COMMAND);

			PrintParamsWithExtraButtons(params, backupParams, "Select " + object, identicalButtonsNumber);
			Sleep(SLEEP);

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

					NextMenuRun(backupParams[selectedOption]);

				} else {
					if (IsAdditionMenu(selectedOption, identicalButtonsNumber)) {
						string createdObject = InputMenu::Run("Enter the name of the new " + object + " : ").c_str();

						/*while (selectedObject == "") {
							InfoMenu::Run("You should write something!");
							selectedObject = SelectParamMenu::Run(object, "Select " + object + " to delete");
						}*/

						if (createdObject != ESCAPE_STRING && createdObject.length() > 0) {
							MakeDirectory(currentPath + "\\" + createdObject);

							// Params Reset
							backupParams = GetNewObjectParamsWithExtraParams(currentPath, object);
							params = GetNewObjectParamsWithExtraParams(currentPath, object);
							params[0] = GREEN + params[0] + RESET;
							selectedOption = 0;

							identicalButtonsNumber = params.Length() - 2;

							InfoMenu::Run("Successfully added " + object + "!");
						}
					}
					else {
						if (identicalButtonsNumber > 0) {
							string selectedObject = SelectParamMenu::Run(object, "Select " + object + " to delete");
							if (selectedObject != ESCAPE_STRING) {
								DeleteDirectory(currentPath + "\\" + selectedObject);

								// Params Reset
								backupParams = GetNewObjectParamsWithExtraParams(currentPath, object);
								params = GetNewObjectParamsWithExtraParams(currentPath, object);
								params[0] = GREEN + params[0] + RESET;
								selectedOption = 0;
								identicalButtonsNumber = params.Length() - 2;

								InfoMenu::Run("Successfully deleted " + object + "!");
							}
						}
						else {
							InfoMenu::Run("Nothing to delete!");
						}

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

class GroupSelectionMenu : public MainChooseMenu {
	string SetObject() {
		return "group";
	}
	void NextMenuRun(string selectedParam) {
		InfoMenu::Run("OK");
	}
};

class InstituteSelectionMenu : public MainChooseMenu {
	string SetObject() {
		return "institute";
	}
	void NextMenuRun(string selectedParam) {
		currentPath += "\\" + selectedParam;
		GroupSelectionMenu groupMenu;
		groupMenu.Run();
		RestoreCurrentPath();
	}
};
