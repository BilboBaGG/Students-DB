#pragma once

List<string>* GetNewObjectParamsWithExtraParams(string currentPath, string object) {
	List<string>* params = GetObjectsFromDir(currentPath);

	params->Append("Create new " + object);
	params->Append("Delete " + object);

	return params;
}

List<string>* GetNewObjectParams() {
    List<string>* params = GetObjectsFromDir(currentPath);

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

string GetLastParam() {
    stringstream ss(currentPath);
    string temp, newCurrentPath = "", object;

    int countSlashes = 0;
    for (int j = 0; j < currentPath.length(); ++j) {
        if (currentPath[j] == '\\') {
            countSlashes += 1;
        }
    }

    for (int j = 0; j < countSlashes; ++j) {
        getline(ss, temp, '\\');
    }
    getline(ss, newCurrentPath);

    return newCurrentPath;
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

List<string>& GetClearList() {
    List<string>* temp = new List<string>();
    return *temp;
}