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
	cPos.X = static_cast<SHORT>(param.length()) + 5;
	SetConsoleCursorPosition(hCon, cPos);
}

void PrintClearLine() {
	cout << "|" << string(LINE_LENGTH - 2, ' ') << "|" << "\n";
}

void PrintLine() {
	cout << "|" << string(LINE_LENGTH - 2, '-') << "|" << "\n";
}

void PrintInCenter(string param) {
	param += string(param.length() % 2, ' ');
	cout << "|" << string((LINE_LENGTH - 2 - param.length()) / 2, ' ') << param << string((LINE_LENGTH - 2 - param.length()) / 2, ' ') << "|\n";
}

void PrintHeader() {

	PrintLine();
	
	PrintInCenter(HEADER);

	PrintLine();
}

void PrintHeader(string secondHeader) {

	PrintLine();

	PrintInCenter(HEADER);

	PrintLine();

	PrintInCenter(secondHeader);

	PrintLine();
}

void PrintOneParam(string param) {
	PrintHeader();
	cout << "|    " << param << string(LINE_LENGTH - param.length() - 6, ' ') << "|" << endl;
	PrintLine();
	
	SetPrintable(param);
}

void PrintParams(List<string>& params, List<string>& backupParams, string header, int identicalButtonsNumber) {
	PrintHeader(header);
	for (int i = 0; i < params.Length(); ++i) {
		if (i == identicalButtonsNumber) PrintClearLine();
		string param = params[i];
		string backupParam = backupParams[i];

		if (backupParam.length() % 2 == 1) {
			param += " ";
			backupParam += " ";
		}

		cout << "|" << string((LINE_LENGTH - 2 - backupParam.length()) / 2, ' ') << param << string((LINE_LENGTH - 2 - backupParam.length()) / 2, ' ') << "|\n";
	}
	PrintLine();
}
