#pragma once

class Subject {
private:
	int mark;
	string name;
public:
	Subject(string name_, int mark_) {
		mark = mark_;
		name = name_;
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
};

class Marks {
private:
	int semesterNumber, subjectsNumber;
	List<Subject*> subjects;
public:
	Marks(int semesterNumber_) {
		semesterNumber = semesterNumber_;
		for (int i = 0; i < 10; ++i) {
			Subject* temp = new Subject("", 0); 
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

	/*
	List<Subject*>& GetSubjects() {
		return subjects;
	}
	*/

	Subject& GetSubject(int index) {
		return *subjects[index];
	}

	void AddSubjectMark(string name, int mark) {
		subjects[subjectsNumber]->SetMark(mark);
		subjects[subjectsNumber]->SetName(name);
		subjectsNumber += 1;
		// Sort
	}

	void SetSubjectMark(string name, int mark) {
		for (int i = 0; i < subjectsNumber; ++i) {
			if (name == subjects[i]->GetName()) {
				subjects[i]->SetMark(mark);
			}
		}
	}
	
	void DeleteMark(string name) {
		for (int i = 0; i < subjectsNumber; ++i) {
			if (subjects[i]->GetName() == name) {
				delete subjects[i];
				subjects.Delete(i);
				subjects.Append(new Subject("", 0));
				subjectsNumber -= 1;
				break;
			}
		}
	}

};