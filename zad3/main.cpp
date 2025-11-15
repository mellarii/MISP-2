#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;

    stack<pair<char, int>> stack;

    for (int i = 0; i < (int)s.size(); i++) {
        char simv = s[i];
        if (simv == '(' or simv == '{' or simv == '[') {
            stack.push({simv, i + 1});
        } else if (simv == ')' or simv == '}' or simv == ']') {
            if (stack.empty()) {
                cout << i + 1 << endl;
            }
            
            char first = stack.top().first;
            if ((simv == ')' and first == '(') 
            or (simv == '}' and first == '{') 
            or (simv == ']' and first == '[')) {
                stack.pop();
            }
            
            } 
    }

    if (stack.empty()) {
        cout << "Zaversheno" << endl;
    } else {
        cout << stack.top().second << endl;
    }

    return 0;
}