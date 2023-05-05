#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;


#include "list.h"
#include "settings.h"
#include "student.h"
#include "file_functions.h"
#include "menu.h"

int main() {
	InstituteSelectionMenu startMenu;
	startMenu.Run();
	

	/*Student misha;
	misha.SetName("Mikhail");
	misha.SetSurname("Kobyak");
	misha.SetPatronymic("Evgenyevich");
	misha.SetGroup("BISO-01-22");
	misha.SetInstitute("IKB");
	misha.SetRecordBookNumber(string(8, 'h'));
	Date date = { 10, 1110, 22 };

	misha.SetBirthday(date);
	misha.SetAdmissionYear(1000);

	misha.AddMark(0,"Math",5);
	misha.AddMark(0,"Russian",5);
	misha.AddMark(4, "Latin", 2);

	Write(misha);

	Student kolobok = Read("./Students/IKB/BISO-01-22/Kobyak_Mikhail_Evgenyevich.bin");

	kolobok.DeleteSubject(0, "Math");

	kolobok.AddMark(0, "Math", 5);

	for (int j = 0; j < SEMESTERS_NUMBER; ++j) {
		cout << j << " semester\n";
		for (int i = 0; i < SUBJECTS_NUMBER; ++i) {
			cout << kolobok.GetSubjcetName(j, i) << " : " << kolobok.GetMark(j, i) << endl;
		}
		cout << "\n";
	}
	cout << kolobok.GetMarksNumberInSemester(0);*/
}