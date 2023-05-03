#pragma once

List<string>& GetNewInstituteParams(string currentPath, string object) {
	List<string>* params = GetObjectsFromDir(currentPath);

	params->Append("Create new " + object);
	params->Append("Delete " + object);

	return *params;
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