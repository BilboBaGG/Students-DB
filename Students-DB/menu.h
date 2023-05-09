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
				if (inputString.length() <= maxLength && (key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z' || key == '-' || key <= '9' && key >= '0' || key == ' ')) {
					inputString += string(1, key);
					AddNewLetter(key);
					break;
				}
			}
		}
	}
};

class SelectDirParam : public virtual SelectParamMenuReturnModel {
public:
	SelectDirParam(string object_, string header_) {
		object = object_;
		header = header_;
	}
private:
	List<string>& ParseParams() override {
		return *GetNewObjectParams();
	}
};

class SelectStudentParam : public virtual SelectParamMenuReturnModel {
public:
	SelectStudentParam(string object_, string header_) {
		object = object_;
		header = header_;
	}
private:
	List<string>& ParseParams() override {
		return *GetParsedStudentsFromDir(currentPath);
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

class DefaultSelectionMenuWithButtons : public virtual MainChooseMenu {
protected:
	virtual List<string>& ParseParams() = 0;
	virtual void NextMenuRun(string selectedParam) = 0;
	virtual void OnCreate() = 0;
	virtual void OnDelete() = 0;

	void OnEnter() override {
		if (IsIdenticalParam(selectedOption, identicalButtonsNumber)) {
			NextMenuRun(backupParams[selectedOption]);
		}
		else {
			if (IsAdditionMenu(selectedOption, identicalButtonsNumber)) {
				OnCreate();
			}
			else {
				OnDelete();
			}

		}
	}
};

class StudentsParamsMenu : public virtual MainChooseMenu{
public:
	Student student;
	StudentsParamsMenu() {
		object = "students's paramenters";
		student = Read(currentPath);
	}
private:
	string header = "Select students's paramenters";
	List<string>& ParseParams() override {
		return *GetStudentsParams(currentPath, student);
	}
	void Printer() override {
		// PrintStudent
		PrintStudent(params, backupParams, header);
	}
	virtual void OnEnter() override {
		// switch
	}
};

class StudentSelectionMenu : public virtual DefaultSelectionMenuWithButtons {
public:
	StudentSelectionMenu() {
		object = "student";
	}
private:
	void Printer() override {
		PrintParamsWithExtraButtons(params, backupParams, "Select " + object + " from " + GetGroup(), identicalButtonsNumber);
	}
	List<string>& ParseParams() override {
		return *GetParsedStudentsFromDirWithExtraButtons(currentPath, object);
	}

	void NextMenuRun(string selectedParam) override {
		currentPath += "\\" + GetFilenameFromParsedStudent(selectedParam);
		StudentsParamsMenu paramsMenu{};
		paramsMenu.Run();
		RestoreCurrentPath();
	}

	void OnCreate() override{
		string surname = InputMenu::Run("Enter the student's surname: ", "", DEFAULT_STRING_LENGTH - 1);
		while (surname == "") {
			surname = InputMenu::Run("Please, enter some surname: ", "", DEFAULT_STRING_LENGTH - 1);
		}
		if (surname != ESCAPE_STRING) {
			string name = InputMenu::Run("Enter the student's name: ", "", DEFAULT_STRING_LENGTH - 1);
			while (name == "") {
				name = InputMenu::Run("Please, enter some name: ", "", DEFAULT_STRING_LENGTH - 1);
			}
			if (name != ESCAPE_STRING) {
				string patronymic = InputMenu::Run("Enter the student's patronymic: ", "", DEFAULT_STRING_LENGTH - 1);
				while (patronymic == "") {
					patronymic = InputMenu::Run("Please, enter some patronymic: ", "", DEFAULT_STRING_LENGTH - 1);
				}
				if (patronymic != ESCAPE_STRING) {
					if (IsStudentExists(surname + " " + name + " " + patronymic, currentPath)) {
						InfoMenu::Run("This student is already in the database");
					} else {
						Student student;
						student.SetName(name);
						student.SetSurname(surname);
						student.SetPatronymic(patronymic);
						student.SetGroup(GetGroup());
						student.SetInstitute(GetInstitute());
						Write(student);
						InfoMenu::Run("Student successfully added to the database!");
						ResetParams();
					}
				}
			}
		}
	}

	void OnDelete() override {
		if (identicalButtonsNumber > 0) {
			SelectStudentParam delMenu = SelectStudentParam(object, "Select " + object + " to delete");
			string selectedObject = delMenu.Run();
			if (selectedObject != ESCAPE_STRING) {
				DeleteStudentFile(currentPath + "\\" + GetFilenameFromParsedStudent(selectedObject));

				ResetParams();

				InfoMenu::Run("Successfully deleted " + object + "!");
			}
		}
		else {
			InfoMenu::Run("Nothing to delete!");
		}
	}
};

class StudentsOptionsSelectionMenu : public virtual MainChooseMenu {
public:
	StudentsOptionsSelectionMenu() {
		object = "option";
	}
private:
	string header = "Select option to view students";
	List<string>& ParseParams() override {
		List<string>* clearParams = new List<string>;
		clearParams->Append("Print all students");
		clearParams->Append("Divide students by grades (Variant 73)");
		return *clearParams;
	}
	void Printer() {
		PrintParams(params, backupParams, header);
	}
	virtual void OnEnter() override {
		if (selectedOption == 0) {
			StudentSelectionMenu student;
			student.Run();
		}
		else {
			InfoMenu::Run("Doesen't work now!");
		}
	}
};


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
		string createdObject = InputMenu::Run("Enter the name of the new " + object + " : ", "", 30);

		while (createdObject.length() == 0) {
			createdObject = InputMenu::Run("Enter correct " + object + " name : ", "", 30);
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



class InstituteSelectionMenu : public virtual DefaultSelectionMenuWithButtons {
public:
	InstituteSelectionMenu() {
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
		string createdObject = InputMenu::Run("Enter the name of the new " + object + " : ", "", 30);

		while (createdObject.length() == 0) {
			createdObject = InputMenu::Run("Enter correct " + object + " name : ", "", 30);
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
