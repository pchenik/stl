#include <iostream>
#include "vector.h"

using namespace std;

typedef pair<int, int> pii;

bool cmp(const pii& a, const pii& b) {
    return a.first > b.first || a.first == b.first && a.second > b.second;
}

int main() {
    Vector<int> a;
    a.push_back(1);
    a.push_back(2);
    for (size_t i = 0; i < a.size(); ++i)
        cout << a[i] << endl;
    a = {1, 2, 3};
    for (size_t i = 0; i < a.size(); ++i)
        cout << a[i] << endl;
    cout << a.back() << endl;
    a.pop_back();
    a.push_back(123);
    cout << a.back() << endl;
    Vector<pii> b(4, make_pair(1, 2));
    for (size_t i = 0; i < b.size(); ++i)
        cout << b[i].first << " " << b[i].second << endl;
    b.clear();
    b = {make_pair(1, 2), make_pair(3, 4), make_pair(1, 8), make_pair(3, 5)};
    cout << b.minimum(cmp).second << endl;
    return 0;
}
