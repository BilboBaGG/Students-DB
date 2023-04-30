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

	/*
	Student misha;
	misha.SetName("Mikhail");
	misha.SetSurname("Kobyak");
	misha.SetPatronymic("Evgenyevich");
	misha.SetGroup("BISO-01-22");
	misha.SetInstitute("IKB");

	Date date = { 10, 1110, 22 };

	misha.SetBirthday(date);
	misha.SetAdmissionYear(1000);

	misha.Write();
	
	Student kolobok{ "Students/IKB/BISO-01-22/Kobyak_Mikhail_Evgenyevich.bin" };

	cout << kolobok.GetBirthday().GetYear() << endl;
	*/
	Marks mark{ 1 };

	mark.AddSubjectMark("Math", 5);


	for (int i = 0; i < 10; ++i) {
		cout << mark.GetSubjects()[i]->GetName() << ":" << mark.GetSubjects()[i]->GetMark() << endl;
	}

}