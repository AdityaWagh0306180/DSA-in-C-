#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Structure for a transaction
struct Transaction {
    string category;  // e.g., "Food", "Travel", etc.
    double amount;
    string date;
    Transaction(string c, double a, string d) : category(c), amount(a), date(d) {}
};

class CashFlow {
private:
    unordered_map<string, double> balance;  // Name and net balance of each person

public:
    // Function to add a transaction between two people
    void add_transaction(const string& from, const string& to, double amount) {
        balance[from] -= amount;  // Deduct amount from 'from'
        balance[to] += amount;    // Add amount to 'to'
    }

    // Function to minimize cash flow
    void minimize_cash() {
        // Separate creditors and debtors
        vector<pair<string, double>> creditors, debtors;
        for (auto& entry : balance) {
            if (entry.second > 0) {
                creditors.push_back(entry);  // Person is a creditor
            } else if (entry.second < 0) {
                debtors.push_back({entry.first, -entry.second});  // Person is a debtor
            }
        }

        // Minimizing transactions
        size_t i = 0, j = 0;
        cout << "\nMinimized Transactions:\n";
        while (i < creditors.size() && j < debtors.size()) {
            double settledAmount = min(creditors[i].second, debtors[j].second);

            // Print the transaction
            cout << debtors[j].first << " pays " << settledAmount << " to " << creditors[i].first << endl;

            // Adjust the amounts
            creditors[i].second -= settledAmount;
            debtors[j].second -= settledAmount;

            // Move to the next creditor or debtor if fully settled
            if (creditors[i].second == 0) ++i;
            if (debtors[j].second == 0) ++j;
        }
    }

    // Utility function to display balances
    void display_balances() {
        cout << "\nBalances:\n";
        for (auto& entry : balance) {
            cout << entry.first << ": " << entry.second << endl;
        }
    }
};

int main() {
    CashFlow cf;
    int n; // Number of transactions

    cout << "Enter the number of transactions: ";
    cin >> n;

    cout << "Enter the transactions in the format: <payer> <payee> <amount>\n";

    for (int i = 0; i < n; ++i) {
        string payer, payee;
        double amount;
        cin >> payer >> payee >> amount;

        // Add the transaction to the cash flow system
        cf.add_transaction(payer, payee, amount);
    }

    // Display balances before minimizing
    cf.display_balances();

    // Minimize cash flow
    cf.minimize_cash();

    return 0;
}

