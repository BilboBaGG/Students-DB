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
		subjectsNumber = 0;
	}
	~Marks() {
		for (int i = 0; i < subjectsNumber; ++i) {
			delete subjects[i];
		}
	}
	
	int GetSemesterNumber() {
		return semesterNumber;
	}

	int GetSubjectsNumber() {
		return subjectsNumber;
	}

	Subject& GetSubject(int index) {
		return *subjects[index];
	}

	string GetParsedMarks() {
		string out = "";
		for (int i = 0; i < subjectsNumber; ++i) {
			out += subjects[i]->GetName() + ":" + to_string(subjects[i]->GetMark());
			if (i != subjectsNumber - 1) {
				out += ":";
			}
		}
		return out;
	}

	void AddSubjectMark(string name, int mark) {
		subjects.Append(new Subject(name, mark));
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