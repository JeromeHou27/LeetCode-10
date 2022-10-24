#include <iostream>
#include <vector>
#include <list>

using namespace std;

const char MatchesSingleCharacter = '.';
const char MatchesMultiCharacter = '*';

struct Regular {
    bool isMatches = false;
    char matches = '/0';
    string text = "";
    int backStringCount = 0;

    Regular(char matches) {
        this->isMatches = true;
        this->matches = matches;
    }

    Regular(string text) {
        this->text = text;
    }

    int getStringCount() {
        return text.size() + backStringCount;
    }
};

vector<Regular> split(string p) {
    vector<Regular> regularList;
    string text = "";
    char lastWord = '\0';
    char lastMatches = '\0';

    for (int i = 0; i < p.size(); ++i) {
        if (p[i] == MatchesMultiCharacter) {
            if (lastWord != '\0') {
                if (text != "") {
                    regularList.push_back(Regular(text));
                    text = "";
                }

                if (lastMatches != '\0') {
                    if (lastMatches != lastWord)
                        regularList.push_back(lastWord);
                }
                else {
                    regularList.push_back(lastWord);
                }

                lastMatches = lastWord;
                lastWord = '\0';
            }
        }
        else {
            if (lastWord != '\0') {
                text += lastWord;
            }

            lastMatches = '\0';
            lastWord = p[i];
        }
    }

    if (lastWord != '\0')
        text += lastWord;
    if (text != "")
        regularList.push_back(Regular(text));

    int size = 0;
    for (int i = regularList.size() - 1; i >= 0; --i) {
        regularList[i].backStringCount = size;
        size += regularList[i].text.size();
    }

    return regularList;
}

bool compareText(const string& s, int offset, const string& p) {
    if (s.size() < p.size()) {
        return false;
    }

    for (int i = 0; i < p.size(); ++i) {
        if (s[i + offset] == p[i] || p[i] == MatchesSingleCharacter)
            continue;

        return false;
    }

    return true;
}

bool match(const string& s, int offset, vector<Regular>& regularList, int index) {
    for (int i = offset; i < s.size(); ++i) {
        if (s.size() - i < regularList[index].getStringCount())
            return false;

        if (regularList[index].isMatches) {
            if (s[i] == regularList[index].matches || regularList[index].matches == MatchesSingleCharacter) {
                if (index == regularList.size() - 1) {
                    continue;
                }

                if (i == s.size() - 1 && regularList[index].backStringCount == 0) {
                    return true;
                }

                if (match(s, i, regularList, index + 1))
                    return true;

                if (i == s.size() - 1) {
                    return false;
                }
            }
            else {
                if (index == regularList.size() - 1) {
                    return false;
                }

                return match(s, i, regularList, index + 1);
            }
        } else {
            if (!compareText(s, i, regularList[index].text)) {
                return false;
            }

            if (regularList[index].backStringCount == 0) {
                if (i == s.size() - regularList[index].text.size())
                    return true;
            }

            if (index == regularList.size() - 1) {
                return s.size() - i - regularList[index].text.size() == 0;
            }

            return match(s, i + regularList[index].text.size(), regularList, index + 1);
        }
    }

    return true;
}

bool isMatch(string s, string p) {

    if (p == "") {
        return s == "";
    }

    vector<Regular> regularList = split(p);

    return match(s, 0, regularList, 0);
}

int main()
{
    string s = "abbabaaaaaaacaa";
    string p = "a*.*b.a.*c*b*a*c*";

    cout << (isMatch(s, p) ? "true" : "false");

    return 0;
}
