#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

using namespace std;

// A class to represent a CSP problem
class CSP {
public:
    vector<string> variables;
    unordered_map<string, vector<int>> domains;
    vector<function<bool(unordered_map<string, int>)>> constraints;

    unordered_map<string, int> finalAssignment; // store final solution

    void addVariable(const string& var, const vector<int>& domain) {
        variables.push_back(var);
        domains[var] = domain;
    }

    void addConstraint(function<bool(unordered_map<string, int>)> constraint) {
        constraints.push_back(constraint);
    }

    bool backtrack(unordered_map<string, int>& assignment) {
        if (assignment.size() == variables.size()) {
            finalAssignment = assignment;  // store solution
            return true;
        }

        string var;
        for (const auto& v : variables) {
            if (assignment.find(v) == assignment.end()) {
                var = v;
                break;
            }
        }

        for (int value : domains[var]) {
            assignment[var] = value;

            bool valid = true;
            for (const auto& constraint : constraints) {
                if (!constraint(assignment)) {
                    valid = false;
                    break;
                }
            }

            if (valid && backtrack(assignment)) {
                return true;
            }

            assignment.erase(var);
        }

        return false;
    }

    bool solve() {
        unordered_map<string, int> assignment;
        return backtrack(assignment);
    }
};

int main() {
    CSP csp;

    csp.addVariable("X", {1, 2, 3});
    csp.addVariable("Y", {1, 2, 3});
    csp.addVariable("Z", {1, 2, 3});

    csp.addConstraint([](unordered_map<string, int> assignment) {
        if (assignment.find("X") != assignment.end() && assignment.find("Y") != assignment.end()) {
            return assignment["X"] != assignment["Y"];
        }
        return true;
    });

    csp.addConstraint([](unordered_map<string, int> assignment) {
        if (assignment.find("Y") != assignment.end() && assignment.find("Z") != assignment.end()) {
            return assignment["Y"] < assignment["Z"];
        }
        return true;
    });

    // Solve and print solution
    if (csp.solve()) {
        cout << "Solution found!" << endl;
        for (auto &p : csp.finalAssignment) {
            cout << p.first << " = " << p.second << endl;
        }
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}
