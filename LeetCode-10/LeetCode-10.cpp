#include <iostream>
#include <vector>

using namespace std;

struct Regular {
    string preMatches = "";
    string text = "";
    int backStringCount = 0;

    Regular(string preMatches, string text, int backStringCount) {
        preMatches = preMatches;
        text = text;
        backStringCount = backStringCount;
    }

    bool hasPreMatches() {
        return preMatches.size() > 0;
    }

    int getStringLength() {
        return text.size();
    }
};

vector<Regular> split(string p) {
    vector<Regular> regularVector;
    string preMatches = "";
    string text = "";

    int offset = 0;
    int len = 0;

    for (int i = 0; i < p.size(); ++i) {
        if (p[i] == '*') {
            preMatches += p[i - 1];
            offset = i + 1;
        }
        else {

        }
        if (p[i] != '*') {
            if (i + 1 < p.size() && p[i + 1] == '*') {
                if (preMatches.size() == 0 || preMatches[preMatches.size() - 1] != p[i])
                    preMatches += p[i];
            }
            else {
                text += p[i];
                regularVector.push_back(Regular(preMatches, text, 0));
                text = "";
                text.substr()
            }
        }
    }

    int size = 0;
    string nextText = "";
    for (int i = regularVector.size() - 1; i >= 0; --i) {
        regularVector[i].backStringCount = size;
        nextText = regularVector[i].text;
        size = regularVector[i].getStringLength();
    }

    return regularVector;
}

bool startWith(const string& s, int offset, const string& p) {
    if (s.size() < p.size()) {
        return false;
    }

    for (int i = 0; i < p.size(); ++i) {
        if (s[i + offset] == p[i] || p[i] == '.')
            continue;

        return false;
    }

    return true;
}

bool endWith(const string& s, const string& p) {
    int sSize = s.size();
    int pSize = p.size();
    for (int i = 1; i <= pSize; ++i) {
        if (p[pSize - i] == '.' || s[sSize - i] == p[pSize - i])
            continue;

        return false;
    }

    return true;
}

int find(const string& s, int offset, int interval, Regular& p) {
    if (!p.hasPreMatches()) {
        return startWith(s, offset, p.text) ? offset + p.getStringLength() : -1;
    }

    int succesOffset = -1;
    for (int i = offset; i < offset + interval; ++i) {
        if (s[i] == p.preMatches) {
            if (p.getStringLength() > 0) {
                if (startWith(s, offset, p.text))
                    succesOffset = i;
            }
            else {
                succesOffset = i;
            }
        }
        else {
            if (startWith(s, offset, p.text))
                succesOffset = i;

            break;
        }
    }

    return succesOffset == -1 ? -1 : succesOffset + p.getStringLength();
}

bool isMatch(string s, string p) {

    if (p == "") {
        return s == "";
    }

    vector<Regular> v = split(p);
    int miniOffset = 0;
    int miniInterval = 0;

    for (int i = 0; i < v.size(); ++i) {
        miniInterval = s.size() - miniOffset - v[i].getStringLength();
        if (miniInterval <= 0)
            return false;

        miniOffset = find(s, i, miniInterval, v[i]);
        if (miniOffset < 0)
            return false;

        if (s.size() == miniOffset)
            return v[i].backStringCount == 0;

        if (i + 1 == v.size()) {
            return miniOffset == 0;
        }
    }

    return true;
}

int main()
{
    string s = "abcabc";
    string p = "a*b*c*ab";

    cout << (isMatch(s, p) ? "true" : "false");

    return 0;
}
