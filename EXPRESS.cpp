// Calculate infix (natural) expression
#include <cstdio>
#include <iostream>
#include <cstring>
#include <stack>

using namespace std;

stack <char> st_infix;
stack <long long> st_rpn;

int N;
char opt[6] = {'(', ')', '+', '-', '*', '/'};
string T, rpn, infix;

bool inOpt(char x) {
	for (int j = 0; j < 6; j++)
		if (x == opt[j]) return true;
	return false;
}

void refine(char* s) {
    infix = "";
    for (int i = 0; i < strlen(s); i++)
        if (inOpt(s[i]) || inOpt(s[i+1]))
            infix += s[i], infix += " ";
        else infix += s[i];
    infix += " ";
}

int priority(char x) {
    if (x == '*' || x == '/') return 2;
    return x == '+' || x == '-' ? 1 : 0;
}

void to_rpn(string T) {
    char c = T[0], x;
    if (!inOpt(c)) rpn += T, rpn += " ";
    else {
        if (c == '(') { st_infix.push(c); return; }
        if (c == ')') {
            do {
                x = st_infix.top(); st_infix.pop();
                if (x != '(') rpn += x;   rpn += " ";
            } while (x != '(');
            return;
        }
        while (st_infix.size() && priority(c) <= priority(st_infix.top())) {
            rpn += st_infix.top();  rpn += " ";  st_infix.pop();
        }
        st_infix.push(c);
    }
}

void cover_to_RPN(string infix) {
    T = "";
    for (int i = 0; i < infix.size(); i++)
        if (infix[i] != ' ') T += infix[i];
        else {
            to_rpn(T);  T = "";
        }
    while (st_infix.size()) { rpn += st_infix.top() ; rpn += " "; st_infix.pop(); }
}

long long val(string x) {
    long long p = 0;
    for (int j = 0; j < x.size(); j++)
        p = p*10 + (x[j] - 48);
    return p;
}

void extract(string T) {
    char c = T[0];
    if (!inOpt(c)) st_rpn.push(val(T));
    else {
        long long y = st_rpn.top(); st_rpn.pop();
        long long x = st_rpn.top(); st_rpn.pop();
        if (T == "+") x = x + y;
		if (T == "-") x = x - y;
		if (T == "*") x = x * y;
		if (T == "/") x = x / y;
		st_rpn.push(x);
    }
}

long long calc_RPN(string rpn) {
    T = "";
    while (rpn[rpn.size() - 1] == ' ') rpn.erase(rpn.end() - 1);
    for (int i = rpn.size() - 2; i >= 0; i--)
        if (rpn[i] == ' ' && rpn[i+1] == ' ') rpn.erase(rpn.begin() + i);
    while (st_rpn.size()) st_rpn.pop();
    rpn += " ";
    for (int i = 0; i < rpn.size(); i++)
        if (rpn[i] != ' ') T += rpn[i];
        else {
            extract(T); T = "";
        }
    return st_rpn.top();
}

void debug() {
    cout << rpn << ": ";
    for (int i = 0; i < rpn.size(); i++)
        cout << "{" << rpn[i] << "} ";
    cout << endl;
}

int main() {
	freopen("in.txt", "r", stdin);
	cin >> N;   scanf("\n");
	while (N--) {
        char s[251];
		gets(s);    refine(s);
		cover_to_RPN(infix);
		cout << s << " = " << calc_RPN(rpn) << endl;
		rpn = "";
	}
}
