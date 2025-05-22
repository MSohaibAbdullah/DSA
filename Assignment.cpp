#include <iostream>
#include <string>
using namespace std;

class Expense {
public:
    string title;
    float cost;
    string date; // Format: YYYY-MM-DD
    Expense* next;

    Expense(string t, float c, string d) {
        title = t;
        cost = c;
        date = d;
        next = NULL;
    }
};

class ExpenseTracker {
private:
    Expense* head;

public:
    ExpenseTracker() {
        head = NULL;
    }

    // Add new expense
    void addExpense(string title, float cost, string date) {
        Expense* newExpense = new Expense(title, cost, date);
        if (head == NULL) {
            head = newExpense;
        } else {
            Expense* temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newExpense;
        }
        cout << "✅ Expense added successfully!\n";
    }

    // View all expenses
    void viewExpenses() {
        if (head == NULL) {
            cout << "❌ No expenses found.\n";
            return;
        }
        Expense* temp = head;
        cout << "\n--- All Expenses ---\n";
        while (temp != nullptr) {
            cout << "Title: " << temp->title
                 << ", Cost: Rs." << temp->cost
                 << ", Date: " << temp->date << endl;
            temp = temp->next;
        }
    }

    // Edit expense by title
    void editExpense(string oldTitle, string newTitle, float newCost, string newDate) {
        Expense* temp = head;
        while (temp != nullptr) {
            if (temp->title == oldTitle) {
                temp->title = newTitle;
                temp->cost = newCost;
                temp->date = newDate;
                cout << "✏️ Expense updated successfully!\n";
                return;
            }
            temp = temp->next;
        }
        cout << "❌ Expense not found.\n";
    }

    // Delete expense by title
    void deleteExpense(string title) {
        if (head == nullptr) return;

        if (head->title == title) {
            Expense* toDelete = head;
            head = head->next;
            delete toDelete;
            cout << "🗑️ Expense deleted.\n";
            return;
        }

        Expense* temp = head;
        while (temp->next != nullptr && temp->next->title != title)
            temp = temp->next;

        if (temp->next != nullptr) {
            Expense* toDelete = temp->next;
            temp->next = toDelete->next;
            delete toDelete;
            cout << "🗑️ Expense deleted.\n";
        } else {
            cout << "❌ Expense not found.\n";
        }
    }

    // Most expensive item
    void mostExpensiveItem() {
        if (head == nullptr) {
            cout << "❌ No expenses.\n";
            return;
        }

        Expense* maxExpense = head;
        Expense* temp = head->next;

        while (temp != nullptr) {
            if (temp->cost > maxExpense->cost)
                maxExpense = temp;
            temp = temp->next;
        }

        cout << "💰 Most Expensive Item: "
             << maxExpense->title << ", Rs." << maxExpense->cost
             << " on " << maxExpense->date << endl;
    }

    // (Simple) Monthly report
    void monthlyReport(string month) {
        cout << "\n📅 Monthly Report for: " << month << endl;
        Expense* temp = head;
        float total = 0;
        while (temp != nullptr) {
            if (temp->date.substr(0, 7) == month) {
                cout << temp->title << " - Rs." << temp->cost << " on " << temp->date << endl;
                total += temp->cost;
            }
            temp = temp->next;
        }
        cout << "Total Monthly Expense: Rs." << total << endl;
    }

    // Weekly report (basic using date prefix)
    void weeklyReport(string weekStartDate) {
        cout << "\n🗓️ Weekly Report starting from: " << weekStartDate << endl;
        Expense* temp = head;
        float total = 0;
        while (temp != nullptr) {
            if (temp->date >= weekStartDate && temp->date <= getNext7Days(weekStartDate)) {
                cout << temp->title << " - Rs." << temp->cost << " on " << temp->date << endl;
                total += temp->cost;
            }
            temp = temp->next;
        }
        cout << "Total Weekly Expense: Rs." << total << endl;
    }

    // Fake 7 day forward function (static 7-day range, no date logic)
    string getNext7Days(string startDate) {
        // Just for simplicity: not actually calculating next 7 days
        return startDate; // Placeholder, should implement real logic with <ctime>
    }
};
int main() {
    ExpenseTracker tracker;
    tracker.addExpense("Groceries", 2500, "2025-05-10");
    tracker.addExpense("Fuel", 1500, "2025-05-11");
    tracker.addExpense("Gym", 3000, "2025-05-12");

    tracker.viewExpenses();

    tracker.editExpense("Fuel", "Petrol", 1700, "2025-05-13");

    tracker.deleteExpense("Gym");

    tracker.viewExpenses();

    tracker.mostExpensiveItem();

    tracker.monthlyReport("2025-05");
    tracker.weeklyReport("2025-05-10");

    return 0;
}
