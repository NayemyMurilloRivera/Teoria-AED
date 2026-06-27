// implementacion del proxy para el operator 

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


struct proxy;
class sparsa;


class sparsa {
public:
    int col;
    int fil;
    nodito** heads;
    sparsa(int coll, int fill) {
        col = coll;
        fil = fill;
        heads = new nodito * [fil];
        for (int i = 0; i < fil; i++) {
            heads[i] = nullptr;
        }
    };

    bool findx(int x, int y, nodito**& h);
    int get(int x, int y);// porque aqui solo busca no? me lo pide y yo devulvo algo numerico
    void set(int x, int y, int v);
    void insert(int x, int y, int v);
    void remove(int x, int y);
    proxy operator()(int x, int y);

};

struct proxy {
    int x;
    int y;
    // la idea central de este proxy es 

    /*s(1,2)
        ↓
    proxy
        ↓
    operator=(30) // get solo return get
        ↓
    m.set(1,2,30)  */


    sparsa& m;
    proxy(int x1, int y1, sparsa& matriz) :m(matriz) {
        x = x1;
        y = y1;

    }

    operator int() {
        return m.get(x, y);
    }


    proxy& operator=(int v) {
        m.set(x, y, v);
        return *this;

    }



};
proxy sparsa::operator()(int x, int y) {
    return proxy(x, y, *this); //*this = el objeto real (sparsa&)
}

int sparsa::get(int x, int y) {
    if (x < 0 || x >= fil || y < 0 || y >= col) {
        cout << "Fuera de rango en get " << endl;
        return 0;
    }
    nodito** h = &heads[x];

    if (findx(x, y, h)) {
        return (*h)->valor; // devuelve el valor nada mas
    }
    return 0;// 0 pe
}



void sparsa::set(int x, int y, int v) {
    if (x < 0 || x >= fil || y < 0 || y >= col) {
        cout << "Fuera de rango en set " << endl;
        return;
    }
    nodito** h = &heads[x];
    if (findx(x, y, h)) {
        if (v == 0) {
            remove(x, y);
        }
        else {
            (*h)->valor = v;
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

    nodito** h = &heads[x];// findx!=true
    if (!findx(x, y, h)) { // si false= no lo encontro = no hay nada que eliminar;
        return;
    }
    // lo encontre , necesito una direccion de memoria 
    nodito* todelete = *h;
    *h = (*h)->next;
    delete todelete;

}

void sparsa::insert(int x, int y, int v) {

    if (x < 0 || x >= fil || y < 0 || y >= col) {
        cout << "Fuera de rango";
        return;
    }

    nodito** h = &heads[x];

    // la vida de h , es solo para saber si en find este regresa o no si h regresa es decir con false no hay nada 
    if (findx(x, y, h)) { // si TRUE = lo encontró = ya existe = no insertes
        return;
    }
    // donde deberia estar h
    nodito* nuevo = new nodito(x, y, v);  // 
    nuevo->next = heads[x];
    heads[x] = nuevo;


}

// en este caso solo deberia poner la de la de x para la lista simple con solo una lista , findx basta
bool sparsa::findx(int x, int y, nodito**& h) { // el nodito * referencia es porque quiero cambiar el valor dentro de este?
    if (x < 0 || x >= fil || y < 0 || y >= col) {
        cout << "Fuera de rango";
        return false;
    }
    nodito** aux = &heads[x];
    for (; (*aux) && !((*aux)->fil == x && (*aux)->columna == y); aux = &((*aux)->next));
    // **heads , 
    // !aux === aux!=nullptr  

    if (!*aux) {
        return false;
    }
    h = aux;
    return true;
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
    cout << s(5, 5) << "\n";
}

