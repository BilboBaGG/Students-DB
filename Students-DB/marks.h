#pragma once

class Subject {
public:
	Subject(int mark_, string name_) {
		mark = mark_;
		name = name_;
	}
	~Subject() {

	}

	int GetMark() {
		return mark;
	}
	void SetMark(int mark_) {
		mark = mark_;
	}

	string GetName() {
		return name;
	}
	void SetName(string name_) {
		name = name_;
	}

private:
	int mark;
	string name;
};

class Marks {
private:
	int semesterNumber, subjectsNumber;
	List<Subject*> subjects;
public:
	Marks(int semesterNumber_) {
		semesterNumber = semesterNumber_;
		for (int i = 0; i < 10; ++i) {
			Subject* temp = new Subject(0, ""); 
			subjects.Append(temp);
		}
		subjectsNumber = 0;
	}
	~Marks() {
		for (int i = 0; i < 10; ++i) {
			delete subjects[i];
		}
	}

	int GetSubjectsNumber() {
		return subjectsNumber;
	}

	List<Subject*>& GetSubjects() {
		return subjects;
	}
};