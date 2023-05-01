#include <iostream>
#include <stdlib.h>
#include <string>

#include "menu.h"
#include "list.h"
#include "settings.h"
#include "student.h"

#include "marks.h"

using namespace std;

int main() {
	system(CLEAR_COMMAND);


	Student misha;
	misha.SetName("Mikhail");
	misha.SetSurname("Kobyak");
	misha.SetPatronymic("Evgenyevich");
	misha.SetGroup("BISO-01-22");
	misha.SetInstitute("IKB");

	Date date = { 10, 1110, 22 };

	misha.SetBirthday(date);
	misha.SetAdmissionYear(1000);
	
	misha.GetSemesterMarks(1).AddSubjectMark("asd", 123);
	misha.GetSemesterMarks(8).AddSubjectMark("jjj", 5);

	misha.GetSemesterMarks(6).AddSubjectMark("asjdfjasfj", 123);



	/*for (int j = 0; j < 9; ++j) {
		for (int i = 0; i < 10; ++i) {
			cout << misha.GetSemesterMarks(j + 1).GetSubject(i).GetName() << ":" << misha.GetSemesterMarks(j + 1).GetSubject(i).GetMark() << endl;
		}
		cout << "\n";
	}*/

	misha.Write();

	Student kolobok{ "Students/IKB/BISO-01-22/Kobyak_Mikhail_Evgenyevich.bin" };

	for (int j = 0; j < 9; ++j) {
		for (int i = 0; i < 10; ++i) {
			cout << kolobok.GetSemesterMarks(j + 1).GetSubject(i).GetName() << ":" << kolobok.GetSemesterMarks(j + 1).GetSubject(i).GetMark() << endl;
		}
		cout << "\n";
	}

}