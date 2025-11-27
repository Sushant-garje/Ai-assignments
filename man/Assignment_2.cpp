#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

using namespace std;

// A class to represent a CSP problem
class CSP {
public:
    vector<string> variables; // Variables in the problem
    unordered_map<string, vector<int>> domains; // Domains of each variable
    vector<function<bool(unordered_map<string, int>)>> constraints; // Constraints

    // Add a variable with its domain
    void addVariable(const string& var, const vector<int>& domain) {
        variables.push_back(var);
        domains[var] = domain;
    }

    // Add a constraint
    void addConstraint(function<bool(unordered_map<string, int>)> constraint) {
        constraints.push_back(constraint);
    }

    // Backtracking search to solve the CSP
    bool backtrack(unordered_map<string, int>& assignment) {
        if (assignment.size() == variables.size()) {
            return true; // All variables are assigned
        }

        // Select an unassigned variable
        string var;
        for (const auto& v : variables) {
            if (assignment.find(v) == assignment.end()) {
                var = v;
                break;
            }
        }

        // Try each value in the domain of the variable
        for (int value : domains[var]) {
            assignment[var] = value;

            // Check if the assignment satisfies all constraints
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

            // Undo the assignment
            assignment.erase(var);
        }

        return false; // No solution found
    }

    // Solve the CSP
    bool solve() {
        unordered_map<string, int> assignment;
        return backtrack(assignment);
    }
};

int main() {
    CSP csp;

    // Define variables and their domains
    csp.addVariable("X", {1, 2, 3});
    csp.addVariable("Y", {1, 2, 3});
    csp.addVariable("Z", {1, 2, 3});

    // Add constraints
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

    // Solve the CSP
    if (csp.solve()) {
        cout << "Solution found!" << endl;
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}