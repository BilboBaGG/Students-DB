#include "date.h"
//#include "marks.h"

class Student {

private:
	char name[DEFAULT_STRING_LENGTH] = "", surname[DEFAULT_STRING_LENGTH] = "", patronymic[DEFAULT_STRING_LENGTH] = "", institute[DEFAULT_STRING_LENGTH] = "", department[DEFAULT_STRING_LENGTH] = "", group[DEFAULT_STRING_LENGTH] = "", recordBookNumber[RECORD_BOOK_STR_LENGTH] = "", gender[2] = "";
	Date birthday;
	int admissionYear;
	int marks[SEMESTERS_NUMBER][SUBJECTS_NUMBER];
	char subjectNames[SEMESTERS_NUMBER][SUBJECTS_NUMBER][31];

	// List<Marks*> marks;

public:
	Student() {
		Date clearDate;
		birthday = clearDate;
		admissionYear = 0;

		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 10; ++j) {
				marks[i][j] = 0;
				strcpy_s(subjectNames[i][j], "");
			}
		}
	}

	string GetName() {
		return name;
	}
	void SetName(string name_) {
		strcpy_s(name, name_.c_str());
	}

	string GetSurname() {
		return surname;
	}
	void SetSurname(string surname_) {
		strcpy_s(surname, surname_.c_str());
	}

	string GetPatronymic() {
		return patronymic;
	}
	void SetPatronymic(string patronymic_) {
		strcpy_s(patronymic, patronymic_.c_str());
	}

	string GetInstitute() {
		return institute;
	}
	void SetInstitute(string institute_) {
		strcpy_s(institute, institute_.c_str());
	}

	string GetDepartment() {
		return department;
	}
	void SetDepartment(string department_) {
		strcpy_s(department, department_.c_str());
	}

	string GetGroup() {
		return group;
	}
	void SetGroup(string group_) {
		strcpy_s(group, group_.c_str());
	}

	string GetRecordBookNumber() {
		return recordBookNumber;
	}
	void SetRecordBookNumber(string recordBookNumber_) {
		strcpy_s(recordBookNumber, recordBookNumber_.c_str());
	}

	string GetGender() {
		return gender;
	}

	void SetGender(string gender_) {
		strcpy_s(gender, gender_.c_str());
	}

	int GetAdmissionYear() {
		return admissionYear;
	}
	void SetAdmissionYear(int admissionYear_) {
		admissionYear = admissionYear_;
	}

	Date GetBirthday() {
		return birthday;
	}
	void SetBirthday(Date birthday_) {
		birthday = birthday_;
	}

	int GetMark(int semesterNumber_, int index) {
		return marks[semesterNumber_][index];
	}

	int GetMark(int semesterNumber_, string subjectName) {
		int mark = 0;
		for (int i = 0; i < SUBJECTS_NUMBER; ++i) {
			if (!strcmp(subjectName.c_str(), subjectNames[semesterNumber_][i])) {
				mark = marks[semesterNumber_][i];
				break;
			}
		}
		return mark;
	}
	
	void DeleteSubject(int semesterNumber_, string subjectName) {
		for (int i = 0; i < SUBJECTS_NUMBER; ++i) {
			if (!strcmp(subjectNames[semesterNumber_][i], subjectName.c_str())) {
				strcpy_s(subjectNames[semesterNumber_][i], "");
				marks[semesterNumber_][i] = 0;
			}
		}
	}

	string GetSubjcetName(int semesterNumber_, int index) {
		return subjectNames[semesterNumber_][index];
	}

	int GetMarksNumberInSemester(int semesterNumber_) {
		int countMarks = 0;
		for (int i = 0; i < SUBJECTS_NUMBER; ++i) {
			if (marks[semesterNumber_][i] == 0) {
				break;
			}
			else {
				countMarks += 1;
			}
		}
		return countMarks;
	}

	void AddMark(int semesterNumber_, string subjectName, int mark) {
		for (int i = 0; i < SUBJECTS_NUMBER; ++i) {
			if (marks[semesterNumber_][i] == 0) {
				marks[semesterNumber_][i] = mark;
				strcpy_s(subjectNames[semesterNumber_][i], subjectName.c_str());
				break;
			}
		}
	}

	/*Marks& GetSemesterMarks(int semesterNumber) {
		return *(marks[semesterNumber - 1]);
	}*/

	/*string StringParseMarks() {
		string parsedMarks = "";


		for (int i = 0; i < marks.Length(); ++i) {
			if (marks[i]->GetSubjectsNumber()!=0) {	
				parsedMarks += to_string(marks[i]->GetSemesterNumber()) + ":" + marks[i]->GetParsedMarks();
				if (i != marks.Length() - 1) {
					parsedMarks += "\n";
				}
			}
		}
		return parsedMarks;
	}*/

};
