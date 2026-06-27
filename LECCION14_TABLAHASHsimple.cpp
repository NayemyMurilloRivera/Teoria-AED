#include <iostream>
#include <list>
#include <string>
#include <vector>
using namespace std;

// ── función hash ──────────────────────────────
int hash31(string clave, int tamano) {
    unsigned int h = 0;
    for (char c : clave) h = h * 31 + (unsigned char)c;
    return h % tamano;
}

int hash37(string clave, int tamano) {
    unsigned int h = 0;
    for (char c : clave) h = h * 37 + (unsigned char)c;
    return h % tamano;
}

int hashSuma(string clave, int tamano) {
    unsigned int h = 0;
    for (char c : clave) h = h + (unsigned char)c;
    return h % tamano;
}

// ── tabla hash ────────────────────────────────
class tablahash {
    list<string> table[101];  // tamaño máximo que usaremos
    int tamano;
    int (*hashfn)(string, int);  // puntero a la función hash

public:
    tablahash(int tam, int (*fn)(string, int)) {
        tamano = tam;
        hashfn = fn;
    }

    void insertar(string valor) {
        int idx = hashfn(valor, tamano);
        table[idx].push_back(valor);
    }

    bool buscar(string valor) {
        int idx = hashfn(valor, tamano);
        for (const string& item : table[idx]) {
            if (item == valor) return true;
        }
        return false;
    }

    void contarcoli() {
        int cont = 0;
        int maxcoli = 0;
        for (int i = 0; i < tamano; i++) {
            int n = table[i].size();
            if (n > 1) {
                cont = cont + (n - 1);
                cout << "cubeta[" << i << "] → " << n << " elementos\n";
            }
            if (n > maxcoli) maxcoli = n;
        }
        cout << "Total colisiones : " << cont << "\n";
        cout << "Max en una cubeta: " << maxcoli << "\n";
    }
};

int main() {
    vector<string> estudiantes = {
        "Andrade Rios", "Apaza Calizaya", "Baca Flores", "Barreros Rodriguez",
        "Benique Huaman", "Bravo Rivera", "Bustamante Mamani", "Cama Choque",
        "Camaña Champi", "Carrera Alfaro", "Conchacalla Quispe", "Concha Castro",
        "Cruz Ponce", "Failoc Castro", "Farfan Begazo", "Gonzales Begazo",
        "Huaman Amanqui", "Lajo Atayupanqui", "Loayza Paucar", "Luna Carpio",
        "Mansilla Lujan", "Mazza Cordova", "Medina Chino", "Mendoza Maque",
        "Mollapaza Apaza", "Murillo Rivera", "Paredes Hallasi", "Patiño Delgado",
        "Payehuanca Diaz", "Perez Flores", "Perez Vega", "Pino Charun",
        "Ponce Molina", "Prado Manrique", "Pumacayo Gonzales", "Quispe Montes",
        "Revilla Calderon", "Rocha Alvis", "Rodriguez Vilcapaza", "Rosas Lipa",
        "Rospigliosi Escalante", "Salazar Guillen", "Sana Flores", "Saravia Apaza",
        "Sierra Huaracha", "Stelman Melo", "Vargas Llerena", "Villachica Cuentas",
        "Villacis Espinoza", "Villagomez Iquira", "Virrueta Marquez"
    };

    // prueba hash31 tamaño 67
    cout << "► hash31, tamaño 67:\n";
    {
        tablahash t(67, hash31);
        for (const auto& e : estudiantes) t.insertar(e);
        t.contarcoli();
    }

    // prueba hash31 tamaño 97
    cout << "\n► hash31, tamaño 97:\n";
    {
        tablahash t(97, hash31);
        for (const auto& e : estudiantes) t.insertar(e);
        t.contarcoli();
    }

    // prueba hashSuma tamaño 67
    cout << "\n► hashSuma, tamaño 67:\n";
    {
        tablahash t(67, hashSuma);
        for (const auto& e : estudiantes) t.insertar(e);
        t.contarcoli();
    }

    // busqueda
    cout << "\n► Buscar con hash31 tamaño 97:\n";
    {
        tablahash t(97, hash31);
        for (const auto& e : estudiantes) t.insertar(e);
        cout << "Quispe Montes: " << (t.buscar("Quispe Montes") ? "ENCONTRADO" : "no existe") << "\n";
        cout << "Gomez Perez:   " << (t.buscar("Gomez Perez")   ? "ENCONTRADO" : "no existe") << "\n";
    }

    return 0;
}
