#pragma once

class MenuModel {
private:
	int pressedKey = 0;
	bool isExit = false;

	void virtual Printer() {}
	void virtual StartFunction() {}

	void virtual OnDownArrow() {}
	void virtual OnUpArrow() {}
	void virtual OnEnter() {}
	void virtual DefaultKeyPressed(int pressedKey) {}

	virtual void ExitFunction() {}

public:
	void Run() {

		StartFunction();

		while (true) {
			system(CLEAR_COMMAND);

			Printer();
			Sleep(SLEEP);

			pressedKey = _getch();

			switch (pressedKey) {

			case ESC:
				isExit = true;
				break;
			case ARROW_DOWN:
				OnDownArrow();
				break;
			case ARROW_UP:
				OnUpArrow();
				break;
			case ENTER:
				OnEnter();
				break;

			default:
				DefaultKeyPressed(pressedKey);
			}

			if (isExit) {
				system(CLEAR_COMMAND);
				ExitFunction();
				break;
			}
		}
	}
};

class ReturnMenuModel {
private:
	int pressedKey = 0;
	bool isExit = false;

	void virtual FirstPrinter() {}
	void virtual InerationPrinter() {}

	void virtual StartFunction() {}

	void virtual OnDownArrow() {}
	void virtual OnUpArrow() {}
	virtual string OnEnter() { return ""; }
	virtual string OnEsc() { return ""; }
	void virtual DefaultKeyPressed(int pressedKey) {}

	virtual void ExitFunction() {}

public:
	string Run() {

		StartFunction();

		FirstPrinter();

		while (true) {
			system(CLEAR_COMMAND);

			InerationPrinter();
			Sleep(SLEEP);

			pressedKey = _getch();

			switch (pressedKey) {

			case ESC:
				return OnEsc();
				break;
			case ARROW_DOWN:
				OnDownArrow();
				break;
			case ARROW_UP:
				OnUpArrow();
				break;
			case ENTER:
				return OnEnter();
				break;

			default:
				DefaultKeyPressed(pressedKey);
			}

			if (isExit) {
				system(CLEAR_COMMAND);
				ExitFunction();
				break;
			}
		}
	}
};