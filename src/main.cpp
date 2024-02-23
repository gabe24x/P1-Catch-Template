#include <iostream>
#include <AVLTree.h>
#include <regex>

using namespace std;

bool processCommand(AVLTree& tree, const string& command) {
    // Regex patterns for each command
    regex insertPattern("^insert\\s+\"([^\"]+)\"\\s+(\\d{8})$");
    regex removePattern("^remove\\s+(\\d{8})$");
    regex searchIdPattern("^search\\s+(\\d{8})$");
    regex searchNamePattern("^search\\s+\"([^\"]+)\"$");
    regex printInorderPattern("^printInorder$");
    regex printPreorderPattern("^printPreorder$");
    regex printPostorderPattern("^printPostorder$");
    regex printLevelCountPattern("^printLevelCount$");
    regex removeInorderPattern("^removeInorder\\s+(\\d+)$");

    smatch match;

    if (regex_match(command, match, insertPattern)) {
        tree.insert(match[1].str(), match[2].str());
        return true;
    }

    else if (regex_match(command, match, removePattern)) {
        tree.remove(match[1].str());
        return true;
    }

    else if (regex_match(command, match, searchIdPattern)) {
        tree.searchID(match[1].str());
        return true;
    }

    else if (regex_match(command, match, searchNamePattern)) {
        tree.searchName(match[1].str());
        return true;
    }

    else if (regex_match(command, match, printInorderPattern)) {
        tree.printInorder();
        return true;
    }

    else if (regex_match(command, match, printPreorderPattern)) {
        tree.printPreorder();
        return true;
    }

    else if (regex_match(command, match, printPostorderPattern)) {
        tree.printPostorder();
        return true;
    }

    else if (regex_match(command, match, printLevelCountPattern)) {
        tree.printLevelCount();
        return true;
    }

    else if (regex_match(command, match, removeInorderPattern)) {
        tree.removeInorder(stoi(match[1].str()));
        return true;
    }

    else {
        cout << "unsuccessful" << endl;
        return false;
    }
}

int main(){
    AVLTree tree;
    string firstLine;
    getline(cin, firstLine);
    int numCommands = stoi(firstLine);

    for (int iterations = 0; iterations < numCommands; ++iterations) {
        string command;
        getline(cin, command);
        processCommand(tree, command);
    }
}