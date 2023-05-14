#pragma once

class SelectDirParam : public virtual SelectParamMenuReturnModel {
public:
	SelectDirParam(string object_, string header_) {
		object = object_;
		header = header_;
	}
private:
	List<string>& ParseParams() override {
		return *GetNewObjectParams();
	}
};

class SelectStudentParam : public virtual SelectParamMenuReturnModel {
public:
	SelectStudentParam(string object_, string header_) {
		object = object_;
		header = header_;
	}
private:
	List<string>& ParseParams() override {
		return *GetParsedStudentsFromDir(currentPath);
	}
};