#pragma once

class DeleteMark : public virtual SelectParamMenuReturnModel {
public:
	DeleteMark(int selectedSemester_) {
		selectedSemester = selectedSemester_;
		header = "Select subject to delete";
	}
private:
	int selectedSemester;
	void InerationPrinter() override {
		PrintMarks(params, backupParams, header);
	}
	List<string>& ParseParams() override {
		List<string>* marks = new List<string>;
		for (int i = 0; i < currentStudent->GetMarksNumberInSemester(selectedSemester); ++i) {
			marks->Append(currentStudent->GetSubjcetName(selectedSemester, i) + ": " + to_string(currentStudent->GetMark(selectedSemester, i)));
		}
		return *marks;
	}
};

class MarksSelectionMenu : public virtual DefaultSelectionMenuWithButtons {
public:
	MarksSelectionMenu(int selectedSemester_) {
		object = "mark";

		selectedSemester = selectedSemester_;
		header = "Here is marks for student " + currentStudent->GetSurname() + " " + currentStudent->GetName() + " " + currentStudent->GetPatronymic() + " in " + to_string(selectedSemester + 1) + " semester";
	}
private:
	string header;
	int selectedSemester;
	List<string>& ParseParams() override {
		List<string>* marks = new List<string>;
		for (int i = 0; i < currentStudent->GetMarksNumberInSemester(selectedSemester); ++i) {
			marks->Append(currentStudent->GetSubjcetName(selectedSemester, i) + ": " + to_string(currentStudent->GetMark(selectedSemester, i)));
		}
		marks->Append("Add subject");
		marks->Append("Delete subject");
		return *marks;
	}
	void Printer() override {
		PrintMarksWithExtraButtons(params, backupParams, header);
	}
	void OnCreate() override {
		if (currentStudent->GetMarksNumberInSemester(selectedSemester) != SUBJECTS_NUMBER) {
			string subject = letterOnlyInputMenu.Run("Ehter the name of new subject: ", "", 30);
			while (subject == "") {
				subject = letterOnlyInputMenu.Run("Ehter correct name of new subject: ", "", 30);
			}
			if (subject != ESCAPE_STRING) {
				if (!currentStudent->IsSubjectExists(selectedSemester, subject)) {
					string mark = markMenu.Run("Enter the mark: ", "", 1);

					while (mark == "") {
						mark = markMenu.Run("Enter the mark correctly: ", "", 1);
					}

					if (mark != ESCAPE_STRING) {
						currentStudent->AddMark(selectedSemester, subject, stoi(mark));
						Write(*currentStudent);
						InfoMenu::Run("Subject successfully added!!!");
						ResetParams();

					}
				}
				else {
					InfoMenu::Run("This subject is already exists!");
				}
			}
		}
		else {
			InfoMenu::Run("All marks are already filled!!");
		}
	}
	void OnDelete() override {
		if (currentStudent->GetMarksNumberInSemester(selectedSemester) != 0) {
			DeleteMark deleteMark{ selectedSemester };
			string subjectToDelete = deleteMark.Run();
			if (subjectToDelete != ESCAPE_STRING) {
				subjectToDelete = GetSubjectName(subjectToDelete);
				currentStudent->DeleteSubject(selectedSemester, subjectToDelete);

				Write(*currentStudent);
				InfoMenu::Run("Subject successfully deleted!");
				ResetParams();
			}
		}
		else {
			InfoMenu::Run("Nothing to delete!");
		}
	}
	void NextMenuRun(string selectedParam) override {
		string mark = markMenu.Run("Enter the new mark for " + GetSubjectName(selectedParam) + ": ", "", 1);

		while (mark == "") {
			mark = markMenu.Run("Enter the new mark for " + GetSubjectName(selectedParam) + " correctly: ", "", 1);
		}

		if (mark != ESCAPE_STRING) {
			currentStudent->SetMark(selectedSemester, GetSubjectName(selectedParam), stoi(mark));
			Write(*currentStudent);
			InfoMenu::Run("Subject successfully added!!!");
			ResetParams();
		}
	}

};

class SemesterSelectionMenu : public virtual MainChooseMenu {
public:
	SemesterSelectionMenu(string param) {
		header = "Select semester marks for student " + param;
	}
private:
	string header;
	List<string>& ParseParams() override {
		List<string>* params = new List<string>;
		for (int i = 1; i < 10; ++i) {
			params->Append("Semester " + to_string(i));
		}
		return *params;
	}
	void Printer() override {
		PrintParams(params, backupParams, header);
	}
	void OnEnter() override {
		MarksSelectionMenu marks{ selectedOption };
		marks.Run();

	}
};



class StudentsParamsMenu : public virtual MainChooseMenu {
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
		PrintStudent(params, backupParams, header);
	}
	virtual void OnEnter() override {
		switch (selectedOption) {
		case 0: {
			string newSurname = letterOnlyInputMenu.Run("Enter the student's surname: ", student.GetSurname(), DEFAULT_STRING_LENGTH - 1);
			while (newSurname == "") {
				newSurname = letterOnlyInputMenu.Run("Enter the correct surname: ", student.GetSurname(), DEFAULT_STRING_LENGTH - 1);
			}
			if (newSurname != ESCAPE_STRING) {
				DeleteFileByFilename(currentPath + ".enc");
				student.SetSurname(newSurname);
				currentPath = GetCurrentPath(student);
			}
			break;
		}
		case 1: {
			string newName = letterOnlyInputMenu.Run("Enter the student's name: ", student.GetName(), DEFAULT_STRING_LENGTH - 1);
			while (newName == "") {
				newName = letterOnlyInputMenu.Run("Enter the correct name: ", student.GetName(), DEFAULT_STRING_LENGTH - 1);
			}
			if (newName != ESCAPE_STRING) {
				DeleteFileByFilename(currentPath + ".enc");
				student.SetName(newName);
				currentPath = GetCurrentPath(student);
			}
			break;
		}
		case 2: {
			string newPatronymic = letterOnlyInputMenu.Run("Enter the student's name: ", student.GetPatronymic(), DEFAULT_STRING_LENGTH - 1);
			while (newPatronymic == "") {
				newPatronymic = letterOnlyInputMenu.Run("Enter the correct name: ", student.GetPatronymic(), DEFAULT_STRING_LENGTH - 1);
			}
			if (newPatronymic != ESCAPE_STRING) {
				DeleteFileByFilename(currentPath + ".enc");
				student.SetPatronymic(newPatronymic);
				currentPath = GetCurrentPath(student);
			}
			break;
		}
		case 3: {
			string newInstitute = baseInputMenu.Run("Enter the student's institute: ", student.GetInstitute(), DEFAULT_STRING_LENGTH - 1);
			while (newInstitute == "") {
				newInstitute = baseInputMenu.Run("Enter the correct institute: ", student.GetInstitute(), DEFAULT_STRING_LENGTH - 1);
			}
			if (newInstitute != ESCAPE_STRING) {
				DeleteFileByFilename(".\\Students\\" + student.GetInstitute() + "\\" + student.GetGroup() + "\\" + student.GetSurname() + "_" + student.GetName() + "_" + student.GetPatronymic() + ".bin.enc");
				student.SetInstitute(newInstitute);
				if (!(IsDirectoryExists(student.GetInstitute(), ".\\Students\\"))) {
					MakeDirectory(".\\Students\\" + student.GetInstitute());
				}
				if (!(IsDirectoryExists(student.GetGroup(), ".\\Students\\" + student.GetInstitute() + "\\"))) {
					MakeDirectory(".\\Students\\" + student.GetInstitute() + "\\" + student.GetGroup());
				}

			}
			break;
		}
		case 4: {
			string newDepartment = baseInputMenu.Run("Enter the student's department: ", student.GetDepartment(), DEFAULT_STRING_LENGTH - 1);
			while (newDepartment == "") {
				newDepartment = baseInputMenu.Run("Enter the correct department: ", student.GetDepartment(), DEFAULT_STRING_LENGTH - 1);
			}
			if (newDepartment != ESCAPE_STRING) {
				student.SetDepartment(newDepartment);
			}
			break;
		}
		case 5: {
			string newGroup = baseInputMenu.Run("Enter the student's group: ", student.GetGroup(), DEFAULT_STRING_LENGTH - 1);
			while (newGroup == "") {
				newGroup = baseInputMenu.Run("Enter the correct group: ", student.GetGroup(), DEFAULT_STRING_LENGTH - 1);
			}
			if (newGroup != ESCAPE_STRING) {
				DeleteFileByFilename(".\\Students\\" + student.GetInstitute() + "\\" + student.GetGroup() + "\\" + student.GetSurname() + "_" + student.GetName() + "_" + student.GetPatronymic() + ".bin.enc");
				student.SetGroup(newGroup);

				if (!(IsDirectoryExists(student.GetGroup(), ".\\Students\\" + student.GetInstitute() + "\\"))) {
					MakeDirectory(".\\Students\\" + student.GetInstitute() + "\\" + student.GetGroup());
				}
			}
			break;
		}
		case 6: {
			string newRecordBookNumber = baseInputMenu.Run("Enter the student's record book number: ", student.GetRecordBookNumber(), RECORD_BOOK_STR_LENGTH - 2);
			while (newRecordBookNumber == "") {
				newRecordBookNumber = baseInputMenu.Run("Enter the correct record book number: ", student.GetRecordBookNumber(), RECORD_BOOK_STR_LENGTH - 2);
			}
			if (newRecordBookNumber != ESCAPE_STRING) {
				student.SetRecordBookNumber(newRecordBookNumber);
			}
			break;
		}
		case 7: {
			string newGender = genderInut.Run("Enter the student's gender (M or W): ", student.GetGender(), 1);
			while (newGender == "") {
				newGender = genderInut.Run("Enter the correct gender (M or W): ", student.GetGender(), 1);
			}
			if (newGender != ESCAPE_STRING) {
				student.SetGender(newGender);
			}
			break;
		}
		case 8: {
			string newAdmissionYear = numberOnlyInput.Run("Enter the student's admission year: ", student.GetStringAdmissionYear(), 4);
			while (newAdmissionYear == "") {
				newAdmissionYear = numberOnlyInput.Run("Enter the correct admission year: ", student.GetStringAdmissionYear(), 4);
			}
			if (newAdmissionYear != ESCAPE_STRING) {
				student.SetAdmissionYear(stoi(newAdmissionYear));
			}
			break;
		}
		case 9: {
			string day = numberOnlyInput.Run("Enter the student's day of birthday: ", "", 2);
			while (day == "") {
				day = numberOnlyInput.Run("Please, enter correct day of birthday: ", "", 2);
			}
			if (day != ESCAPE_STRING) {

				if (stoi(day) > 31) {
					InfoMenu::Run("Too big day of birthday!");
					break;
				}
				string month = numberOnlyInput.Run("Enter the student's month of birthday: ", "", 2);
				while (month == "" || stoi(month) > 12) {
					month = numberOnlyInput.Run("Please, enter correct month of birthday: ", "", 2);
				}
				if (month != ESCAPE_STRING) {

					if (stoi(day) == 31 && (stoi(month) == 2 || stoi(month) == 4 || stoi(month) == 6 || stoi(month) == 9 || stoi(month) == 11)) {
						InfoMenu::Run("There are no 31 day in the entered month!");
						break;
					}
					if (stoi(day) == 30 && stoi(month) == 2) {
						InfoMenu::Run("It can be only 29 day in February!");
						break;
					}


					string year = numberOnlyInput.Run("Enter the student's year of birthday: ", "", 4);
					while (year == "") {
						year = numberOnlyInput.Run("Please, enter correct year of birthday: ", "", 4);
					}
					if (year != ESCAPE_STRING) {
						Date birthday = { stoi(day),stoi(month), stoi(year) };
						student.SetBirthday(birthday);
					}
				}
			}
			break;
		}
		case 10: {
			currentStudent = &student;
			SemesterSelectionMenu semesters{ student.GetSurname() + " " + student.GetName() + " " + student.GetPatronymic() };
			semesters.Run();
			break;
		}
		}
		Write(student);
		ResetParams();
	}
};

class TypeStudentMenu : public virtual MainChooseMenu {
public:
	TypeStudentMenu(List<string>* backupParams_, List<string>* params_, string type_) {
		type = type_;
		params = *params_;
		backupParams = *backupParams_;
	}
protected:
	string type = "";

	void Printer() override {
		PrintParams(params, backupParams, "Select " + type + " student from " + GetGroup());
	}

	List<string>& ParseParams() override {
		List<string>* temp = new List <string>();
		for (int i = 0; i < backupParams.Length(); ++i) {
			temp->Append(backupParams[i]);
		}

		return *temp;
	}

	void OnEnter() override {
		currentPath += "\\" + GetFilenameFromParsedStudent(backupParams[selectedOption]);
		StudentsParamsMenu paramsMenu{};
		paramsMenu.Run();
		RestoreCurrentPath();
		isExit = true;
	}
}; 

class TypeMenuLogic {
public:
	static void Run(List<Student*>& students, string type) {
		if (students.Length() > 0) {
			string minYear = numberOnlyInput.Run("Enter the minimum birthday year of students : ", "", 4);
			while (minYear == "") {
				minYear = numberOnlyInput.Run("Enter the minimum birthday year of students correctly : ", "", 4);
			}

			if (minYear != ESCAPE_STRING) {
				string maxYear = numberOnlyInput.Run("Enter the maximum birthday year of students : ", "", 4);

				while (maxYear == "") {
					maxYear = numberOnlyInput.Run("Enter the maximum birthday year of students correctly : ", "", 4);
				}

				if (maxYear != ESCAPE_STRING) {
					if (stoi(maxYear) < stoi(minYear)) {
						InfoMenu::Run("You entered too small maximum year!!");
					}
					else {
						List<string> studentsString;
						List<string> studentBackupString;

						for (int i = 0; i < students.Length(); ++i) {
							Student& tempStudent = *students.Get(i);
							if (tempStudent.GetBirthday().GetYear() <= stoi(maxYear) && tempStudent.GetBirthday().GetYear() >= stoi(minYear)) {
								studentsString.Append(tempStudent.GetSurname() + " " + tempStudent.GetName() + " " + tempStudent.GetPatronymic());
								studentBackupString.Append(tempStudent.GetSurname() + " " + tempStudent.GetName() + " " + tempStudent.GetPatronymic());
							}
						}

						if (studentsString.Length() > 0) {
							TypeStudentMenu studentMenu{ &studentBackupString, &studentsString, type };
							studentMenu.Run();
						}
						else {
							InfoMenu::Run("No such students in this date range!!");
						}
					}
				}
			}
		}
		else {
			InfoMenu::Run("There are no " + type + " student in " + GetGroup());
		}
	}
};

class StudentModeMenu : public virtual MainChooseMenu {
public:
	StudentModeMenu() {
		header = "Select mode to view students";
	}
private:
	string header;
	List<string>& ParseParams() override {
		List<string>* params = new List<string>;
		params->Append("Excellent students");
		params->Append("Good students");
		params->Append("Students with bad marks");
		return *params;
	}
	void Printer() override {
		PrintParams(params, backupParams, header);
	}
	void OnEnter() override {
		switch (selectedOption) {
		case 0: {
			List<Student*> students = *GetTypedStudents(currentPath, 5);
			TypeMenuLogic::Run(students, "excellent");
			break;
		}
		case 1: {
			List<Student*> students = *GetTypedStudents(currentPath, 4);
			TypeMenuLogic::Run(students, "good");
			break;
		}
		case 2: {
			List<Student*> students = *GetTypedStudents(currentPath, 3);
			TypeMenuLogic::Run(students, "bad");

			break;
		}
		}
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
		ResetParams();
	}

	void OnCreate() override {
		string surname = letterOnlyInputMenu.Run("Enter the student's surname: ", "", DEFAULT_STRING_LENGTH - 1);
		while (surname == "") {
			surname = letterOnlyInputMenu.Run("Please, enter some surname: ", "", DEFAULT_STRING_LENGTH - 1);
		}
		if (surname != ESCAPE_STRING) {
			string name = letterOnlyInputMenu.Run("Enter the student's name: ", "", DEFAULT_STRING_LENGTH - 1);
			while (name == "") {
				name = letterOnlyInputMenu.Run("Please, enter some name: ", "", DEFAULT_STRING_LENGTH - 1);
			}
			if (name != ESCAPE_STRING) {
				string patronymic = letterOnlyInputMenu.Run("Enter the student's patronymic: ", "", DEFAULT_STRING_LENGTH - 1);
				while (patronymic == "") {
					patronymic = letterOnlyInputMenu.Run("Please, enter some patronymic: ", "", DEFAULT_STRING_LENGTH - 1);
				}
				if (patronymic != ESCAPE_STRING) {
					if (IsStudentExists(surname + " " + name + " " + patronymic, currentPath)) {
						InfoMenu::Run("This student is already in the database");
					}
					else {
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
				DeleteFileByFilename(currentPath + "\\" + GetFilenameFromParsedStudent(selectedObject) + ".enc");

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
	void Printer() override {
		PrintParams(params, backupParams, header);
	}
	virtual void OnEnter() override {
		if (selectedOption == 0) {
			StudentSelectionMenu student;
			student.Run();
		}
		else {
			StudentModeMenu modeMenu;
			modeMenu.Run();

		}
	}
};