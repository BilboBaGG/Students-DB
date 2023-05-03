#include "date.h"
#include "marks.h"

class Student {
private:
	string name, surname, patronymic, institute, department, group, recordBookNumber, gender;
	Date birthday;
	int admissionYear;
	List<Marks*> marks;
public:
	Student() {
		name = "";
		surname = "";
		patronymic = "";

		institute = "";
		department = "";
		group = "";
		recordBookNumber = "";
		gender = "";
		Date clearDate;
		birthday = clearDate;
		admissionYear = 0;

		for (int i = 0; i < 9; ++i) {
			Marks* temp = new Marks(i+1);
			marks.Append(temp);
		}
	}

	~Student() {
		for (int i = 0; i < 9; ++i) {
			delete marks[i];
		}
	}

	string GetName() {
		return name;
	}
	void SetName(string name_) {
		name = name_;
	}

	string GetSurname() {
		return surname;
	}
	void SetSurname(string surname_) {
		surname = surname_;
	}

	string GetPatronymic() {
		return patronymic;
	}
	void SetPatronymic(string patronymic_) {
		patronymic = patronymic_;
	}

	string GetInstitute() {
		return institute;
	}
	void SetInstitute(string institute_) {
		institute = institute_;
	}

	string GetDepartment() {
		return department;
	}
	void SetDepartment(string department_) {
		department = department_;
	}

	string GetGroup() {
		return group;
	}
	void SetGroup(string group_) {
		group = group_;
	}

	string GetRecordBookNumber() {
		return recordBookNumber;
	}
	void SetRecordBookNumber(string recordBookNumber_) {
		recordBookNumber = recordBookNumber_;
	}

	string GetGender() {
		return gender;
	}
	void SetGender(string gender_) {
		gender = gender_;
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

	Marks& GetSemesterMarks(int semesterNumber) {
		return *(marks[semesterNumber - 1]);
	}

	string StringParseMarks() {
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
	}

};
