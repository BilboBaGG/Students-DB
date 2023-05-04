#pragma once

string currentPath = ".\\Students";

#include <conio.h>
#include <windows.h>

#include "printers.h"
#include "directory_functions.h"
#include "object_functions.h"

class InputMenu {
public:
	static string Run(string message, string iString) {
		string inputString = iString;
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

class MenuModel {
private:
	int pressedKey = 0;
	bool isExit = false;

	void virtual Printer() {}
	void virtual StartFunction() {}

	void virtual OnDownArrow() {}
	void virtual OnUpArrow() {}
	void virtual OnEnter() {}
	void virtual DefaultKeyPressed(int pressedKey) {}

	virtual void ExitFunction() {}

public:
	void Run() {

		StartFunction();

		while (true) {
			system(CLEAR_COMMAND);

			Printer();
			Sleep(SLEEP);

			pressedKey = _getch();

			switch (pressedKey) {

			case ESC:
				isExit = true;
				break;
			case ARROW_DOWN:
				OnDownArrow();
				break;
			case ARROW_UP:
				OnUpArrow();
				break;
			case ENTER:
				OnEnter();
				break;

			default:
				DefaultKeyPressed(pressedKey);
			}

			if (isExit) {
				system(CLEAR_COMMAND);
				ExitFunction();
				break;
			}
		}
	}
};


class MainChooseMenu : public virtual MenuModel {
protected:
	string object = "";
	List<string>& backupParams = GetClearList();
	List<string>& params = GetClearList();

	int identicalButtonsNumber = 0;
	int selectedOption = 0;

private:

	void SetSelecetdOption(int selectedOption_) {
		selectedOption = selectedOption_;
	}

	virtual List<string>& ParseParams(string currentPath, string object) = 0;
	virtual void NextMenuRun(string selectedParam) = 0;

	void ResetParams() {
		backupParams = ParseParams(currentPath, object);
		params = ParseParams(currentPath, object);
		params[0] = GREEN + params[0] + RESET;
		selectedOption = 0;

		identicalButtonsNumber = params.Length() - 2;
	}

	virtual void Printer() {}

	void StartFunction() {
		ResetParams();
	}

	// Move selector down
	void OnDownArrow() {
		params[selectedOption] = backupParams[selectedOption];
		selectedOption += 1;
		selectedOption %= backupParams.Length();
		params[selectedOption] = GREEN + params[selectedOption] + RESET;
	}

	// Move selector up
	void OnUpArrow() {
		params[selectedOption] = backupParams[selectedOption];
		if (selectedOption == 0) {
			selectedOption = backupParams.Length() - 1;
		}
		else {
			selectedOption -= 1;
			selectedOption %= backupParams.Length();
		}
		params[selectedOption] = GREEN + params[selectedOption] + RESET;
	}

	void OnEnter() {
		if (IsIdenticalParam(selectedOption, identicalButtonsNumber)) {
			NextMenuRun(backupParams[selectedOption]);
		}
		else {
			if (IsAdditionMenu(selectedOption, identicalButtonsNumber)) {
				string createdObject = InputMenu::Run("Enter the name of the new " + object + " : ", "").c_str();

				// Need to create validation

				if (createdObject != ESCAPE_STRING && createdObject.length() > 0) {
					MakeDirectory(currentPath + "\\" + createdObject);

					ResetParams();

					InfoMenu::Run("Successfully added " + object + "!");
				}
			}
			else {
				if (identicalButtonsNumber > 0) {
					string selectedObject = SelectParamMenu::Run(object, "Select " + object + " to delete");
					if (selectedObject != ESCAPE_STRING) {
						DeleteDirectory(currentPath + "\\" + selectedObject);

						ResetParams();

						InfoMenu::Run("Successfully deleted " + object + "!");
					}
				}
				else {
					InfoMenu::Run("Nothing to delete!");
				}

			}

		}
	}

	void DefaultKeyPressed(int pressedKey) {}

	void ExitFunction() {}

};

class GroupSelectionMenu : public virtual MainChooseMenu {
public:
	GroupSelectionMenu() {
		object = "group";
	}
private:
	void Printer() {
		PrintParamsWithExtraButtons(params, backupParams, "Select " + object + " from " + GetLastParam(), identicalButtonsNumber);
	}
	void NextMenuRun(string selectedParam) {
		InfoMenu::Run("OK");
	}
	List<string>& ParseParams(string currentPath, string object) {
		return *GetNewObjectParamsWithExtraParams(currentPath, object);
	}
};

class InstituteSelectionMenu : public virtual MainChooseMenu {
public:
	InstituteSelectionMenu() {
		object = "institute";
	}
private:
	void Printer() {
		PrintParamsWithExtraButtons(params, backupParams, "Select " + object + " from database", identicalButtonsNumber);
	}
	void NextMenuRun(string selectedParam) {
		currentPath += "\\" + selectedParam;
		GroupSelectionMenu groupMenu;
		groupMenu.Run();
		RestoreCurrentPath();
	}

	List<string>& ParseParams(string currentPath, string object) {
		return *GetNewObjectParamsWithExtraParams(currentPath, object);
	}
};

