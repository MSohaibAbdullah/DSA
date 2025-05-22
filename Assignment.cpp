#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Expense {
public:
    string name;
    float amount;
    int day, month, year;
    Expense* next;

    Expense(string n, float a, int d, int m, int y) {
        name = n;
        amount = a;
        day = d;
        month = m;
        year = y;
        next = nullptr;
    }
};

class ExpenseTracker {
private:
    Expense* head;

    void saveExpenseToFile(Expense* exp) {
        ofstream file("Expenses.txt", ios::app);
        if (file.is_open()) {
            file << exp->name << "," << exp->amount << "," 
                 << exp->day << "," << exp->month << "," << exp->year << endl;
            file.close();
        }
    }

public:
    ExpenseTracker() {
        head = nullptr;
        loadExpensesFromFile();
    }

    void addExpense() {
        string name;
        float amount;
        int day, month, year;

        cout << "Enter item name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter amount: ";
        cin >> amount;

        cout << "Enter date (day month year): ";
        cin >> day >> month >> year;

        Expense* newExpense = new Expense(name, amount, day, month, year);
        newExpense->next = head;
        head = newExpense;

        saveExpenseToFile(newExpense);

        cout << "Expense added and saved!\n";
    }

    void loadExpensesFromFile() {
        ifstream file("expenses.txt");
        if (!file.is_open()) return;

        string name;
        float amount;
        int day, month, year;
        char comma;

        
        while (getline(file, name, ',')) {
            file >> amount >> comma >> day >> comma >> month >> comma >> year;
            file.ignore();

            Expense* newExpense = new Expense(name, amount, day, month, year);
            newExpense->next = head;
            head = newExpense;
        }

        file.close();
    }

    void showExpenses() {
        if (!head) {
            cout << "No expenses recorded.\n";
            return;
        }

        Expense* temp = head;
        cout << "All Expenses:\n";
        while (temp) {
            cout << temp->day << "/" << temp->month << "/" << temp->year << " - "
                 << temp->name << ": Rs. " << temp->amount << endl;
            temp = temp->next;
        }
    }

    void showTotalExpense() {
        float total = 0;
        Expense* temp = head;

        
        while (temp) {
            total += temp->amount;
            temp = temp->next;
        }

        cout << "Total Expense: Rs. " << total << endl;
    }

    void showWeeklyReport() {
        int weekDay, weekMonth, weekYear;
        cout << "Enter starting day of week (day month year): ";
        cin >> weekDay >> weekMonth >> weekYear;

        cout << "Weekly Report:\n";

        Expense* temp = head;
        
        while (temp) {
            if (temp->year == weekYear && temp->month == weekMonth &&
                (temp->day >= weekDay && temp->day < weekDay + 7)) {
                cout << temp->day << "/" << temp->month << "/" << temp->year << " - "
                     << temp->name << ": Rs. " << temp->amount << endl;
            }
            temp = temp->next;
        }
    }

    void showMonthlyReport() {
        int month, year;
        cout << "Enter month and year for report: ";
        cin >> month >> year;

        cout << "Monthly Report:\n";

        Expense* temp = head;
        
        while (temp) {
            if (temp->month == month && temp->year == year) {
                cout << temp->day << "/" << temp->month << "/" << temp->year << " - "
                     << temp->name << ": Rs. " << temp->amount << endl;
            }
            temp = temp->next;
        }
    }

    void showMostExpensive() {
        if (!head) {
            cout << "No expenses recorded.\n";
            return;
        }

        Expense* temp = head;
        Expense* maxExpense = head;

        
        while (temp) {
            if (temp->amount > maxExpense->amount) {
                maxExpense = temp;
            }
            temp = temp->next;
        }

        cout << "Most Expensive Item:\n";
        cout << maxExpense->name << ": Rs. " << maxExpense->amount
             << " on " << maxExpense->day << "/" << maxExpense->month << "/" << maxExpense->year << endl;
    }

    ~ExpenseTracker() {
        Expense* current = head;
        while (current) {
            Expense* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    ExpenseTracker tracker;
    int choice;

    do {
        cout << "\n--- Expense Tracker Menu ---\n";
        cout << "1. Add Expense\n";
        cout << "2. Show All Expenses\n";
        cout << "3. Show Total Expense\n";
        cout << "4. Show Weekly Report\n";
        cout << "5. Show Monthly Report\n";
        cout << "6. Most Expensive Item\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: tracker.addExpense(); break;
            case 2: tracker.showExpenses(); break;
            case 3: tracker.showTotalExpense(); break;
            case 4: tracker.showWeeklyReport(); break;
            case 5: tracker.showMonthlyReport(); break;
            case 6: tracker.showMostExpensive(); break;
            case 7: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
