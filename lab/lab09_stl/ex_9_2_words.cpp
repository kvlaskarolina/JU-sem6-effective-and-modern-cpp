#include <iostream>
#include <vector>
#include <map>
using namespace std;

/**
 * Removes all non alphanumeric characters from given word and converts to lower case.
 * @param[in,out] word on return word consist only of lower case characters.
 */
void toLowerAlpha(std::string & s1) {
    s1.erase(std::remove_if(s1.begin(), s1.end(), [](char c){ return !std::isalnum(c); }), s1.end());
    std::transform(s1.begin(), s1.end(), s1.begin(), [](char c){ return std::tolower(c); });
}

int main(){
    int count = 0;


    map<string,int> wordCount;
    string word;
        while (cin >> word) {
            toLowerAlpha(word);
            if (!word.empty()) {
                if (wordCount.find(word) == wordCount.end()) {
                    ++count; 
                }
                ++wordCount[word];
            }
        }
        vector<pair<string,int>> wordVector(wordCount.begin(), wordCount.end());
        sort(wordVector.begin(), wordVector.end(), [](const pair<string,int>& a, const pair<string,int>& b) {
            return a.second > b.second; // Sort in descending order of count
        });
        
        cout << "Number of distinct words : " << count << endl;
        cout << "\nThe top 20 most popular words: \n";

        for (size_t i = 0; i < min(wordVector.size(), size_t(20)); ++i) {
            cout << wordVector[i].first << " : " << wordVector[i].second << endl;
        }
        

    // ...
    return 0;
}
/*
 * Expected output for ./words < hamletEN.txt

Number of distinct words : 4725

The top 20 most popular words:
the : 1145
and : 967
to : 745
of : 673
i : 569
you : 550
a : 536
my : 514
hamlet : 465
in : 437
it : 417
that : 391
is : 340
not : 315
lord : 311
this : 297
his : 296
but : 271
with : 268
for : 248
your : 242

 */