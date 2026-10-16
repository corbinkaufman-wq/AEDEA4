#include <iostream>
#include <vector>
using namespace std;

int factorial(int n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

int fibonacci(int n) {
    if (n < 2) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void mostrar(const vector<int>& v) {
    cout << "{ ";
    for (int x : v) cout << x << " ";
    cout << "}\n";
}

void subconjuntos(const vector<int>& datos, int i, vector<int>& actual) {
    if (i == (int)datos.size()) {
        mostrar(actual);
        return;
    }
    subconjuntos(datos, i + 1, actual);   // no lo tomo
    actual.push_back(datos[i]);
    subconjuntos(datos, i + 1, actual);   // lo tomo
    actual.pop_back();
}

void permutaciones(const vector<int>& datos, vector<bool>& usado, vector<int>& actual) {
    if (actual.size() == datos.size()) {
        mostrar(actual);
        return;
    }
    for (int i = 0; i < (int)datos.size(); i++) {
        if (usado[i]) continue;
        usado[i] = true;
        actual.push_back(datos[i]);
        permutaciones(datos, usado, actual);
        actual.pop_back();
        usado[i] = false;
    }
}

void combinaciones(int n, int k, int desde, vector<int>& actual) {
    if ((int)actual.size() == k) {
        mostrar(actual);
        return;
    }
    for (int i = desde; i <= n; i++) {
        if (n - i + 1 < k - (int)actual.size()) break;   // poda: ya no alcanzan
        actual.push_back(i);
        combinaciones(n, k, i + 1, actual);
        actual.pop_back();
    }
}

int main() {
    cout << "5! = " << factorial(5) << "\n";
    cout << "fib(10) = " << fibonacci(10) << "\n";

    vector<int> datos = {1, 2, 3};
    vector<int> actual;

    cout << "\nSubconjuntos de {1,2,3} (2^n):\n";
    subconjuntos(datos, 0, actual);

    cout << "\nPermutaciones de {1,2,3} (n!):\n";
    vector<bool> usado(datos.size(), false);
    permutaciones(datos, usado, actual);

    cout << "\nCombinaciones C(4,2):\n";
    combinaciones(4, 2, 1, actual);
    return 0;
}
