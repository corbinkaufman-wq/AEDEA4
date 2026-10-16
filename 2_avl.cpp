#include <iostream>
#include <vector>
using namespace std;

struct Nodo {
    int valor;
    int alto;
    Nodo* izq;
    Nodo* der;
    Nodo(int v) : valor(v), alto(1), izq(nullptr), der(nullptr) {}
};

int alto(Nodo* n) {
    return n == nullptr ? 0 : n->alto;
}

int mayor(int a, int b) {
    return a > b ? a : b;
}

void actualizar(Nodo* n) {
    n->alto = 1 + mayor(alto(n->izq), alto(n->der));
}

int balance(Nodo* n) {
    return alto(n->izq) - alto(n->der);
}

Nodo* rotarDer(Nodo* y) {
    Nodo* x = y->izq;
    y->izq = x->der;
    x->der = y;
    actualizar(y);
    actualizar(x);
    return x;
}

Nodo* rotarIzq(Nodo* x) {
    Nodo* y = x->der;
    x->der = y->izq;
    y->izq = x;
    actualizar(x);
    actualizar(y);
    return y;
}

Nodo* rebalancear(Nodo* n) {
    actualizar(n);
    int b = balance(n);

    if (b > 1) {
        if (balance(n->izq) < 0) n->izq = rotarIzq(n->izq);  // caso LR
        return rotarDer(n);                                  // caso LL
    }
    if (b < -1) {
        if (balance(n->der) > 0) n->der = rotarDer(n->der);  // caso RL
        return rotarIzq(n);                                  // caso RR
    }
    return n;
}

Nodo* insertar(Nodo* n, int v) {
    if (n == nullptr) return new Nodo(v);
    if (v < n->valor) n->izq = insertar(n->izq, v);
    else if (v > n->valor) n->der = insertar(n->der, v);
    else return n;
    return rebalancear(n);
}

Nodo* minimo(Nodo* n) {
    while (n->izq != nullptr) n = n->izq;
    return n;
}

Nodo* borrar(Nodo* n, int v) {
    if (n == nullptr) return nullptr;
    if (v < n->valor) n->izq = borrar(n->izq, v);
    else if (v > n->valor) n->der = borrar(n->der, v);
    else {
        if (n->izq == nullptr || n->der == nullptr) {
            Nodo* hijo = (n->izq != nullptr) ? n->izq : n->der;
            delete n;
            return hijo;
        }
        Nodo* sucesor = minimo(n->der);
        n->valor = sucesor->valor;
        n->der = borrar(n->der, sucesor->valor);
    }
    return rebalancear(n);
}

void imprimir(Nodo* n, int nivel = 0) {
    if (n == nullptr) return;
    imprimir(n->der, nivel + 1);
    for (int i = 0; i < nivel; i++) cout << "      ";
    cout << n->valor << "(h" << n->alto << ")\n";
    imprimir(n->izq, nivel + 1);
}

int main() {
    Nodo* raiz = nullptr;
    vector<int> datos = {10, 20, 30, 40, 50, 25};

    for (int x : datos) {
        raiz = insertar(raiz, x);
        cout << "Inserto " << x << " -> raiz = " << raiz->valor
             << ", altura = " << alto(raiz) << "\n";
    }

    cout << "\nArbol AVL final:\n";
    imprimir(raiz);

    raiz = borrar(raiz, 40);
    cout << "\nDespues de borrar 40:\n";
    imprimir(raiz);
    return 0;
}
