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
const char* MONTHSNAMES[] = {
		"JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE",
		"JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"
};
const char* SORTINGTYPES[] = {
		"INCOME", "EXPENSES", "BALANCE"
};

void setupAccount(double profile[][MONTHS], int inputMonths) {
	for (size_t i = 0; i < MONTHS; i++)
	{
		if (i < inputMonths) {
			profile[ACCOUNTINCOMEINDEX][i] = 0;
			profile[ACCOUNTEXPENSESINDEX][i] = 0;
			continue;
		}
		profile[ACCOUNTINCOMEINDEX][i] = -1;
		profile[ACCOUNTEXPENSESINDEX][i] = -1;
		
	}
	std::cout << "Profile created successfully" << std::endl;
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
		const char* currentType = SORTINGTYPES[i];
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

void inputMonthValues(double profile[][MONTHS], int targetMonth, double income, double expense) {
	targetMonth -= NORMALIZEINPUTMONTHINDEX;
	double incomeMonth = profile[ACCOUNTINCOMEINDEX][targetMonth] += income;
	double expenseMonth = profile[ACCOUNTEXPENSESINDEX][targetMonth] += expense;

	printResultForTargetMonth(targetMonth, income, expense);
}

void returnMonthlyReport(double profile[][MONTHS]) {
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
	if (!activeMonths) return;
	std::cout << "---------------------------------- \n";
	std::cout << "Total income: " << totalIncome << std::endl;
	std::cout << "Total expense: " << totalExpenses << std::endl;
	std::cout << "Average Balance: " << (totalIncome - totalExpenses) / activeMonths << std::endl;

}

void search(char* targetMonth, double profile[][MONTHS]) {
	toUpper(targetMonth);
	int parsedMonth = parseMonth(targetMonth);
	if (parsedMonth == DEFAULTINACTIVEVALUE) {
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
void byBalanceSort(double profile[][MONTHS]) {
	double profileCopy[ACCOUNTROWS][MONTHS];
	copyArray(profileCopy, profile);

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

}

void sort(double profile[][MONTHS], char* typeOfSort) {
	char signType = '+';
	toUpper(typeOfSort);
	int parsedType = parseSortingType(typeOfSort);
	std::cout << "Sorted by monthly ";
	double profileCopy[ACCOUNTROWS][MONTHS];
	copyArray(profileCopy, profile);
	switch (parsedType) {
	case SORTINGBYEXPENSES: std::cout << "expenses (ascending): \n"; signType = '-';
	case SORTINGBYINCOME:
		if(parsedType == SORTINGBYINCOME) std::cout << "income (descending): \n";
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
	case SORTINGBYBALANCE: std::cout << "balance (descending): \n";
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
	}

}

void forecast(double profile[][MONTHS], int monthsAhead) {
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



int main() {
	// demo

	double profile[ACCOUNTROWS][MONTHS];
	int activeMonths;
	std::cin >> activeMonths;
	setupAccount(profile, activeMonths);
	inputMonthValues(profile, 1, 2500, 1250);
	inputMonthValues(profile, 2, 2400, 1350);
	inputMonthValues(profile, 3, 2200, 1900);


	returnMonthlyReport(profile);
	char monthinput[] = "march";
	search(monthinput, profile);
	char string[] = "balance";
	sort(profile, string);
	forecast(profile, 6);



	return 1;
}