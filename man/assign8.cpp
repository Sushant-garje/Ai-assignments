#include <bits/stdc++.h>
using namespace std;

struct Rule {
vector<string> antecedents;
string consequent;
};

// Build an index: consequent -> list of rules producing it
unordered_map<string, vector<Rule>> index_rules(const
vector<Rule>& rules) 
{
    unordered_map<string, vector<Rule>> idx;
    for (const auto &r : rules) idx[r.consequent].push_back(r);
    return idx;
}

/*
backward_prove:
- goal: symbol to prove
- facts: current set of known facts (updated when we prove new
facts)
- rules_by_cons: rules indexed by consequent
- proven: cache of already proved symbols (to avoid re-proving)
- visiting: set of symbols currently on the recursion stack (cycle
detection)

- trace: appended lines describing steps (for printing)
*/
bool backward_prove(const string &goal,
unordered_set<string> &facts,
unordered_map<string, vector<Rule>> &rules_by_cons,
unordered_set<string> &proven,
unordered_set<string> &visiting,
vector<string> &trace) {
    // 1) If it's already a known fact -> success
    if (facts.count(goal)) {
        trace.push_back("KNOWN FACT: " + goal);
        proven.insert(goal);
        return true;
    }
    // 2) If we already proved it before -> success (reuse)
    if (proven.count(goal)) {
        trace.push_back("ALREADY PROVED: " + goal);
        return true;
    }
    // 3) Cycle detection: if goal is on current path, fail this branch
    if (visiting.count(goal)) {
        trace.push_back("CYCLE DETECTED: " + goal);
        return false;
    }
    // 4) Find rules that can produce the goal
    auto it = rules_by_cons.find(goal);
    if (it == rules_by_cons.end()) {
        trace.push_back("NO RULES PRODUCE: " + goal);
        return false;
    }
    visiting.insert(goal);
    trace.push_back("TRY PROVING: " + goal);

    // Try each rule with consequent == goal
    for (const auto &rule : it->second) {
        // show the rule being tried
        {
            string s = " Try rule: ";
            for (size_t i = 0; i < rule.antecedents.size(); ++i) {
                if (i) s += " ∧ ";
                s += rule.antecedents[i];
            }
            s += " ⇒ " + rule.consequent;
            trace.push_back(s);
        }
        bool rule_ok = true;
        // Attempt to prove every antecedent (recursive)
        for (const auto &ant : rule.antecedents) {
            bool ant_proved = backward_prove(ant, facts, rules_by_cons,proven, visiting, trace);
            if (!ant_proved) {
                trace.push_back(" -> antecedent FAILED: " + ant);
                rule_ok = false;
                break;
            } else {
                trace.push_back(" -> antecedent PROVED: " + ant);
            }
        }
        if (rule_ok) {
            // All antecedents proved -> this rule proves the goal
            facts.insert(goal); // add to facts for future reuse
            proven.insert(goal);
            trace.push_back("RULE SUCCEEDED -> proved: " + goal);
            visiting.erase(goal);
            return true;
        } else {
            trace.push_back("Rule failed for: " + goal);
        }
    }
    // All candidate rules failed
    visiting.erase(goal);
    trace.push_back("ALL RULES FAILED for: " + goal);
    return false;
}

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Rule> rules = {
        {{"Fever","Cough"}, "ViralInfection"},
        {{"ViralInfection","BodyAche"}, "FluSymptoms"},
        {{"FluSymptoms"}, "Flu"}
    };
    unordered_set<string> facts = {"Fever", "Cough", "BodyAche"};
    auto rules_by_cons = index_rules(rules);

    string query = "Flu";
    vector<string> trace;
    unordered_set<string> proven;
    unordered_set<string> visiting;

    bool result = backward_prove(query, facts, rules_by_cons, proven,visiting, trace);

    cout << "Backward Chaining Trace:\n";
    for (auto &line : trace) cout << line << "\n";

    cout << "\nResult: " << (result ? "PROVED" : "NOT PROVED") << "for goal: " << query << "\n";
    cout << "Final facts: ";
    for (auto &f : facts) cout << f << " ";
    cout << "\n";
    return 0;
}