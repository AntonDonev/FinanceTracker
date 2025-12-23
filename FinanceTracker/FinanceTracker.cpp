#include <iostream>
const int MONTHS = 12;
const int DEFAULTINACTIVEVALUE = -1;
const int DEFAULTEMPTYVALUE = 0;
const int ACCOUNTEXPENSESINDEX = 1;
const int ACCOUNTINCOMEINDEX = 0;
const int NORMALIZEINPUTMONTHINDEX = 1;
const int ACCOUNTROWS = 2;
const int CONVERTTOPERCENTAGES = 100;
const int SORTINGTYPESCOUNT = 3;
const int SORTINGBYBALANCE = 2;
const int SORTINGBYINCOME = 0;
const int SORTINGBYEXPENSES = 1;
const int CHARTSTEPS = 5;
const int COMMANDSCOUNT = 8;
const int SETUPINDEX = 0;
const int ADDINDEX = 1;
const int REPORTINDEX = 2;
const int SEARCHINDEX = 3;
const int SORTINDEX = 4;
const int FORECASTINDEX = 5;
const int CHARTINDEX = 6;
const int EXITINDEX = 7;
const char* MONTHSNAMES[] = {
		"JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE",
		"JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"
};
const char* COMMANDS[] = {
		"SETUP", "ADD", "REPORT", "SEARCH", "SORT", "FORECAST",
		"CHART", "EXIT"
};
const char* TYPES[] = {
		"INCOME", "EXPENSES", "BALANCE"
};

void setupAccount(double profile[][MONTHS], int inputMonths) {

	if (inputMonths <= 0) {
		std::cout << "Invalid months amount. Must be a value between 1 and 12";
		return;
	}
	for (size_t i = 0; i < MONTHS; i++)
	{
		profile[ACCOUNTINCOMEINDEX][i] = 0;
		profile[ACCOUNTEXPENSESINDEX][i] = 0;
	}
	std::cout << "Profile created successfully" << std::endl;
}

bool validateProfile(double profile[][MONTHS]) {
	if (*profile[0] < DEFAULTEMPTYVALUE) return false;
	return true;
}

void stringifyMonth(int targetMonth) {
	switch (targetMonth) {
	case 0: std::cout << "January"; break;
	case 1: std::cout << "February"; break;
	case 2: std::cout << "March"; break;
	case 3: std::cout << "April"; break;
	case 4: std::cout << "May"; break;
	case 5: std::cout << "June"; break;
	case 6: std::cout << "July"; break;
	case 7: std::cout << "August"; break;
	case 8: std::cout << "September"; break;
	case 9: std::cout << "October"; break;
	case 10: std::cout << "November"; break;
	case 11: std::cout << "December"; break;
	}
}

void stringifyShortMonth(int targetMonth) {
	switch (targetMonth) {
	case 0: std::cout << "Jan"; break;
	case 1: std::cout << "Feb"; break;
	case 2: std::cout << "Mar"; break;
	case 3: std::cout << "Apr"; break;
	case 4: std::cout << "May"; break;
	case 5: std::cout << "Jun"; break;
	case 6: std::cout << "Jul"; break;
	case 7: std::cout << "Aug"; break;
	case 8: std::cout << "Sep"; break;
	case 9: std::cout << "Oct"; break;
	case 10: std::cout << "Nov"; break;
	case 11: std::cout << "Dec"; break;
	}
}

void toUpper(char* input) {
	if (!input) return;

	while (*input) {
		if (*input >= 'a' && *input <= 'z') *input = *input ^ ' ';
		input++;
	}
}

int parseSortingType(char* input) {
	if (!input) return -1;
	char* start = input;
	for (size_t i = 0; i < SORTINGTYPESCOUNT; i++)
	{
		input = start;
		const char* currentType = TYPES[i];
		while (*input) {
			if (*input != *currentType) {
				break;
			}
			input++;
			currentType++;
		}
		if (*currentType == *input) return i;
	}
	return -1;
}

int parseChar(char*& input) {
	if (!input || !*input) return -1;

	int number = 0;
	while (*input >= '0' && *input <= '9') {
		number = (number * 10) + (*input - '0');
		input++;
	}

	return number;
}

int parseCommand(char* &input) {
	if (!input) return -1;
	char* start = input;
	for (size_t i = 0; i < COMMANDSCOUNT; i++)
	{
		input = start;
		const char* currentType = COMMANDS[i];
		while (*input && *input != ' ') {
			if (*input != *currentType) {
				break;
			}
			input++;
			currentType++;
		}
		if (*currentType == *input) return i;
	}
	return -1;
}

int parseMonth(char* input) {
	if (!input) return -1;
	char* start = input;
	for (size_t i = 0; i < MONTHS; i++)
	{
		input = start;
		const char* currentMonth = MONTHSNAMES[i];
		while (*input) {
			if (*input != *currentMonth) {
				break;
			}
			input++;
			currentMonth++;
		}
		if (*currentMonth == *input) return i;
	}
	return -1;
}

void printResultForTargetMonth(int targetMonth, double income, double expense) {
	std::cout << "Result: Balance for ";
	stringifyMonth(targetMonth);
	std::cout << ": " << income - expense << std::endl;
}

void inputMonthValues(double profile[][MONTHS], int profileMonths) {
	if (!validateProfile(profile)) {
		std::cout << "Profile has not been created yet! \n";
		return;
	}
	int targetMonth;
	double income;
	double expenses;

	std::cout << "Enter month (1-12): ";
	std::cin >> targetMonth;
	std::cout << "Enter income: ";
	std::cin >> income;
	std::cout << "Enter expense: ";
	std::cin >> expenses;
	targetMonth -= NORMALIZEINPUTMONTHINDEX;
	if (targetMonth < profileMonths) {
		double incomeMonth = profile[ACCOUNTINCOMEINDEX][targetMonth] += income;
		double expenseMonth = profile[ACCOUNTEXPENSESINDEX][targetMonth] += expenses;

		printResultForTargetMonth(targetMonth, income, expenses);
		return;
	}
	std::cout << "Invalid month";
	
}

void returnMonthlyReport(double profile[][MONTHS]) {
	if (!validateProfile(profile)) {
		std::cout << "Profile has not been created yet! \n";
		return;
	}
	std::cout << "---------------------------------- \n";
	std::cout << "Month | Income | Expense | Balance \n";
	std::cout << "---------------------------------- \n";
	double totalIncome = 0;
	double totalExpenses = 0;
	int activeMonths = 0;
	
	for (size_t i = 0; i < MONTHS; i++)
	{
		double currentMonthIncome = profile[ACCOUNTINCOMEINDEX][i];
		double currentMonthExpenses = profile[ACCOUNTEXPENSESINDEX][i];

		if (currentMonthIncome > DEFAULTEMPTYVALUE && currentMonthExpenses > DEFAULTEMPTYVALUE) {
			totalIncome += currentMonthIncome;
			totalExpenses += currentMonthExpenses;
			activeMonths++;
			stringifyMonth(i);
			std::cout << " | " << currentMonthIncome << " | " << currentMonthExpenses << " | " << currentMonthIncome-currentMonthExpenses << std::endl;
		}
	}
	if (!activeMonths) {
		std::cout << "No valid existing months. A valid month is a month with income and expense different than 0. \n";
		std::cout << "---------------------------------- \n";
		return;
	}
	std::cout << "---------------------------------- \n";
	std::cout << "Total income: " << totalIncome << std::endl;
	std::cout << "Total expense: " << totalExpenses << std::endl;
	std::cout << "Average Balance: " << (totalIncome - totalExpenses) / activeMonths << std::endl;

}

void search(char* targetMonth, double profile[][MONTHS], int profileMonths) {
	if (!validateProfile(profile)) {
		std::cout << "Profile has not been created yet! \n";
		return;
	}
	toUpper(targetMonth);
	int parsedMonth = parseMonth(targetMonth);
	if (parsedMonth == -1 || parsedMonth >= profileMonths) {
		std::cout << "Invalid month" << std::endl;
		return;
	}
	double currentMonthIncome = profile[ACCOUNTINCOMEINDEX][parsedMonth];
	double currentMonthExpense = profile[ACCOUNTEXPENSESINDEX][parsedMonth];
	std::cout << "Income: " << currentMonthIncome << std::endl;
	std::cout << "Expense: " << currentMonthExpense << std::endl;
	std::cout << "Balance: " << currentMonthIncome-currentMonthExpense << std::endl;
	std::cout << "Expense Ratio: " << (currentMonthExpense/currentMonthIncome)* CONVERTTOPERCENTAGES << std::endl;

}

void copyArray(double toCopy[][MONTHS], const double source[][MONTHS]) {
	for (size_t i = 0; i < MONTHS; i++)
	{
		for (size_t j = 0; j < ACCOUNTROWS; j++)
		{
			toCopy[j][i] = source[j][i];
		}
	}
}

void sortByType(double profile[][MONTHS], char* typeOfSort) {
	if (!validateProfile(profile)) {
		std::cout << "Profile has not been created yet! \n";
		return;
	}
	char signType = '+';
	toUpper(typeOfSort);
	int parsedType = parseSortingType(typeOfSort);
	double profileCopy[ACCOUNTROWS][MONTHS];
	copyArray(profileCopy, profile);
	switch (parsedType) {
	case SORTINGBYEXPENSES: std::cout << "Sorted by monthly expenses (ascending): \n"; signType = '-';
	case SORTINGBYINCOME:
		if(parsedType == SORTINGBYINCOME) std::cout << "Sorted by monthly income (descending): \n";
		for (size_t i = 0; i < SORTINGTYPESCOUNT; i++)
		{
			int index = 0;
			double maxValue = profileCopy[parsedType][index];
			for (size_t j = 0; j < MONTHS; j++)
			{
				double currentValue = profileCopy[parsedType][j];
				if (currentValue > maxValue) {
					maxValue = currentValue;
					index = j;
				}

			}
			stringifyMonth(index);
			std::cout << ": " << signType << maxValue << std::endl;
			profileCopy[parsedType][index] = -1;
		}
		break;
	case SORTINGBYBALANCE: std::cout << "Sorted by monthly balance (descending): \n";
		for (size_t i = 0; i < SORTINGTYPESCOUNT; i++)
		{
			int index = 0;
			double maxBalance = profileCopy[ACCOUNTINCOMEINDEX][index] - profileCopy[ACCOUNTEXPENSESINDEX][index];
			for (size_t j = 0; j < MONTHS; j++)
			{
				double currentBalance = profileCopy[ACCOUNTINCOMEINDEX][j] - profileCopy[ACCOUNTEXPENSESINDEX][j];
				if (currentBalance > maxBalance) {
					maxBalance = currentBalance;
					index = j;
				}

			}
			stringifyMonth(index);
			std::cout << ": " << maxBalance << std::endl;
			profileCopy[ACCOUNTINCOMEINDEX][index] = -1;
			profileCopy[ACCOUNTEXPENSESINDEX][index] = -1;
		}
		break;
	default: std::cout << "Invalid parseType. Valid options are: balance, income, expenses.";
	}
	

}

void forecast(double profile[][MONTHS], int monthsAhead) {
	if (!validateProfile(profile)) {
		std::cout << "Profile has not been created yet! \n";
		return;
	}
	double savings = 0;
	int activeMonths = 0;
	for (size_t i = 0; i < MONTHS; i++)
	{
		double currentMonthIncome = profile[ACCOUNTINCOMEINDEX][i];
		double currentMonthExpense = profile[ACCOUNTEXPENSESINDEX][i];
		if (currentMonthIncome > DEFAULTEMPTYVALUE && currentMonthExpense > DEFAULTEMPTYVALUE) {
			savings += currentMonthIncome - currentMonthExpense;
			activeMonths++;
		}
	}
	double averageMonthlyChange = savings / activeMonths;

	std::cout << "Current savings: " << savings << std::endl;
	std::cout << "Average monthly change: " << averageMonthlyChange << std::endl;
	if (averageMonthlyChange < 0) {
		std::cout << "Predicted savings after " << monthsAhead << " months: " << savings / -averageMonthlyChange << std::endl;
	}
	else {
		std::cout << "Predicted savings after " << monthsAhead << " months: " << savings + monthsAhead * averageMonthlyChange << std::endl;
	}

}

void findMinMaxValueArray(double profile[][MONTHS], double& maxValue, double& minValue) {
	maxValue = profile[ACCOUNTINCOMEINDEX][0]- profile[ACCOUNTEXPENSESINDEX][0];
	minValue = profile[ACCOUNTINCOMEINDEX][0] - profile[ACCOUNTEXPENSESINDEX][0];
	for (size_t i = 1; i < MONTHS; i++)
	{
		double income = profile[ACCOUNTINCOMEINDEX][i];
		double expense = profile[ACCOUNTEXPENSESINDEX][i];
		if (income != -1 && expense != -1) {
			double balance = income - expense;
			if (maxValue < balance) maxValue = balance;
			if (minValue > balance) minValue = balance;
		}
	}
}
void chart(double profile[][MONTHS], char* typeOfChart) {
	if (!validateProfile(profile)) {
		std::cout << "Profile has not been created yet! \n";
		return;
	}
	double maxValue = 0;
	double minValue = 0;
	toUpper(typeOfChart);
	int parsedType = parseSortingType(typeOfChart);
	switch (parsedType) {
	case SORTINGBYEXPENSES: std::cout << "=== YEARLY FINANCIAL EXPENSES CHART === \n \n";
	case SORTINGBYINCOME:
		if (parsedType == SORTINGBYINCOME) std::cout << "=== YEARLY FINANCIAL INCOME CHART === \n \n";
		maxValue = profile[parsedType][0];
		minValue = profile[parsedType][0];
		for (size_t j = 0; j < MONTHS; j++)
		{
			double currentValue = profile[parsedType][j];
			if (currentValue > maxValue) maxValue = currentValue;
			if (currentValue < minValue && minValue) minValue = currentValue;

		}
		break;
	case SORTINGBYBALANCE: std::cout << "=== YEARLY FINANCIAL BALANCE CHART === \n \n";
		maxValue = profile[ACCOUNTINCOMEINDEX][0] - profile[ACCOUNTEXPENSESINDEX][0];
		minValue = profile[ACCOUNTINCOMEINDEX][0] - profile[ACCOUNTEXPENSESINDEX][0];
		for (size_t j = 0; j < MONTHS; j++)
		{

			double currentValue = profile[ACCOUNTINCOMEINDEX][j] - profile[ACCOUNTEXPENSESINDEX][j];
			if (currentValue > maxValue) maxValue = currentValue;
			if (currentValue < minValue) minValue = currentValue;

		}
		break;
	}

	const double decrementValue = (maxValue - minValue) / CHARTSTEPS;
	double treshold = maxValue;

	for (size_t i = 0; i < CHARTSTEPS; i++)
	{
		int intTreshold = int(treshold);
		if (i == CHARTSTEPS - 1) intTreshold = minValue;

		if (intTreshold >= 1000) std::cout << " ";
		else if (intTreshold >= 100) std::cout << "  ";
		else if (intTreshold >= 10) std::cout << "   ";
		else if (intTreshold >= 0) std::cout << "    ";
		else if (intTreshold > -10) std::cout << "   ";
		else if (intTreshold > -100) std::cout << "  ";
		else std::cout << " ";

		std::cout << intTreshold << " |  ";
		for (size_t j = 0; j < MONTHS; j++)
		{
			double income = profile[ACCOUNTINCOMEINDEX][j];
			double expense = profile[ACCOUNTEXPENSESINDEX][j];
			if (income != -1 && expense != -1) {
				switch(parsedType) {
				case SORTINGBYBALANCE: if (int(income-expense) >= treshold) std::cout << "#   "; else std::cout << "  ";break;
				case SORTINGBYEXPENSES: if(int(expense) >= treshold) std::cout << "#   ";else std::cout << "  ";break;
				case SORTINGBYINCOME: if(int(income) >= treshold) std::cout << "#   ";else std::cout << "  ";break;
				}
			}
		}
		std::cout << std::endl;
		treshold -= decrementValue;
	}
	std::cout << "--------------------------- \n        ";
	for (size_t i = 0; i < MONTHS; i++)
	{
		double income = profile[ACCOUNTINCOMEINDEX][i];
		double expense = profile[ACCOUNTEXPENSESINDEX][i];
		if (income > DEFAULTEMPTYVALUE && expense > DEFAULTEMPTYVALUE) {
			stringifyShortMonth(i);
			std::cout << " ";
		}
	}
	std::cout << std::endl;


}

void commandIteration(char* command, char*& ptr) {
	std::cin >> command;
	ptr = command;
}


int main() {
	int profileMonths = 0;
	double profile[ACCOUNTROWS][MONTHS];
	char command[1024];
	std::cin >> command;
	while (true) {
		toUpper(command);
		char* commandPtr = command;
		int commandIndex = parseCommand(commandPtr);

		switch (commandIndex) {
		case EXITINDEX: return 1;
		case SETUPINDEX: std::cin >> profileMonths; setupAccount(profile, profileMonths); break;
		case REPORTINDEX: returnMonthlyReport(profile); break;
		case ADDINDEX: inputMonthValues(profile, profileMonths); break;
		case SEARCHINDEX: commandIteration(command, commandPtr); search(commandPtr, profile, profileMonths);break;
		case SORTINDEX: commandIteration(command, commandPtr); sortByType(profile, commandPtr);break;
		case FORECASTINDEX: int forecastMonths; std::cin >> forecastMonths; forecast(profile, forecastMonths); break;
		case CHARTINDEX: commandIteration(command, commandPtr); chart(profile, commandPtr); break;
		default: std::cout << "Wrong command, valid commands are: exit, setup, add, report, search, sort, forecast, chart.\n";
		}

		std::cin >> command;
	}

	return 1;
}