#include<string>
#include<vector>
#include<stack>
#include<algorithm>
#include<iostream>
#include<unordered_set>
using namespace std;

int getPri(const string& s) {
    if (s == "+" || s == "-") {
        return 1;
    }
    else if (s == "*" || s == "/") {
        return 2;
    }
    return 0; // (
}
vector<string> infixToPostfix(const vector<string>& infix) {
    stack<string> st;
    vector<string> res;

    for (const string& s : infix) {
        if (isdigit(s[0])) {
            res.push_back(s);
        }
        else if (s == ")") {
            while (!st.empty() && st.top() != "(") {
                res.push_back(st.top());
                st.pop();
            }
            if (!st.empty() && st.top() == "(") {
                st.pop();
            }
        }
        else if (s == "(") {
            st.push(s);
        }
        else {
            while (!st.empty() && getPri(s) <= getPri(st.top())) {
                res.push_back(st.top());
                st.pop();
            }
            st.push(s);
        }
    }

    while (!st.empty()) {
        res.push_back(st.top());
        st.pop();
    }
    return res;
}

int calcPostfix(const vector<string>& postfix) {
    stack<string> st;
    for (const string& s : postfix) {
        if (isdigit(s[0])) {
            st.push(s);
        }
        else {
            int n1 = stoi(st.top());
            st.pop();
            int n2 = stoi(st.top());
            st.pop();
            if (s == "+") {
                st.push(to_string(n1 + n2));
            }
            else if (s == "-") {
                st.push(to_string(n2 - n1));
            }
            else if (s == "*") {
                st.push(to_string(n2 * n1));
            }
            else if (s == "/") {
                st.push(to_string(n2 / n1));
            }
        }
    }
    return stoi(st.top());
}


vector<string> stringToInfix(const string& s) {
    vector<string> res;
    string o;
    unordered_set<char> op = { '+','-','*','/','(',')' };
    for (char ch : s) {
        if (isspace(ch)) continue;

        if (op.find(ch) != op.end()) {
            if (!o.empty()) {
                res.push_back(o);
                o = "";
            }
            res.push_back(string(1, ch));
        }
        else if (isdigit(ch)) {
            o += ch;
        }
    }
    if (!o.empty()) res.push_back(o);
    return res;
}
int main() {
    string s;
    cout << "请输入您要转换的中缀表达式:";
    getline(cin, s);
    vector<string> infix = stringToInfix(s);
    vector<string> postfix = infixToPostfix(infix);
    cout << "最终结果为:" << calcPostfix(postfix) << endl;
    return 0;
}