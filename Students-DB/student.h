#include "date.h"
//#include "marks.h"

class Student {

private:
	char name[31] = "", surname[31] = "", patronymic[31] = "", institute[31] = "", department[31] = "", group[31] = "", recordBookNumber[31] = "", gender[31] = "";
	Date birthday;
	int admissionYear;
	int marks[SEMESTERS_NUMBER][SUBJECTS_NUMBER];
	char subjectNames[SEMESTERS_NUMBER][SUBJECTS_NUMBER][30];

	// List<Marks*> marks;

public:
	Student() {
		Date clearDate;
		birthday = clearDate;
		admissionYear = 0;

		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 10; ++j) {
				marks[i][j] = 0;
				strcpy(subjectNames[i][j], "");
			}
		}
	}

	string GetName() {
		return name;
	}
	void SetName(string name_) {
		strcpy(name, name_.c_str());
	}

	string GetSurname() {
		return surname;
	}
	void SetSurname(string surname_) {
		strcpy(surname, surname_.c_str());
	}

	string GetPatronymic() {
		return patronymic;
	}
	void SetPatronymic(string patronymic_) {
		strcpy(patronymic, patronymic_.c_str());
	}

	string GetInstitute() {
		return institute;
	}
	void SetInstitute(string institute_) {
		strcpy(institute, institute_.c_str());
	}

	string GetDepartment() {
		return department;
	}
	void SetDepartment(string department_) {
		strcpy(department, department_.c_str());
	}

	string GetGroup() {
		return group;
	}
	void SetGroup(string group_) {
		strcpy(group, group_.c_str());
	}

	string GetRecordBookNumber() {
		return recordBookNumber;
	}
	void SetRecordBookNumber(string recordBookNumber_) {
		strcpy(recordBookNumber, recordBookNumber_.c_str());
	}

	string GetGender() {
		return gender;
	}
	void SetGender(string gender_) {
		strcpy(gender, gender_.c_str());
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

	//int GetSubjcetName(int semesterNumber_, int index) {
	//	subject
	//	for (int i = 0; i < SUBJECTS_NUMBER; ++i) {
	//		if (!strcmp(subjectName.c_str(), subjectNames[semesterNumber_][i])) {
	//			mark = marks[semesterNumber_][i];
	//			break;
	//		}
	//	}
	//	return mark;
	//}

	

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
				strcpy(subjectNames[semesterNumber_][i], subjectName.c_str());
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
