#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cctype>
using namespace std;

/**
 * Removes all non alphanumeric characters from given word and converts to lower case.
 * @param[in,out] word on return word consist only of lower case characters.
 */
void toLowerAlpha(std::string& s1) {
    s1.erase(std::remove_if(s1.begin(), s1.end(), [](char c){ return !std::isalnum(c); }), s1.end());
    std::transform(s1.begin(), s1.end(), s1.begin(), [](char c){ return std::tolower(c); });
}

int main() {
    map<string, int> wordCount;

    string word;
    while (cin >> word) {
        toLowerAlpha(word);
        if (!word.empty()) {
            ++wordCount[word];  
        }
    }

    cout << "Number of distinct words : " << wordCount.size() << "\n";

    multimap<int, string> freqMap;
    for (const auto& entry : wordCount) {
        freqMap.insert({ entry.second, entry.first });
    }

    cout << "\nThe top 20 most popular words:\n";
    int printed = 0;
    for (auto it = freqMap.rbegin(); it != freqMap.rend() && printed < 20; ++it, ++printed) {
        cout << it->second << " : " << it->first << "\n";
    }

    return 0;
}

/*
 * map vs unordered_map performance:
 *
 *  map<string,int>
 *    - Backed by a balanced BST (red-black tree).
 *    - O(log n) insert / lookup.
 *    - Keys are always sorted — useful when order matters.
 *    - Slightly higher memory overhead per node (left/right/parent pointers + colour bit).
 *
 *  unordered_map<string,int>
 *    - Backed by a hash table.
 *    - O(1) average insert / lookup, O(n) worst case (hash collisions).
 *    - No ordering guarantee.
 *    - Faster in practice for large inputs (e.g. counting words in a big text file).
 */