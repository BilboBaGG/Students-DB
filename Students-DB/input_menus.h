#pragma once

class InputMenu {
public:
	static string Run(string message, string iString, int maxLength) {
		string inputString = iString;
		int key = 0;
		system(CLEAR_COMMAND);
		PrintOneParam(message + inputString);
		while (true) {
			key = _getch();
			switch (key)
			{
			case (ESC):
				inputString = ESCAPE_STRING;
				return inputString;
			case (ENTER):
				return inputString;
				break;
			case (BACKSPACE):
				if (inputString.length() > 0) {
					ClearLastLetter(message + inputString);
					inputString = inputString.substr(0, inputString.length() - 1);
				}
				break;
			default:
				if (inputString.length() < maxLength && (key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z' || key == '-' || key <= '9' && key >= '0' || key == ' ')) {
					inputString += string(1, key);
					AddNewLetter(key);
					break;
				}
			}
		}
	}
};

class InputLetterOnlyMenu {
public:
	static string Run(string message, string iString, int maxLength) {
		string inputString = iString;
		int key = 0;
		system(CLEAR_COMMAND);
		PrintOneParam(message + inputString);
		while (true) {
			key = _getch();
			switch (key)
			{
			case (ESC):
				inputString = ESCAPE_STRING;
				return inputString;
			case (ENTER):
				return inputString;
				break;
			case (BACKSPACE):
				if (inputString.length() > 0) {
					ClearLastLetter(message + inputString);
					inputString = inputString.substr(0, inputString.length() - 1);
				}
				break;
			default:
				if (inputString.length() < maxLength && (key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z' || key == ' ')) {
					inputString += string(1, key);
					AddNewLetter(key);
					break;
				}
			}
		}
	}
};

class InputNumberOnlyMenu {
public:
	static string Run(string message, string iString, int maxLength) {
		string inputString = iString;
		int key = 0;
		system(CLEAR_COMMAND);
		PrintOneParam(message + inputString);
		while (true) {
			key = _getch();
			switch (key)
			{
			case (ESC):
				inputString = ESCAPE_STRING;
				return inputString;
			case (ENTER):
				return inputString;
				break;
			case (BACKSPACE):
				if (inputString.length() > 0) {
					ClearLastLetter(message + inputString);
					inputString = inputString.substr(0, inputString.length() - 1);
				}
				break;
			default:
				if (inputString.length() < maxLength && (key <= '9' && key >= '0')) {
					inputString += string(1, key);
					AddNewLetter(key);
					break;
				}
			}
		}
	}
};

class InputMarkMenu {
public:
	static string Run(string message, string iString, int maxLength) {
		string inputString = iString;
		int key = 0;
		system(CLEAR_COMMAND);
		PrintOneParam(message + inputString);
		while (true) {
			key = _getch();
			switch (key)
			{
			case (ESC):
				inputString = ESCAPE_STRING;
				return inputString;
			case (ENTER):
				return inputString;
				break;
			case (BACKSPACE):
				if (inputString.length() > 0) {
					ClearLastLetter(message + inputString);
					inputString = inputString.substr(0, inputString.length() - 1);
				}
				break;
			default:
				if (inputString.length() < maxLength && (key >= '2' && key <= '5')) {
					inputString += string(1, key);
					AddNewLetter(key);
					break;
				}
			}
		}
	}
};