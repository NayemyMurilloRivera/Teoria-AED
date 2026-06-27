#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;
/*CHashTable<T,S,F,Z>, donde T es el tipo de dato, S es la estructura de datos donde se almacena 
las colisiones, F es un function-obtject
que contiene a la función de dispersión, y Z es el tamaño de la tabla hash. */
template <typename T>
struct funcion31{
	int operator()(const T& clave , int tamano) const {
		unsigned int i = 0;
		for (char c : clave) {
			i= i * 31 + (unsigned char)c;
		}
		return i % tamano;
	}


};

template <typename T>
struct funcion37 {
	int operator()(const T& clave, int tamano) const {
		unsigned int i = 0;
		for (char c : clave) {
			i = i * 37 + (unsigned char)c;
		}
		return i % tamano;
	}


};

template <typename T>
struct fsuma {
	int operator()(const T& clave, int tamano) const {
		unsigned int i = 0;
		for (char c : clave) {
			i = i + (unsigned char)c;
		}
		return i % tamano;
	}


};


template <typename T, typename S, typename F, int Z   >
class tablahash {
	S table[Z];
	F hashfn;

public:
	void insertar(const T& valor) {
		int idx = hashfn(valor, Z); 
		if (idx < 0) { // si es mas pequeño
			idx = -idx;
		}
		
		
		// esto de aqui solo esta buscando en la funcion que le demos , y lo va aa iterar a la direccion a la que corresponda
		table[idx].push_back(valor); // luego de obtener el iterador , se inserta en esa posicion en la tabla
	}

	bool buscar(const T& valor) {
		int idb = hashfn(valor, Z); 
		if (idb < 0) {
			idb = -idb;
		}// me ayuda a encontrar la cubeta que es donde se almacenan si hay mas colisiones

		for (const T& item : table[idb]) {// es como decir (int =0 ; i< table[idb].size(); i++
			if (item == valor) {
				return true;
			}

		}
		return false;
	}

	void contarcoli() {
		int cont = 0;
		int maxcoli = 0;
		for (int i = 0; i < Z; i++) {
			int n = table[i].size();
			if (n > 1) {
				cont =cont + (n - 1);
				cout << "cubeta[" << i << "] → " << n << " elementos\n";
			}
			if (n > maxcoli) {
				maxcoli = n;
			}
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

	// prueba con funcion31 y tamaño 67
	cout << "► funcion31, tamano 67:\n";
	{
		tablahash<string, list<string>, funcion31<string>, 67> t;
		for (const auto& e : estudiantes) t.insertar(e);
		t.contarcoli();
	}

	// prueba con funcion31 y tamaño 97
	cout << "\n► funcion31, tamano 97:\n";
	{
		tablahash<string, list<string>, funcion31<string>, 97> t;
		for (const auto& e : estudiantes) t.insertar(e);
		t.contarcoli();
	}

	// prueba con fsuma y tamaño 67
	cout << "\n► fsuma, tamano 67:\n";
	{
		tablahash<string, list<string>, fsuma<string>, 67> t;
		for (const auto& e : estudiantes) t.insertar(e);
		t.contarcoli();
	}

	// busqueda O(1)
	cout << "\n► Buscar:\n";
	{
		tablahash<string, list<string>, funcion31<string>, 97> t;
		for (const auto& e : estudiantes) t.insertar(e);
		cout << "Quispe Montes: " << (t.buscar("Quispe Montes") ? "ENCONTRADO" : "no existe") << "\n";
		cout << "Gomez Perez:   " << (t.buscar("Gomez Perez") ? "ENCONTRADO" : "no existe") << "\n";
	}

	return 0;
}
