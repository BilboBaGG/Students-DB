#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>

#include "list.h"
#include "settings.h"
#include "student.h"
#include "marks.h"
#include "file_functions.h"
#include "menu.h"

using namespace std;

int main() {

	MainMenu::Run();

	Student misha;
	misha.SetName("Mikhail");
	misha.SetSurname("Kobyak");
	misha.SetPatronymic("Evgenyevich");
	misha.SetGroup("BISO-01-22");
	misha.SetInstitute("IKB");

	Date date = { 10, 1110, 22 };

	misha.SetBirthday(date);
	misha.SetAdmissionYear(1000);
	
	misha.GetSemesterMarks(1).AddSubjectMark("Math", 5);
	misha.GetSemesterMarks(8).AddSubjectMark("Math", 5);
	misha.GetSemesterMarks(8).AddSubjectMark("Russian", 4);
	misha.GetSemesterMarks(6).AddSubjectMark("Programming", 3);

	Write(&misha);

	//Student kolobok = Read("filename.bin");
	//cout << kolobok.GetName();


	//for (int j = 0; j < 9; ++j) {
		//for (int i = 0; i < 10; ++i) {
			//cout << kolobok.GetSemesterMarks(j + 1).GetSubject(i).GetName() << ":" << kolobok.GetSemesterMarks(j + 1).GetSubject(i).GetMark() << endl;
		//}
		//cout << "\n";
	//}
}