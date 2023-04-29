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
	*/
	Student kolobok{ "Students/IKB/BISO-01-22/Kobyak_Mikhail_Evgenyevich.bin" };

	cout << kolobok.GetBirthday().GetYear();

	Marks mark{ 1 };
	mark.GetSubjects()[0]->SetMark(10);
	cout << mark.GetSubjects()[0]->GetMark();

}