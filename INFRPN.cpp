#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>

using namespace std;

char Opt[6] = {'(', ')', '+', '-', '*', '/'};
string T;
char Infix[1000000];
stack <char> st;

int Priority(char ch) {
    if (ch == '*' || ch == '/') return 2;
    return ch == '+' || ch == '-' ? 1 : 0;
}

bool InOpt(char x) {
    for (int j = 0; j < 6; j++)
        if (x == Opt[j]) return true;
    return false;
}

void Process(string T) {
    char c = T[0], x;
    if (!InOpt(c)) cout << T << " ";
    else {
        if (c == '(') { st.push(c); return; }
        if (c == ')') {
            do {
                x = st.top();  st.pop();
                if (x != '(') cout << x << " ";
            } while (x != '(');
            return;
        }
        while (st.size() && Priority(c) <= Priority(st.top())) {
                cout << st.top() << " ";
                st.pop();
        }
        st.push(c);
    }
}

int main() {
    freopen("in.txt", "r",stdin);
    gets(Infix);         cout << "RPN: ";
    Infix[strlen(Infix)] = ' ';
    for (int i = 0; i < strlen(Infix); i++)
        if (Infix[i] != ' ') T += Infix[i];
        else {
            Process(T);
            T = "";
        }
    while (st.size()) { cout << st.top() << " "; st.pop(); }
    return 0;
}
