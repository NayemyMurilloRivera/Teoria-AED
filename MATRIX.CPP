
#include <iostream>
using namespace std;

struct nodito {
    int valor;
    int columna;
    int fil;
    nodito* next;
    nodito(int v, int row, int col) {
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
    int& operator[](int valor);
      
};



int& sparsa::operator[](int valor) {



}
int sparsa::get(int x, int y) {
    nodito* h = nullptr;
    if (findx(x, y, h)) {
        return h->valor; // devuelve el valor nada mas
    }
    return 0;// 0 pe
}

void sparsa::remove(int x, int y) {
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
        prev->next = head->next;

    }
    delete aux;
}


void sparsa::insert(int x, int y, int v) {
    nodito* h = nullptr;

     // la vida de h , es solo para saber si en find este regresa o no si h regresa es decir con false no hay nada 
    if (findx(x, y, h)) { // si TRUE = lo encontró = ya existe = no insertes
        return;
    }
    //no existe en h
    nodito* nuevo = new nodito(x,y,v); // otro puntero otro nodo, no se ni donde esta
    nuevo->next = head; //head->[0.2]->nullptr ----- nuevo->[0.2]->null
    head = nuevo; // la cabeza donde quedaria  head->nuevo[0.1]->[0.2]->null
}



// en este caso solo deberia poner la de la de x para la lista simple con solo una lista , findx basta
bool sparsa:: findx(int x, int y, nodito*& h) { // el nodito * referencia es porque quiero cambiar el valor dentro de este?
    nodito* aux = head;
    for (; aux != nullptr && !(aux->fil == x && aux->columna == y); aux = aux->next);
    if (aux != nullptr) { //aux siendo nullptr significa "caminé por toda la lista y no encontré el nodo que buscaba".
        h = aux;
        return true;
    }
    return false;
}

int sparsa:: get(int x, int y) { // es me devuelve no?

}

void sparsa::set(int x, int y, int v) {


}
int main()
{
    

}
