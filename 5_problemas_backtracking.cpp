#include <iostream>
#include <vector>
using namespace std;

int movimientos = 0;

void hanoi(int n, char origen, char destino, char aux) {
    if (n == 0) return;
    hanoi(n - 1, origen, aux, destino);
    cout << "Mover disco " << n << " de " << origen << " a " << destino << "\n";
    movimientos++;
    hanoi(n - 1, aux, destino, origen);
}

void parentesis(int n, int abiertos, int cerrados, vector<char>& actual) {
    if ((int)actual.size() == 2 * n) {
        for (char c : actual) cout << c;
        cout << "\n";
        return;
    }
    if (abiertos < n) {
        actual.push_back('(');
        parentesis(n, abiertos + 1, cerrados, actual);
        actual.pop_back();
    }
    if (cerrados < abiertos) {
        actual.push_back(')');
        parentesis(n, abiertos, cerrados + 1, actual);
        actual.pop_back();
    }
}

void hamming(int n, int h, vector<int>& bits, int pos) {
    if (h == 0) {
        for (int b : bits) cout << b;
        cout << "\n";
        return;
    }
    for (int i = pos; i < n; i++) {
        bits[i] = 1;
        hamming(n, h - 1, bits, i + 1);
        bits[i] = 0;
    }
}

bool sePuede(const vector<int>& fila, int col, int f) {
    for (int c = 0; c < col; c++) {
        int dif = fila[c] - f;
        if (dif < 0) dif = -dif;
        if (fila[c] == f || dif == col - c) return false;
    }
    return true;
}

int soluciones = 0;

void reinas(int n, int col, vector<int>& fila) {
    if (col == n) {
        soluciones++;
        if (soluciones == 1) {
            cout << "Primera solucion:\n";
            for (int f = 0; f < n; f++) {
                for (int c = 0; c < n; c++) cout << (fila[c] == f ? "Q " : ". ");
                cout << "\n";
            }
        }
        return;
    }
    for (int f = 0; f < n; f++) {
        if (sePuede(fila, col, f)) {
            fila[col] = f;
            reinas(n, col + 1, fila);
        }
    }
}

int main() {
    cout << "Torres de Hanoi con 3 discos:\n";
    hanoi(3, 'A', 'C', 'B');
    cout << "Total: " << movimientos << " movimientos (2^n - 1)\n";

    cout << "\nParentesis balanceados con n = 3:\n";
    vector<char> actual;
    parentesis(3, 0, 0, actual);

    cout << "\nCadenas de 4 bits con distancia de Hamming 2:\n";
    vector<int> bits(4, 0);
    hamming(4, 2, bits, 0);

    cout << "\n8 reinas:\n";
    vector<int> fila(8, 0);
    reinas(8, 0, fila);
    cout << "Total de soluciones: " << soluciones << "\n";
    return 0;
}
