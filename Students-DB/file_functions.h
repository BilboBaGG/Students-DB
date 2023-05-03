#pragma once

#include <fstream>

void Write(Student* studentPointer) {

	ofstream of;

	of.open("./filename.bin", ios::binary | ios::out);

	of.write(studentPointer->StringParseMarks().c_str(),sizeof(char) * (studentPointer->StringParseMarks().length()+2));
	
	of.close();

	// encode
}

//Student& Read(string filename) {
	//ifstream ifs;
	//cout << "asd";
	//ifs.open(filename.c_str(), ios::binary | ios::in | ios::trunc);
	//Student temp;
	//ifs.read((char*)&temp,sizeof(Student));
	//cout << ">>>>" << temp.GetName() << "\n";
	//ifs.close();
	//return temp;
//}

	//string path = "./Students/" + pointer->GetInstitute() + "/" + pointer->GetGroup() + "/" + pointer->GetSurname() + "_" + pointer->GetName() + "_" + pointer->GetPatronymic() + ".bin";
