#pragma once

#include <fstream>

void Write(Student& student) {
	string path = "./Students/" + student.GetInstitute() + "/" + student.GetGroup() + "/" + student.GetSurname() + "_" + student.GetName() + "_" + student.GetPatronymic() + ".bin";

	ofstream of;

	of.open(path, ios::binary | ios::out);
	of.write((char*)&student, sizeof(Student));
	of.close();

	// encode
}

Student& Read(string filename) {
	ifstream ifs;
	ifs.open(filename.c_str(), ios::binary | ios::in );
	Student* temp = new Student();
	ifs.read((char*)temp,sizeof(Student));
	ifs.close();

	return *temp;
}

