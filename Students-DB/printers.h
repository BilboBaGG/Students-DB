#pragma once

#define LINE_LENGTH 100
#define HEADER "Students-DB"

void AddNewLetter(int key) {
	cout << string(1, key);
}

void ClearLastLetter(string param) {
	COORD cPos;
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	cPos.Y = 3;
	cPos.X = param.length() + 4;
	SetConsoleCursorPosition(hCon, cPos);
	cout << " ";
	SetConsoleCursorPosition(hCon, cPos);
}

void SetPrintable(string param) {
	COORD cPos;
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	cPos.Y = 3;
	cPos.X = param.length() + 5;
	SetConsoleCursorPosition(hCon, cPos);
}

void PrintLine() {
	cout << "|" << string(LINE_LENGTH - 2, '-') << "|" << "\n";
}

void PrintHeader() {
	string header = HEADER;
	header += string(header.length()%2,' ');
	PrintLine();
	cout << "|" << string((LINE_LENGTH - 2 - header.length()) / 2, ' ') << header << string((LINE_LENGTH - 2 - header.length()) / 2, ' ') << "|\n";
	PrintLine();
}

void PrintParam(string param) {
	PrintHeader();
	cout << "|    " << param << string(LINE_LENGTH - param.length() - 6, ' ') << "|" << endl;
	PrintLine();
	
	SetPrintable(param);
}

void PrintParams(List<string>& params) {
	PrintHeader();
	for (int i = 0; i < params.Length(); ++i) {
		string param = params[i];
		param += string(param.length() % 2, ' ');
		cout << "|" << string((LINE_LENGTH - 2 - param.length()) / 2, ' ') << param << string((LINE_LENGTH - 2 - param.length()) / 2, ' ') << "|\n";
	}
	PrintLine();
}
