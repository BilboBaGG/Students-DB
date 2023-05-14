#pragma once

#include <conio.h>
#include <windows.h>


#include "list.h"
#include "settings.h"
#include "student.h"
#include "file_functions.h"

string currentPath = ".\\Students";
Student* currentStudent;

#include "printers.h"
#include "directory_functions.h"
#include "object_functions.h"

#include "menu_models.h"
#include "input_menus.h"

BaseInputMenu baseInputMenu{};
InputLetterOnlyMenu letterOnlyInputMenu{};
GenderInputMenu genderInut{};
InputNumberOnlyMenu numberOnlyInput{};
InputMarkMenu markMenu{};

#include "default_selection_menus.h"
#include "student_menus.h"


class GroupSelectionMenu : public virtual DefaultSelectionMenuWithButtons {
public:
	GroupSelectionMenu() {
		object = "group";
	}
private:
	void Printer() {
		PrintParamsWithExtraButtons(params, backupParams, "Select " + object + " from " + GetInstitute(), identicalButtonsNumber);
	}
	void NextMenuRun(string selectedParam) override {
		currentPath += "\\" + selectedParam;
		StudentsOptionsSelectionMenu option{};
		option.Run();
		RestoreCurrentPath();

	}
	List<string>& ParseParams() override {
		return *GetNewDirParamsWithExtraParams(currentPath, object);
	}
	void OnCreate() {
		string createdObject = baseInputMenu.Run("Enter the name of the new " + object + " : ", "", 30);

		while (createdObject.length() == 0) {
			createdObject = baseInputMenu.Run("Enter correct " + object + " name : ", "", 30);
		}

		if (createdObject != ESCAPE_STRING) {
			if (!IsDirectoryExists(createdObject, currentPath)) {
				MakeDirectory(currentPath + "\\" + createdObject);

				ResetParams();

				InfoMenu::Run("Successfully added " + object + "!");

			}
			else {
				InfoMenu::Run("Group already created!");
			}
		}
	}
	void OnDelete() override {
		if (identicalButtonsNumber > 0) {
			SelectDirParam delMenu = SelectDirParam(object, "Select " + object + " to delete");
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
};

class MainMenu : public virtual DefaultSelectionMenuWithButtons {
public:
	MainMenu() {
		object = "institute";
	}
private:
	void Printer() override {
		PrintParamsWithExtraButtons(params, backupParams, "Select " + object + " from DB", identicalButtonsNumber);
	}
	void NextMenuRun(string selectedParam) override {
		currentPath += "\\" + selectedParam;
		GroupSelectionMenu groupMenu;
		groupMenu.Run();
		RestoreCurrentPath();
	}

	List<string>& ParseParams() override {
		return *GetNewDirParamsWithExtraParams(currentPath, object);
	}
	void OnCreate() { // Default (we can make custom)
		string createdObject = baseInputMenu.Run("Enter the name of the new " + object + " : ", "", 30);

		while (createdObject.length() == 0) {
			createdObject = baseInputMenu.Run("Enter correct " + object + " name : ", "", 30);
		}

		if (createdObject != ESCAPE_STRING) {
			if (!IsDirectoryExists(createdObject, currentPath)) {
				MakeDirectory(currentPath + "\\" + createdObject);

				ResetParams();

				InfoMenu::Run("Successfully added " + object + "!");

			}
			else {
				InfoMenu::Run("Institute already created!");
			}
		}
	}
	void OnDelete() override { // Default (we can make custom)
		if (identicalButtonsNumber > 0) {
			SelectDirParam delMenu = SelectDirParam(object, "Select " + object + " to delete");
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
};
