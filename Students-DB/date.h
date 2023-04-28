class Date {
private:
	int day, month, year;
public:
	Date() {
		day = 1;
		month = 1;
		year = 1970;
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
};