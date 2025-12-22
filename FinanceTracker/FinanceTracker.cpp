#include <iostream>
const int MONTHS = 12;
const int DEFAULTINACTIVEVALUE = -1;
const int ACCOUNTEXPENSESINDEX = 1;
const int ACCOUNTINCOMEINDEX = 0;

void setupAccount(double profile[][MONTHS], int inputMonths) {
	for (size_t i = 0; i < inputMonths; i++)
	{
		profile[ACCOUNTINCOMEINDEX][i] = 0;
		profile[ACCOUNTEXPENSESINDEX][i] = 0;
	}
}

void printMonth(int targetMonth) {
	switch (targetMonth) {
	case 1: std::cout << "January"; break;
	case 2: std::cout << "February"; break;
	case 3: std::cout << "March"; break;
	case 4: std::cout << "April"; break;
	case 5: std::cout << "May"; break;
	case 6: std::cout << "June"; break;
	case 7: std::cout << "July"; break;
	case 8: std::cout << "August"; break;
	case 9: std::cout << "September"; break;
	case 10: std::cout << "October"; break;
	case 11: std::cout << "November"; break;
	case 12: std::cout << "December"; break;
	}
}

void printResultForTargetMonth(int targetMonth, double income, double expense) {
	std::cout << "Result: Balance for ";
	printMonth(targetMonth);
	std::cout << ": " << income - expense << std::endl;
}

void inputMonthValues(unsigned profile[][MONTHS], int targetMonth, double income, double expense) {
	double incomeMonth = profile[ACCOUNTINCOMEINDEX][targetMonth] += income;
	double expenseMonth = profile[ACCOUNTEXPENSESINDEX][targetMonth] += expense;

	printResultForTargetMonth(targetMonth, income, expense);
}

void returnMonthlyReport(unsigned profile[][MONTHS]) {
	std::cout << "Month | Income | Expense | Balance" << std::endl;
	std::cout << "----------------------------------";
	double totalIncome = 0;
	double totalExpenses = 0;
	int activeMonths = 0;
	
	for (size_t i = 0; i < MONTHS; i++)
	{
		double currentMonthIncome = profile[ACCOUNTINCOMEINDEX][i];
		double currentMonthExpenses = profile[ACCOUNTINCOMEINDEX][i];

		if (currentMonthIncome != DEFAULTINACTIVEVALUE && currentMonthExpenses != DEFAULTINACTIVEVALUE) {
			totalIncome += currentMonthIncome;
			totalExpenses += currentMonthExpenses;
			activeMonths++;
			printMonth(i);
			std::cout << " | " << currentMonthIncome << " | " << currentMonthExpenses << " | " << currentMonthIncome-currentMonthExpenses << std::endl;
		}
	}
	std::cout << "----------------------------------" << std::endl;
	std::cout << "Total income: " << totalIncome << std::endl;
	std::cout << "Total expense: " << totalExpenses << std::endl;
	std::cout << "Average Balance: " << (totalIncome - totalExpenses) / activeMonths << std::endl;

}





int main() {
	// setupAccount

	double profile[ACCOUNTEXPENSESINDEX][MONTHS] = { DEFAULTINACTIVEVALUE };
	int activeMonths;
	std::cin >> activeMonths;
	setupAccount(profile, activeMonths);



	return 1;
}