#include <iostream>
using namespace std;

template <typename Template>
class Element {
private:
	Element<Template>* nextPointer;
	Template element;

public:
	Element() {
		element = NULL;
		nextPointer = NULL;
	}
	Element(Template el) {
		element = el;
		nextPointer = NULL;
	}
	Element(Template el, Element<Template>* pointer) {
		element = el;
		nextPointer = pointer;
	}
	void SetElement(Template el) {
		element = el;
	}
	Template& GetElement() {
		return element;
	}
	void SetPointer(Element<Template>* pointer) {
		nextPointer = pointer;
	}
	Element<Template>* GetPointer() {
		return nextPointer;

	}
};

template <typename Template>
class List {
private:
	int length;
	Element<Template>* firstPointer;
public:

	List() {
		length = 0;
		firstPointer = NULL;
	}

	~List() {
		if (length != 0) {
			Element<Template>* tempElementPointer = firstPointer;
			Element<Template>* elementPointer = firstPointer;
			for (int i = 0; i < length; ++i) {
				elementPointer = tempElementPointer;
				tempElementPointer = tempElementPointer->GetPointer();
				delete elementPointer;
			}
		}
	}

	void Append(Template element) {
		length += 1;
		if (firstPointer) {
			Element<Template>* tempElementPointer = firstPointer;
			Element<Template>* elementPointer = firstPointer;

			while (tempElementPointer != NULL) {
				elementPointer = tempElementPointer;
				tempElementPointer = tempElementPointer->GetPointer();
			}

			Element<Template>* newElementPointer = new Element<Template>(element);

			elementPointer->SetPointer(newElementPointer);
		}
		else {
			firstPointer = new Element<Template>(element);
		}
	}

	void Insert(int index, Template element) {
		if (index < 0) index = length + index;
		int counter = 0;
		Element<Template>* tempElementPointer = firstPointer;

		if (index == 0) {
			firstPointer = new Element<Template>(element, tempElementPointer);
			length += 1;
		}
		else {
			Element<Template>* elementPointer = firstPointer;
			while (counter != index and tempElementPointer != NULL) {
				counter += 1;
				elementPointer = tempElementPointer;
				tempElementPointer = tempElementPointer->GetPointer();
			}

			elementPointer->SetPointer(new Element<Template>(element, tempElementPointer));
			length += 1;

		}
	}

	void Delete() {
		if (length == 0) throw "Clean List";

		Element<Template>* tempElementPointer = firstPointer;
		Element<Template>* elementPointer = firstPointer;

		while (tempElementPointer->GetPointer() != NULL) {
			elementPointer = tempElementPointer;
			tempElementPointer = tempElementPointer->GetPointer();
		}

		delete tempElementPointer;

		elementPointer->SetPointer(NULL);
		length -= 1;
	}

	void Delete(int index) {
		if (index < 0) index = length + index;
		if (length == 0) throw "Clean List";
		if (index >= length) throw "invalid Index";

		if (index == 0) {
			Element<Template>* tempElementPointer = firstPointer->GetPointer();
			delete firstPointer;
			firstPointer = tempElementPointer;
			length -= 1;
		}
		else {
			Element<Template>* tempElementPointer = firstPointer;
			Element<Template>* elementPointer = firstPointer;
			int counter = 0;

			while (counter != index) {
				elementPointer = tempElementPointer;
				tempElementPointer = tempElementPointer->GetPointer();
				counter += 1;
			}
			elementPointer->SetPointer(tempElementPointer->GetPointer());
			delete tempElementPointer;
			length -= 1;
		}
	}

	int Length() {
		return length;
	}

	Template& operator[](int index) {
		if (index < 0) index = length + index;
		if (index >= length) {
			throw "Invalid Index";
		}
		else {
			int counter = 0;
			Element<Template>* tempElementPointer = firstPointer;
			while (counter != index) {
				tempElementPointer = tempElementPointer->GetPointer();
				counter += 1;
			}
			return tempElementPointer->GetElement();
		}
	}

	Template Get(int index) {
		if (index < 0) index = length + index;
		if (index >= length) {
			throw "Invalid Index";
		}
		else {
			int counter = 0;
			Element<Template>* tempElementPointer = firstPointer;
			while (counter != index) {
				tempElementPointer = tempElementPointer->GetPointer();
				counter += 1;
			}
			return tempElementPointer->GetElement();
		}
	}

	int Find(Template element) {
		Element<Template>* tempElementPointer = firstPointer;
		Element<Template>* elementPointer = firstPointer;
		for (int i = 0; i < length; ++i) {
			elementPointer = tempElementPointer;
			if (elementPointer->GetElement() == element) {
				return i;
			}
			tempElementPointer = tempElementPointer->GetPointer();
		}
		return -1;
	}

	void Print() {
		Element<Template>* tempElementPointer = firstPointer;

		cout << "[";
		while (true) {
			cout << tempElementPointer->GetElement();
			tempElementPointer = tempElementPointer->GetPointer();
			if (tempElementPointer == NULL) {
				break;
			}
			else {
				cout << ", ";
			}
		}
		cout << "]\n";
	}
};


