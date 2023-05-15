#pragma once

List<string>* GetNewDirParamsWithExtraParams(string currentPath, string object) {
	List<string>* params = GetObjectsFromDir(currentPath);

	params->Append("Create new " + object);
	params->Append("Delete " + object);

	return params;
}

List<string>* GetNewFileParsedParamsWithExtraParams(string currentPath, string object) {
    List<string>* params = GetParsedStudentsFromDir(currentPath);

    params->Append("Create new " + object);
    params->Append("Delete " + object);

    return params;
}

List<string>* GetNewObjectParams() {
    List<string>* params = GetObjectsFromDir(currentPath);

    return params;
}

List<string>* GetStudentsParams(string currentPath, Student& student) {
    List<string>* params = new List<string>;
    params->Append("Surname: " + student.GetSurname());
    params->Append("Name: " + student.GetName());
    params->Append("Patronymic: " + student.GetPatronymic());
    params->Append("Institute: " + student.GetInstitute());
    params->Append("Departament: " + student.GetDepartment());
    params->Append("Group: " + student.GetGroup());
    params->Append("RecordBookNumber: " + student.GetRecordBookNumber());
    params->Append("Gender: " + student.GetGender());
    params->Append("Admission year: " + student.GetStringAdmissionYear());
    params->Append("Birthday: " + student.GetBirthday().GetDateInString());
    params->Append("Marks");

    return params;
}


void RestoreCurrentPath() {
    stringstream ss(currentPath);
    string temp,newCurrentPath = "", object;

    int countSlashes = 0;
    for (int j = 0; j < currentPath.length(); ++j) {
        if (currentPath[j] == '\\') {
            countSlashes += 1;
        }
    }

    for (int j = 0; j < countSlashes; ++j) {
        getline(ss, temp, '\\');
        newCurrentPath += temp;
        if (j != countSlashes - 1) newCurrentPath += "\\";
    }

    currentPath = newCurrentPath;
}

string GetInstitute() {
    stringstream ss(currentPath);
    string temp, instituteString = "", object;

    for (int j = 0; j < 2; ++j) {
        getline(ss, temp, '\\');
    }
    getline(ss, instituteString, '\\');

    return instituteString;
}

string GetGroup() {
    stringstream ss(currentPath);
    string temp, groupString = "", object;

    for (int j = 0; j < 3; ++j) {
        getline(ss, temp, '\\');
    }
    getline(ss, groupString,'\\');

    return groupString;
}

string GetFilenameFromParsedStudent(string parsedStudent) {
    stringstream ss(parsedStudent);
    string filename, tempString;
    getline(ss, tempString, ' ');
    filename += tempString + "_";
    getline(ss, tempString, ' ');
    filename += tempString + "_";
    getline(ss, tempString);
    filename += tempString + ".bin"; // .enc


    return filename;
}

int GetNumberOfTypedStudents(string path, int mark) {
    List<string>* allStudents = GetParsedStudentsFromDir(path);
    int counter = 0;

    for (int i = 0; i < allStudents->Length(); ++i) {

        Student student = Read(path + "\\" + GetFilenameFromParsedStudent(allStudents->Get(i)));
        if (student.GetMinMark() == mark) {

            counter += 1;
        }
    }
    return counter;
}

int CountValidStudents(int mark, int minYear, int maxYear) {
    List<string>* allStudents = GetParsedStudentsFromDir(currentPath);
    int counter = 0;

    for (int i = 0; i < allStudents->Length(); ++i) {

        Student student = Read(currentPath + "\\" + GetFilenameFromParsedStudent(allStudents->Get(i)));
        if (student.GetMinMark() == mark && student.GetBirthday().GetYear() >= minYear && student.GetBirthday().GetYear() <= maxYear) {

            counter += 1;
        }
    }
    return counter;
}


string GetSubjectName(string mark) {
    stringstream ss(mark);
    string subjectName, tempString;
    getline(ss, tempString, ':');
    subjectName += tempString;

    return subjectName;
}

bool IsAdditionMenu(int selectedOption, int identicalButtonsNumber) {
    return selectedOption == identicalButtonsNumber;
}
bool IsIdenticalParam(int selectedOption, int identicalButtonsNumber) {
    return selectedOption < identicalButtonsNumber;
}

bool IsObjectExists() {
    return true;
}

List<string>* GetClearList() {
    List<string>* temp = new List<string>();
    return temp;
}

string GetCurrentPath(Student& student) {
    string path = ".\\Students\\";
    path += student.GetInstitute() + "\\";

    path += student.GetGroup() + "\\";

    path += student.GetSurname() + "_" + student.GetName() + "_" + student.GetPatronymic() + ".bin"; // .enc
    return path;
}