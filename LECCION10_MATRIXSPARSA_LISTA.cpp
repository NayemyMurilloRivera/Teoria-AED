
#include <iostream>
using namespace std;

struct nodito {
    int valor;
    int columna;
    int fil;
    nodito* next;
    nodito(int row, int col, int v) {
        valor = v;
        columna = col;
        fil = row;
        next = nullptr;

    }
};

class sparsa {
public:
    int col;
    int fil;

    nodito* head;
    sparsa(int coll, int fill) {
        head = nullptr;
        col = coll;
        fil = fill;
    }

    bool findx(int x, int y, nodito*& h);

    // contruccion del get , set , findx , find y
    int get(int x, int y);// porque aqui solo busca no? me lo pide y yo devulvo algo numerico
    void set(int x, int y, int v);
    void insert(int x, int y, int v);
    void remove(int x, int y);
    int& operator()(int x , int y);

};



int& sparsa::operator()(int x, int y) {
    static int invalido = -1111;
    if (x < 0 || x >= fil || y < 0 || y >= col) {
        cout << "Fuera de rango:-";
        return invalido;
    }
    nodito* h = nullptr;
    if (findx(x, y, h)) {
        return h->valor;
    }
    //H==NULLPTR
    static int  cero = 0;
    return cero;

}
int sparsa::get(int x, int y) {
    if (x < 0 || x >= fil || y < 0 || y >= col) {
        cout << "Fuera de rango en get " << endl;
        return 0;
    }
    nodito* h = nullptr;
    if (findx(x, y, h)) {
        return h->valor; // devuelve el valor nada mas
    }
    return 0;// 0 pe
}


void sparsa::set(int x, int y, int v) {
    if (x < 0 || x >= fil || y < 0 || y >= col) {
        cout << "Fuera de rango en set " << endl;
        return;
    }
    nodito* h = nullptr;
    if (findx(x, y, h)) {
        if (v == 0) {
            remove(x, y);
        }
        else {
            h->valor = v;
        }
    }
    else {
        insert(x, y, v);
    }
}




void sparsa::remove(int x, int y) {
    if (x < 0 || x >= fil || y < 0 || y >= col) {
        cout << "Fuera de rango";
        return;
    }
    nodito* h = nullptr;
    if (!findx(x, y, h)) { // si false= no lo encontro = no hay nada que eliminar;
        return;
    }
    // lo encontre , necesito una direccion de memoria 

    nodito* prev = nullptr;
    nodito* aux = head;

    for (; aux != nullptr && !(aux->fil == x && aux->columna == y); aux = aux->next) {
        prev = aux;
    }
    if (aux == nullptr) {
        return;
    }
    if (prev == nullptr) {
        head = aux->next;
    }
    else {
        prev->next = aux->next;

    }
    delete aux;
}


void sparsa::insert(int x, int y, int v) {

    if (x < 0 || x >= fil || y < 0 || y >= col) {
        cout << "Fuera de rango";
        return;
    }
    nodito* h = nullptr;

    // la vida de h , es solo para saber si en find este regresa o no si h regresa es decir con false no hay nada 
    if (findx(x, y, h)) { // si TRUE = lo encontró = ya existe = no insertes
        return;
    }


    //no existe en h
    nodito* nuevo = new nodito(x, y, v); // otro puntero otro nodo, no se ni donde esta
    nuevo->next = head; //head->[0.2]->nullptr ----- nuevo->[0.2]->null
    head = nuevo; // la cabeza donde quedaria  head->nuevo[0.1]->[0.2]->null
}



// en este caso solo deberia poner la de la de x para la lista simple con solo una lista , findx basta
bool sparsa::findx(int x, int y, nodito*& h) { // el nodito * referencia es porque quiero cambiar el valor dentro de este?
    if (x < 0 || x >= fil || y < 0 || y >= col) {
        cout << "Fuera de rango";
        return false;
    }
    nodito* aux = head;
    for (; aux != nullptr && !(aux->fil == x && aux->columna == y); aux = aux->next);
    if (aux != nullptr) { //aux siendo nullptr significa "caminé por toda la lista y no encontré el nodo que buscaba".
        h = aux;
        return true;
    }
    return false;
}

int main() {
    sparsa s(4, 4);

    s.set(1, 2, 3);
    s.set(0, 0, 7);
    s.set(3, 3, 5);

    cout << s.get(1, 2) << "\n";  // 3
    cout << s.get(0, 0) << "\n";  // 7
    cout << s.get(2, 2) << "\n";  // 0 - no existe

    s.set(1, 2, 0);               // debería eliminarlo
    cout << s.get(1, 2) << "\n";  // 0 - fue eliminado

    s.set(5, 5, 9);               // fuera de rango
    cout << s(3, 3) << "\n";  // 5
    cout << s(0, 1) << "\n";  // 0 - no existe
    cout << s(5,5) << "\n"; 
}
