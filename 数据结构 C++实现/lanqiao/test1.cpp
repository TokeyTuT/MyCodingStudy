#include <iostream>
#include <vector>
#include <string>
#include <queue> 
using namespace std;
class Solution {
public:
    string reverseByType(string s) {
        string alph, sp;
        vector<int> idx1, idx2;
        for (int i = 0;i < s.size();i++) {
            char ch = s[i];
            if ('a' <= ch && ch <= 'z') {
                alph.push_back(ch);
                idx1.push_back(i);
            }
            else {
                sp.push_back(ch);
                idx2.push_back(i);
            }
        }
        cout << sp.size() << endl;
        // idx1.push_back(-1);
        // idx2.push_back(-1);
        reverse(alph.begin(), alph.end());
        reverse(sp.begin(), sp.end());
        cout << alph << endl;
        for (int i = 0;i < alph.size();i++) {
            cout << idx1[i] << "  ";
        }
        cout << sp << endl;

        for (int j = 0;j < sp.size();j++) {
            cout << idx2[j] << "  ";
        }
        cout << endl;
        string res;
        int i = 0, j = 0;
        while (i < alph.size() || j < sp.size()) {
            int id1 = i == alph.size() ? -1 : idx1[i];
            int id2 = j == sp.size() ? -1 : idx2[j];
            if (id2 < id1) {
                res.push_back(sp[j]);
                j++;
            }
            else {
                res.push_back(alph[i]);
                i++;
            }
        }
        return res;

    }
};

int main() {
    string s = ")ebc#da@f(";
    Solution q;
    cout << q.reverseByType(s) << endl;
}