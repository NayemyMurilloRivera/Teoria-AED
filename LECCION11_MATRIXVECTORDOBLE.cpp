
#include <iostream>
using namespace std;

struct nodito {
    int valor;
    int columna;
    int fil;
    nodito* nextfila;
    nodito* nextcol;

    nodito(int row, int col, int v) {
        valor = v;
        columna = col;
        fil = row;
        nextfila = nullptr;
        nextcol = nullptr;


    }
};


struct proxy;
class sparsa;


class sparsa {
public:
    int col;
    int fil;
    nodito** headsx;
    nodito** headsy;
    sparsa(int coll, int fill) {
        col = coll;
        fil = fill;
        headsx = new nodito * [fil];
        headsy = new nodito * [coll];
        for (int i = 0; i < fil; i++) {
            headsx[i] = nullptr;
        }
        for (int j = 0; j < fil; j++) {
            headsy[j] = nullptr;
        }
    };

    bool findx(int x, int y, nodito**& h);
    bool findy(int x, int y, nodito**& h1);
    int get(int x, int y);// porque aqui solo busca no? me lo pide y yo devulvo algo numerico
    void set(int x, int y, int v);
    void insert(int x, int y, int v);
    void remove(int x, int y);
    proxy operator()(int x, int y);


};

struct proxy {
    int x;
    int y;
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
    nodito** h = &headsx[x];

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
    nodito** h = &headsx[x];
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

    nodito** h = &headsx[x];// findx!=true
    nodito** h1 = &headsy[y];
    if (!findx(x, y, h)) { // si false= no lo encontro = no hay nada que eliminar;
        return;
    }


    nodito* todelete = *h;
    //nodito* todelete2 = *h;
    *h = todelete->nextfila;
    nodito** aux = h1;

    for (; *aux && (*aux) != todelete; aux = &(*aux)->nextcol);
    if (*aux) { // aux ==nullptr;
        return;

    }
    *aux = todelete->nextcol;
    delete todelete;

}

void sparsa::insert(int x, int y, int v) {

    if (x < 0 || x >= fil || y < 0 || y >= col) {
        cout << "Fuera de rango";
        return;
    }

    nodito** h = &headsx[x];
    nodito** h1= &headsy[y];

    if (findx(x, y, h)) {
        return;
    }
    nodito* nuevo = new nodito(x,y,v);
  
    nuevo->nextfila = headsx[x];
    headsx[x] = nuevo;
    
    nuevo->nextcol = headsy[y];
    headsy[y] = nuevo;



}

bool sparsa::findx(int x, int y, nodito**& h) { // el nodito * referencia es porque quiero cambiar el valor dentro de este?
    if (x < 0 || x >= fil || y < 0 || y >= col) {
        cout << "Fuera de rango";
        return false;
    }
    nodito** aux = &headsx[x];
    for (; (*aux) &&  !((*aux)->columna == y); aux = &((*aux)->nextfila));
    // **heads , 
    // !aux === aux==nullptr;

    if (!*aux) {
        return false;
    }
    h = aux;
    return true;
}


bool sparsa::findy(int x, int y, nodito**& h1) { // el nodito * referencia es porque quiero cambiar el valor dentro de este?
    if (x < 0 || x >= fil || y < 0 || y >= col) {
        cout << "Fuera de rango";
        return false;
    }
    nodito** aux = &headsy[y];
    for (; (*aux) && !((*aux)->fil == x); aux = &((*aux)->nextcol));
    // **heads , 
    

    if (!*aux) {
        return false;
    }
    h1 = aux;
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
