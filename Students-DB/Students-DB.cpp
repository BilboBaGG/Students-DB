#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>

using namespace std;

#include "main_selection_menus.h"

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("chcp 1251");

	MainDB::Run();
}