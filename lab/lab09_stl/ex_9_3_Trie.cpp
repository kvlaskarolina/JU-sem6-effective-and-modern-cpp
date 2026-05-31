#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

class Trie {
private:
    std::map<string, Trie*> children;
    bool isEnd = false;

public:
    Trie() {}

    static void printSentence(const std::vector<std::string>& sentence) {
        for (const auto& w : sentence)   
            cout << w << " ";
    }

    void add(const std::vector<std::string>& sentence, int index = 0) {
        if (index == 0) {
            cout << "Adding : ";
            printSentence(sentence);
            cout << "\n";
        }
        if (index == (int)sentence.size()) {
            isEnd = true;
            return;
        }

        const std::string& word = sentence[index];
        if (children.find(word) == children.end())
            children[word] = new Trie();

        children[word]->add(sentence, index + 1);
    }

    void printPossibleEndings(const std::vector<std::string>& beginning) {
        cout << "Endings for \"";
        printSentence(beginning);
        cout << "\" are :\n";

        Trie* current = this;
        for (const auto& w : beginning) {  
            if (current->children.find(w) == current->children.end()) {
                cout << " No such sentence in the dictionary.\n";
                return;
            }
            current = current->children[w];
        }

        printEndings(current, beginning);
    }

    void printEndings(Trie* node, const std::vector<std::string>& prefix) {
        if (node->isEnd) {
            cout << " > ";
            printSentence(prefix);
            cout << "\n";
            return;
        }
        for (const auto& [key, child] : node->children) { 
            std::vector<std::string> newPrefix = prefix;
            newPrefix.push_back(key);
            printEndings(child, newPrefix);
        }
    }

    void load(const std::string& fileName) {
        ifstream file(fileName);
        if (!file) {
            cerr << "Error when opening file " << fileName << endl;
            return;
        }
        string word;
        vector<string> sentence;
        while (file >> word) {
            sentence.push_back(word);
            if (word.find_last_of('.') != string::npos) {
                add(sentence);
                sentence.clear();
            }
        }
    }
};

int main(){
    Trie dictionary;
    dictionary.load("sample.txt");

    dictionary.printPossibleEndings({"Curiosity"});
    dictionary.printPossibleEndings({"Curiosity", "killed"});
    dictionary.printPossibleEndings({"The", "mouse","was","killed"});
    return 0;
}
/* Expected output:
Adding : Curiosity killed the cat.
Adding : Curiosity killed the mouse.
Adding : Curiosity saved the cat.
Adding : Curiosity killed the cat and the mouse.
Adding : The cat was killed by curiosity.
Adding : The mouse was killed by cat.
Adding : The mouse was killed by curiosity.
Endings for "Curiosity " are :
 > killed the cat.
 > killed the mouse.
 > killed the cat and the mouse.
 > saved the cat.

Endings for "Curiosity killed " are :
 > killed the cat.
 > killed the mouse.
 > killed the cat and the mouse.

Endings for "The mouse was killed " are :
 > by cat.
 > by curiosity.

 */