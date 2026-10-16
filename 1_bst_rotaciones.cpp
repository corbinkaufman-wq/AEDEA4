#include <iostream>
#include <vector>
using namespace std;

struct Nodo {
    int valor;
    Nodo* izq;
    Nodo* der;
    Nodo(int v) : valor(v), izq(nullptr), der(nullptr) {}
};

Nodo* insertar(Nodo* raiz, int v) {
    if (raiz == nullptr) return new Nodo(v);
    if (v < raiz->valor) raiz->izq = insertar(raiz->izq, v);
    else if (v > raiz->valor) raiz->der = insertar(raiz->der, v);
    return raiz;
}

bool buscar(Nodo* raiz, int v) {
    while (raiz != nullptr) {
        if (v == raiz->valor) return true;
        raiz = (v < raiz->valor) ? raiz->izq : raiz->der;
    }
    return false;
}

int altura(Nodo* raiz) {
    if (raiz == nullptr) return 0;
    int a = altura(raiz->izq);
    int b = altura(raiz->der);
    return 1 + (a > b ? a : b);
}

// x pasa a ser hijo izquierdo de su hijo derecho
Nodo* rotarIzq(Nodo* x) {
    Nodo* y = x->der;
    x->der = y->izq;
    y->izq = x;
    return y;
}

Nodo* rotarDer(Nodo* y) {
    Nodo* x = y->izq;
    y->izq = x->der;
    x->der = y;
    return x;
}

void inorden(Nodo* raiz, vector<int>& salida) {
    if (raiz == nullptr) return;
    inorden(raiz->izq, salida);
    salida.push_back(raiz->valor);
    inorden(raiz->der, salida);
}

void imprimir(Nodo* raiz, int nivel = 0) {
    if (raiz == nullptr) return;
    imprimir(raiz->der, nivel + 1);
    for (int i = 0; i < nivel; i++) cout << "    ";
    cout << raiz->valor << "\n";
    imprimir(raiz->izq, nivel + 1);
}

int main() {
    Nodo* raiz = nullptr;
    vector<int> datos = {1, 2, 3, 4, 5};
    for (int x : datos) raiz = insertar(raiz, x);

    cout << "BST degenerado (insertado en orden), altura = " << altura(raiz) << "\n";
    imprimir(raiz);

    raiz = rotarIzq(raiz);
    raiz->der = rotarIzq(raiz->der);
    cout << "\nDespues de dos rotaciones a la izquierda, altura = " << altura(raiz) << "\n";
    imprimir(raiz);

    vector<int> orden;
    inorden(raiz, orden);
    cout << "\nInorden (sigue ordenado): ";
    for (int x : orden) cout << x << " ";
    cout << "\n";

    cout << "Buscar 4: " << (buscar(raiz, 4) ? "si" : "no") << "\n";
    cout << "Buscar 9: " << (buscar(raiz, 9) ? "si" : "no") << "\n";
    return 0;
}
