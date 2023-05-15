#pragma once

class KeyboardInputMenu {
protected:
	virtual bool IsValid(int key) = 0;
public:
	string Run(string message, string iString, int maxLength) {
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
				if (inputString.length() < maxLength && IsValid(key)) {
					inputString += string(1, key);
					AddNewLetter(key);
					break;
				}
			}
		}
	}
};


class BaseInputMenu : public virtual KeyboardInputMenu {
private:
	bool IsValid(int key) override{
		return (key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z' || key == '-' || key <= '9' && key >= '0' || key == ' ');
	}
};


class InputLetterOnlyMenu : public virtual KeyboardInputMenu {
private:
	bool IsValid(int key) override {
		return (key >= 'a' && key <= 'z' || key >= 'A' && key <= 'Z' || key == ' ');
	}
};

class GenderInputMenu : public virtual KeyboardInputMenu {
private:
	bool IsValid(int key) override {
		return (key == 'M' || key == 'W' || key == 'w' || key == 'm');
	}
};


class InputNumberOnlyMenu : public virtual KeyboardInputMenu {
private:
	bool IsValid(int key) override {
		return (key <= '9' && key >= '0');
	}
};

class InputMarkMenu : public virtual KeyboardInputMenu {
private:
	bool IsValid(int key) override {
		return (key >= '2' && key <= '5');
	}
};

class InputPasswdMenu {
protected:
	virtual bool IsValid(int key) {
		return (key >= 'a' && key <= 'z' || key == '_' || key >= 'A' && key <= 'Z' || key == '-' || key <= '9' && key >= '0' || key == ' ');
	}
public:
	string Run(string message, string iString, int maxLength) {
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
				if (inputString.length() < maxLength && IsValid(key)) {
					inputString += string(1, key);
					AddNewLetter('*');
					break;
				}
			}
		}
	}
};