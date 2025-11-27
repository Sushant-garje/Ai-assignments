#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Rule {
    vector<string> antecedents;
    string consequent;
    bool used = false; 
};
bool canFire(const Rule &rule, const vector<string> &facts) {
    for (auto &ant : rule.antecedents) {
        bool found = false;
        for (auto &f : facts) {
            if (f == ant) { 
                found = true; break; 
            }
        }
        if (!found) return false; // one antecedent missing
        }
    return true;
}
int main() {
// Example Rules:
// 1. P ∧ Q ⇒ R
// 2. R ∧ S ⇒ T
// 3. T ⇒ U
vector<Rule> rules = {
    {{"P","Q"}, "R"},
    {{"R","S"}, "T"},
    {{"T"}, "U"}
};

vector<string> facts = {"P", "Q", "S"};
string query = "U"; 
bool derived = false;

cout << "Initial facts: ";
for (auto &f : facts) cout << f << " ";
cout << "\n";
bool addedNew;
do {
    addedNew = false;
    for (auto &rule : rules) {
        if (!rule.used && canFire(rule, facts)) {
            cout << "Rule fired: ";
            for (auto &a : rule.antecedents) cout << a << " ";
            cout << "=> " << rule.consequent << "\n";
            facts.push_back(rule.consequent);
            rule.used = true;
            addedNew = true;
            if (rule.consequent == query) {
                derived = true;
                break;
            }
        }
    }
} while (addedNew && !derived);

cout << "\nFinal facts: ";
for (auto &f : facts) cout << f << " ";
cout << "\n";

if (derived)
cout << "SUCCESS: Query " << query << " is derived!\n";
else
cout << "FAIL: Query " << query << " cannot be derived.\n";

return 0;
}