#include<iostream>
#include<string>
using namespace std;


void getNext(string pattern, int next[]) {
    next[0] = -1;//下标零默认为 -1
    int i = 1, j = 0;
    while (i < pattern.size() || j < pattern.size()) {
        if (j == -1 || pattern[i] == pattern[j]) {
            j++;
            next[i] = j;
        }
        else {
            j = next[j];
        }
    }
}


int kmp(string s, string p, int next[]) {
    int i = 0;
    int j = 0;
    int sLen = s.size();
    int pLen = p.size();

    while (i < sLen && j < pLen) {
        if (j == -1 || s[i] == p[j]) {
            i++;
            j++;
        }
        else {
            j = next[j];
        }
    }

    if (j == pLen) return i - j;
    return -1;
}




int main() {
    string pattern;
    string s;
    cout << "请输入主串:";
    getline(cin, s);
    cout << "请输入主串:";
    getline(cin, pattern);
    int* next = new int[pattern.size()];

    getNext(pattern, next);
    for (int i = 0;i < pattern.size();i++) {
        cout << next[i] << " ";
    }
    cout << endl;

    cout << kmp(s, pattern, next) << endl;
    return 0;
}