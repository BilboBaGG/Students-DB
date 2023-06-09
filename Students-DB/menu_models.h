#pragma once

class InfoMenu {
public:
	static void Run(string message) {
		system(CLEAR_COMMAND);
		PrintOneParam(message);
		int key = 0;
		while (true) {
			key = _getch();
			if (key == ESC || key == ENTER) {
				break;
			}
		}
	}
};


class MenuModel {
protected:
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
protected:
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

	virtual void ResetParams() {
		//params.Clear();
		//backupParams.Clear();

		backupParams = ParseParams();
		params = ParseParams();

		params[0] = GREEN + params[0] + RESET;
		selectedOption = 0;

		identicalButtonsNumber = params.Length() - 2;

	}

	void StartFunction() override{
		ResetParams();
	}

	// Move selector down
	void OnDownArrow()override {
		params[selectedOption] = backupParams[selectedOption];
		selectedOption += 1;
		selectedOption %= backupParams.Length();
		params[selectedOption] = GREEN + params[selectedOption] + RESET;
	}

	// Move selector up
	void OnUpArrow() override {
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

	virtual void OnEnter()override {}

	void ExitFunction() override {
		delete& backupParams;
		delete& params;
	}
};

class SelectParamMenuReturnModel : public virtual ReturnMenuModel {
protected:
	string object = "";
	string header = "";
	List<string>& backupParams = *GetClearList();
	List<string>& params = *GetClearList();

	int selectedOption = 0;
private:
	virtual List<string>& ParseParams() = 0;

	void ResetParams() {
		backupParams = ParseParams();
		params = ParseParams();
		params[0] = GREEN + params[0] + RESET;
		selectedOption = 0;
	}

	virtual void StartFunction() override {
		ResetParams();
	}

	virtual void InerationPrinter() override {
		PrintParams(params, backupParams, header);
	}

	string OnEsc() override{
		delete& backupParams;
		delete& params;
		return ESCAPE_STRING;
	}

	void OnDownArrow() override {
		params[selectedOption] = backupParams[selectedOption];
		selectedOption += 1;
		selectedOption %= backupParams.Length();
		params[selectedOption] = GREEN + params[selectedOption] + RESET;
	}

	void OnUpArrow() override {
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

	string OnEnter() override {
		return backupParams[selectedOption];
	}
};

class DefaultSelectionMenuWithButtons : public virtual MainChooseMenu {
protected:
	virtual List<string>& ParseParams() = 0;
	virtual void NextMenuRun(string selectedParam) = 0;
	virtual void OnCreate() = 0;
	virtual void OnDelete() = 0;

	void OnEnter() override {
		if (IsIdenticalParam(selectedOption, identicalButtonsNumber)) {
			NextMenuRun(backupParams[selectedOption]);
		}
		else {
			if (IsAdditionMenu(selectedOption, identicalButtonsNumber)) {
				OnCreate();
			}
			else {
				OnDelete();
			}

		}
	}
};
