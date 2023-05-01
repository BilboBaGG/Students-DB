#include <fstream>

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

	Student(string filename) {
		ifstream ifs;
		ifs.open(filename, ios::binary | ios::in);

		char temp[15]{};

		ifs.read((char*)&temp, sizeof(char) * 15);
		name = temp;

		ifs.read((char*)&temp, sizeof(char) * 15);
		surname = temp;

		ifs.read((char*)&temp, sizeof(char) * 15);
		patronymic = temp;

		ifs.read((char*)&temp, sizeof(char) * 15);
		institute = temp;

		ifs.read((char*)&temp, sizeof(char) * 15);
		department = temp;

		ifs.read((char*)&temp, sizeof(char) * 15);
		group = temp;

		ifs.read((char*)&temp, sizeof(char) * 15);
		recordBookNumber = temp;

		ifs.read((char*)&temp, sizeof(char) * 15);
		gender = temp;

		int day = 0;
		int month = 0;
		int year = 0;

		ifs.read((char*)&day, sizeof(int));
		ifs.read((char*)&month, sizeof(int));
		ifs.read((char*)&year, sizeof(int));

		Date date{ day, month, year};
		birthday = date;

		ifs.read((char*)&admissionYear, sizeof(int));

		char tempSubjectName[80]{};
		int tempSubjectMark = 0;

		for (int i = 0; i < 9; ++i) {
			Marks* temp = new Marks(i + 1);
			marks.Append(temp);
		}

		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 10; ++j) {
				ifs.read((char*)&tempSubjectName, sizeof(char) * 80);
				marks[i]->GetSubject(j).SetName(tempSubjectName);

				ifs.read((char*)&tempSubjectMark, sizeof(int));
				marks[i]->GetSubject(j).SetMark(tempSubjectMark);
			}
		}

		ifs.close();
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

	void Write() {
		string path = "./Students/" + institute + "/" + group + "/" + surname + "_" + name + "_" + patronymic + ".bin";

		ofstream of;
		of.open(path, ios::binary | ios::out);
		of.write(name.c_str(), sizeof(char) * 15);
		of.write(surname.c_str(), sizeof(char) * 15);
		of.write(patronymic.c_str(), sizeof(char) * 15);
		of.write(institute.c_str(), sizeof(char) * 15);
		of.write(department.c_str(), sizeof(char) * 15);
		of.write(group.c_str(), sizeof(char) * 15);
		of.write(recordBookNumber.c_str(), sizeof(char) * 15);
		of.write(gender.c_str(), sizeof(char) * 15);

		int day = birthday.GetDay();
		int month = birthday.GetMonth();
		int year = birthday.GetYear();

		of.write((char*)&day, sizeof(int));
		of.write((char*)&month, sizeof(int));
		of.write((char*)&year, sizeof(int));

		
		of.write((char*)&admissionYear, sizeof(int));

		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 10; ++j) {
				string subjectName = marks[i]->GetSubject(j).GetName();
				int subjectMark = marks[i]->GetSubject(j).GetMark();
				of.write(subjectName.c_str(), sizeof(char) * 80);
				of.write((char*)&subjectMark, sizeof(int));
			}
		}

		of.close();

		// encode
	}
};