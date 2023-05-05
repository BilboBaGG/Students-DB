#pragma once

string currentPath = ".\\Students";

#include <conio.h>
#include <windows.h>

#include "printers.h"
#include "directory_functions.h"
#include "object_functions.h"
#include "menu_models.h"


class InputMenu {
public:
	static string Run(string message, string iString, int maxLength) {
		string inputString = iString;
		int key = 0;
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
				if (inputString.length() <= maxLength && (key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z' || key == '-' || key <= '9' && key >= '0')) {
					inputString += string(1, key);
					AddNewLetter(key);
					break;
				}
			}
		}
	}
};

class SelectParamMenu : public virtual ReturnMenuModel {
protected:
	string object = "";
	string header = "";
	List<string>& backupParams = GetClearList();
	List<string>& params = GetClearList();

	int selectedOption = 0;
private:
	virtual List<string>& ParseParams() = 0;

	void ResetParams() {
		backupParams = ParseParams();
		params = ParseParams();
		params[0] = GREEN + params[0] + RESET;
		selectedOption = 0;
	}

	void StartFunction() {
		ResetParams();
	}

	void InerationPrinter() {
		PrintParams(params, backupParams, header);
	}

	string OnEsc() {
		delete& backupParams;
		delete& params;
		return ESCAPE_STRING;
	}

	void OnDownArrow() {
		params[selectedOption] = backupParams[selectedOption];
		selectedOption += 1;
		selectedOption %= backupParams.Length();
		params[selectedOption] = GREEN + params[selectedOption] + RESET;
	}

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

	string OnEnter() {
		return backupParams[selectedOption];
	}
};

class SelectParam : public virtual SelectParamMenu {
public:
	SelectParam(string object_, string header_) {
		object = object_;
		header = header_;
	}
private:
	List<string>& ParseParams() {
		return *GetNewObjectParams();
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

class StudentsOptionSelectionMenu : public virtual MainChooseMenu {
public:
	StudentsOptionSelectionMenu() {
		object = "option";

	}
private:
	string header = "Select option to view students";
	List<string>& ParseParams() {
		List<string>* clearParams = new List<string>;
		clearParams->Append("Print all students");
		clearParams->Append("Divide students by grades (Variant 73)");
		return *clearParams;
	}
	void NextMenuRun(string selectedParam) {}
	void Printer() {
		PrintParams(params, backupParams, header);
	}

};

class DefaultSelectionMenuWithButtons : public virtual MainChooseMenu {
protected:
	virtual List<string>& ParseParams() { return GetClearList(); }
	virtual void OnCreate(string createdObject) {}

	void OnEnter() {
		if (IsIdenticalParam(selectedOption, identicalButtonsNumber)) {
			NextMenuRun(backupParams[selectedOption]);
		}
		else {
			if (IsAdditionMenu(selectedOption, identicalButtonsNumber)) {
				string createdObject = InputMenu::Run("Enter the name of the new " + object + " : ", "", 30).c_str();

				// Need to create validation

				if (createdObject != ESCAPE_STRING && createdObject.length() > 0) {
					OnCreate(createdObject);

					ResetParams();

					InfoMenu::Run("Successfully added " + object + "!");
				}
			}
			else {
				if (identicalButtonsNumber > 0) {

					SelectParam delMenu = SelectParam(object, "Select " + object + " to delete");
					string selectedObject = delMenu.Run();

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
};

class GroupSelectionMenu : public virtual DefaultSelectionMenuWithButtons {
public:
	GroupSelectionMenu() {
		object = "group";
	}
private:
	void OnCreate(string createdObject) {
		MakeDirectory(currentPath + "\\" + createdObject);
	}
	void Printer() {
		PrintParamsWithExtraButtons(params, backupParams, "Select " + object + " from " + GetLastParam(), identicalButtonsNumber);
	}
	void NextMenuRun(string selectedParam) {
		StudentsOptionSelectionMenu option{};
		option.Run();

	}
	List<string>& ParseParams() {
		return *GetNewObjectParamsWithExtraParams(currentPath, object);
	}
};

class InstituteSelectionMenu : public virtual DefaultSelectionMenuWithButtons {
public:
	InstituteSelectionMenu() {
		object = "institute";
	}
private:
	void OnCreate(string createdObject) {
		MakeDirectory(currentPath + "\\" + createdObject);
	}
	void Printer() {
		PrintParamsWithExtraButtons(params, backupParams, "Select " + object + " from DB", identicalButtonsNumber);
	}
	void NextMenuRun(string selectedParam) {
		currentPath += "\\" + selectedParam;
		GroupSelectionMenu groupMenu;
		groupMenu.Run();
		RestoreCurrentPath();
	}

	List<string>& ParseParams() {
		return *GetNewObjectParamsWithExtraParams(currentPath, object);
	}
};
