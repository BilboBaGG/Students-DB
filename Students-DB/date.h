class Date {
private:
	int day, month, year;
public:
	Date() {
		day = 1;
		month = 1;
		year = 0;
	}
	Date(int day_, int month_, int year_) {
		day = day_;
		month = month_;
		year = year_;
	}

	int GetDay() {
		return day;
	}
	void SetDay(int day_) {
		day = day_;
	}

	int GetMonth() {
		return month;
	}
	void SetMonth(int month_) {
		month = month_;
	}

	int GetYear() {
		return year;
	}
	void SetYear(int year_) {
		year = year_;
	}
	string GetDateInString() {
		if (year == 0) {
			return "";
		} else {
			string day_ = (day / 10 == 0) ? ("0") : ("");
			string month_ = (month / 10 == 0) ? ("0") : ("");
			return day_ + to_string(day) + "." + month_ + to_string(month) + "." + to_string(year);
		}
	}
};