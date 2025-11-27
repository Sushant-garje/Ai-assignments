#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

class FamilyTree {
private:
    std::unordered_map<std::string, std::vector<std::string>> knowledgeBase;

public:
    void addRelation(const std::string& parent, const std::string& child) {
        knowledgeBase[parent].push_back(child);
    }

    std::vector<std::string> getChildren(const std::string& parent) {
        if (knowledgeBase.find(parent) != knowledgeBase.end()) {
            return knowledgeBase[parent];
        }
        return {};
    }

    std::string getParent(const std::string& child) {
        for (const auto& pair : knowledgeBase) {
            for (const auto& c : pair.second) {
                if (c == child) {
                    return pair.first;
                }
            }
        }
        return "Unknown";
    }

    void displayFamilyTree() {
        for (const auto& pair : knowledgeBase) {
            std::cout << pair.first << " -> ";
            for (const auto& child : pair.second) {
                std::cout << child << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    FamilyTree familyTree;

    // Adding relations to the knowledge base
    familyTree.addRelation("John", "Alice");
    familyTree.addRelation("John", "Bob");
    familyTree.addRelation("Alice", "Charlie");
    familyTree.addRelation("Alice", "Diana");

    // Display the family tree
    std::cout << "Family Tree:" << std::endl;
    familyTree.displayFamilyTree();

    // Querying the knowledge base
    std::string parent = "Alice";
    std::cout << "\nChildren of " << parent << ": ";
    for (const auto& child : familyTree.getChildren(parent)) {
        std::cout << child << " ";
    }
    std::cout << std::endl;

    std::string child = "Charlie";
    std::cout << "Parent of " << child << ": " << familyTree.getParent(child) << std::endl;

    return 0;
}