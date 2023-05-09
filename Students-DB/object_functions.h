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
    params->Append("Admission year: " + to_string(student.GetAdmissionYear()));
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