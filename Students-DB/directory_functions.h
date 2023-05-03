#pragma once

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

List<string>& GetDirList(string path) { // ls function eqivalent
    List<string>* files = new List<string>;
    for (const auto& entry : fs::directory_iterator(path)) {
        files->Append(entry.path().string());
    }
    return *files;
}

List<string>* GetObjectsFromDir(string path) {

    List<string>* files = new List<string>;

    for (const auto& entry : fs::directory_iterator(path)) {
        files->Append(entry.path().string());
    }

    List<string>* parsedFiles = new List<string>;

    for (int i = 0; i < files->Length(); ++i) {
        stringstream ss(files->Get(i));
        string temp, object;

        int countSlashes = 0;
        for (int j = 0; j < files->Get(i).length(); ++j) {
            if (files->Get(i)[j] == '\\') {
                countSlashes += 1;
            }
        }

        for (int j = 0; j < countSlashes; ++j) {
            getline(ss, temp, '\\');
        }

        getline(ss, object); // Institute 
        parsedFiles->Append(object);
    }

    delete files;
    return parsedFiles;
}

void MakeDirectory(string dirName) {
    string mkdirCommand = "mkdir " + dirName;
    system(mkdirCommand.c_str());
}

void DeleteDirectory(string dirName) {
    string rmdirCommand = "rmdir " + dirName;
    system(rmdirCommand.c_str());
}

