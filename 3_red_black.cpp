#include <iostream>
#include <vector>
using namespace std;

enum Color { ROJO, NEGRO };

struct Nodo {
    int valor;
    Color color;
    Nodo* izq;
    Nodo* der;
    Nodo* padre;
};

struct ArbolRN {
    Nodo* nil;
    Nodo* raiz;

    ArbolRN() {
        nil = new Nodo{0, NEGRO, nullptr, nullptr, nullptr};
        raiz = nil;
    }

    void rotarIzq(Nodo* x) {
        Nodo* y = x->der;
        x->der = y->izq;
        if (y->izq != nil) y->izq->padre = x;
        y->padre = x->padre;
        if (x->padre == nil) raiz = y;
        else if (x == x->padre->izq) x->padre->izq = y;
        else x->padre->der = y;
        y->izq = x;
        x->padre = y;
    }

    void rotarDer(Nodo* y) {
        Nodo* x = y->izq;
        y->izq = x->der;
        if (x->der != nil) x->der->padre = y;
        x->padre = y->padre;
        if (y->padre == nil) raiz = x;
        else if (y == y->padre->der) y->padre->der = x;
        else y->padre->izq = x;
        x->der = y;
        y->padre = x;
    }

    void insertar(int v) {
        Nodo* z = new Nodo{v, ROJO, nil, nil, nil};
        Nodo* y = nil;
        Nodo* x = raiz;
        while (x != nil) {
            y = x;
            x = (v < x->valor) ? x->izq : x->der;
        }
        z->padre = y;
        if (y == nil) raiz = z;
        else if (v < y->valor) y->izq = z;
        else y->der = z;
        arreglar(z);
    }

    void arreglar(Nodo* z) {
        while (z->padre->color == ROJO) {
            Nodo* abuelo = z->padre->padre;
            if (z->padre == abuelo->izq) {
                Nodo* tio = abuelo->der;
                if (tio->color == ROJO) {          // caso 1: recolorear
                    z->padre->color = NEGRO;
                    tio->color = NEGRO;
                    abuelo->color = ROJO;
                    z = abuelo;
                } else {
                    if (z == z->padre->der) {      // caso 2: triangulo
                        z = z->padre;
                        rotarIzq(z);
                    }
                    z->padre->color = NEGRO;       // caso 3: linea
                    abuelo->color = ROJO;
                    rotarDer(abuelo);
                }
            } else {
                Nodo* tio = abuelo->izq;
                if (tio->color == ROJO) {
                    z->padre->color = NEGRO;
                    tio->color = NEGRO;
                    abuelo->color = ROJO;
                    z = abuelo;
                } else {
                    if (z == z->padre->izq) {
                        z = z->padre;
                        rotarDer(z);
                    }
                    z->padre->color = NEGRO;
                    abuelo->color = ROJO;
                    rotarIzq(abuelo);
                }
            }
        }
        raiz->color = NEGRO;
    }

    int alturaNegra(Nodo* n) {
        if (n == nil) return 1;
        int a = alturaNegra(n->izq);
        int b = alturaNegra(n->der);
        if (a == -1 || b == -1 || a != b) return -1;
        return a + (n->color == NEGRO ? 1 : 0);
    }

    void inorden(Nodo* n, vector<int>& salida) {
        if (n == nil) return;
        inorden(n->izq, salida);
        salida.push_back(n->valor);
        inorden(n->der, salida);
    }

    void imprimir(Nodo* n, int nivel = 0) {
        if (n == nil) return;
        imprimir(n->der, nivel + 1);
        for (int i = 0; i < nivel; i++) cout << "     ";
        cout << n->valor << (n->color == ROJO ? "R" : "N") << "\n";
        imprimir(n->izq, nivel + 1);
    }
};

int main() {
    ArbolRN arbol;
    vector<int> datos = {10, 20, 30, 15, 25, 5, 1};
    for (int x : datos) arbol.insertar(x);

    cout << "Red-Black Tree (R = rojo, N = negro):\n";
    arbol.imprimir(arbol.raiz);

    vector<int> orden;
    arbol.inorden(arbol.raiz, orden);
    cout << "\nInorden: ";
    for (int x : orden) cout << x << " ";

    cout << "\nAltura negra: " << arbol.alturaNegra(arbol.raiz) << "\n";
    return 0;
}
