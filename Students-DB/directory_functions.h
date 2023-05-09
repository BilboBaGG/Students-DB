#pragma once

// https://stackoverflow.com/questions/59564671/c-an-vs-error-experimental-filesystem-header-providing-stdexperimentalf 
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

        getline(ss, object);
        parsedFiles->Append(object);
    }

    delete files;
    return parsedFiles;
}


List<string>* GetParsedStudentsFromDir(string path) { 
    List<string>* files = GetObjectsFromDir(path);
    List<string>* students = new List<string>;

    for (int i = 0; i < files->Length(); ++i) {
        stringstream ss(files->Get(i));
        string studentString, studentParsedString = "";

        getline(ss, studentString, '_');
        studentParsedString += studentString + " ";

        getline(ss, studentString, '_');
        studentParsedString += studentString + " ";

        getline(ss, studentString, '.');
        studentParsedString += studentString;


        students->Append(studentParsedString);
    }
    delete files;

    return students;
}

bool IsStudentExists(string student, string path) {
    return (GetParsedStudentsFromDir(path)->Find(student) != -1);
}

bool IsDirectoryExists(string dir, string path) {
    return (GetObjectsFromDir(path)->Find(dir) != -1);
}

//List<string>* GetStudentsFromDir(string path) { 
//    List<string>* files = GetObjectsFromDir(path);
//    List<string>* students = new List<string>;
//
//    for (int i = 0; i < files->Length(); ++i) {
//        stringstream ss(files->Get(i));
//        string studentString;
//        getline(ss, studentString, '.');
//        students->Append(studentString);
//    }
//    delete files;
//
//    return students;
//}

List<string>* GetParsedStudentsFromDirWithExtraButtons(string path, string object) {
    List<string>* studentParams = GetParsedStudentsFromDir(path);
    studentParams->Append("Create new " + object);
    studentParams->Append("Delete " + object);
    return studentParams;
}


void MakeDirectory(string dirName) {
    string mkdirCommand = "mkdir \"" + dirName+"\"";
    system(mkdirCommand.c_str());
}

void DeleteDirectory(string dirName) {
    string rmdirCommand = "rmdir /s /q \"" + dirName + "\"";
    system(rmdirCommand.c_str());
}

void DeleteStudentFile(string fileName) {
    string rmFileCommand = "del \"" + fileName +"\"";
    system(rmFileCommand.c_str());
}
