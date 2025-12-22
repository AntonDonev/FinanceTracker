#include <iostream>
const int MONTHS = 12;
const int DEFAULTINACTIVEVALUE = -1;
const int DEFAULTEMPTYVALUE = 0;
const int ACCOUNTEXPENSESINDEX = 1;
const int ACCOUNTINCOMEINDEX = 0;
const int NORMALIZEINPUTMONTHINDEX = 1;
const int ACCOUNTROWS = 2;
const int CONVERTTOPERCENTAGES = 100;
const char* MONTHSNAMES[] = {
		"January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December"
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
	std::cout << "Expense Ratio: " << (currentMonthExpense/currentMonthIncome)* CONVERTTOPERCENTAGES;

}



int main() {
	// setupAccount

	double profile[ACCOUNTROWS][MONTHS];
	int activeMonths;
	std::cin >> activeMonths;
	setupAccount(profile, activeMonths);
	inputMonthValues(profile, 1, 2500, 1250);
	inputMonthValues(profile, 2, 2400, 1350);
	inputMonthValues(profile, 3, 2200, 2000);


	returnMonthlyReport(profile);
	char string[] = "March";
	search(string, profile);



	return 1;
}