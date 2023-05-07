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
	virtual void OnEsc() {}

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
				break;
			}
		}
	}
};

class MainChooseMenu : public virtual MenuModel {
protected:
	string object = "";
	List<string>& backupParams = *GetClearList();
	List<string>& params = *GetClearList();

	int identicalButtonsNumber = 0;
	int selectedOption = 0;

	virtual List<string>& ParseParams() { return *GetClearList(); }
	virtual string InputMenu() { return ""; }

	void ResetParams() {
		backupParams = ParseParams();
		params = ParseParams();
		params[0] = GREEN + params[0] + RESET;
		selectedOption = 0;

		identicalButtonsNumber = params.Length() - 2;
	}

	void StartFunction() {
		ResetParams();
	}

	// Move selector down
	void OnDownArrow() {
		params[selectedOption] = backupParams[selectedOption];
		selectedOption += 1;
		selectedOption %= backupParams.Length();
		params[selectedOption] = GREEN + params[selectedOption] + RESET;
	}

	// Move selector up
	void OnUpArrow() {
		params[selectedOption] = backupParams[selectedOption];
		if (selectedOption == 0) {
			selectedOption = backupParams.Length() - 1;
		}
		else {
			selectedOption -= 1;
			selectedOption %= backupParams.Length();
		}
		params[selectedOption] = GREEN + params[selectedOption] + RESET;
	}

	virtual void OnEnter() = 0;

	void ExitFunction() {
		delete& backupParams;
		delete& params;
	}
};