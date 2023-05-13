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

	/*Student kolobok = Read("./Students/IKB/BISO-01-22/Kobyak_Mikhail_Evgenyevich.bin");

	for (int j = 0; j < 1; ++j) {
		cout << j << " semester\n";
		for (int i = 0; i < SUBJECTS_NUMBER; ++i) {
			cout << kolobok.GetSubjcetName(j, i) << " : " << kolobok.GetMark(j, i) << endl;
		}
		cout << "\n";
	}

	kolobok.DeleteSubject(0, 0);


	for (int j = 0; j < 1; ++j) {
		cout << j << " semester\n";
		for (int i = 0; i < SUBJECTS_NUMBER; ++i) {
			cout << kolobok.GetSubjcetName(j, i) << " : " << kolobok.GetMark(j, i) << endl;
		}
		cout << "\n";
	}
	cout << kolobok.GetMarksNumberInSemester(0);*/
}