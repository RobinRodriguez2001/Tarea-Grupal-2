#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Palabra {
    string palabra;
    string traduccion;
    string funcionalidad;
};

// Función para agregar una nueva palabra al archivo
void agregarPalabra(const Palabra& palabra) {
    ofstream archivo("palabras.txt", ios::app);
    if (archivo.is_open()) {
        archivo << palabra.palabra << "," << palabra.traduccion << "," << palabra.funcionalidad << endl;
        archivo.close();
        cout << "Palabra agregada correctamente." << endl;
    } else {
        cout << "Error al abrir el archivo." << endl;
    }
}

// Función para mostrar todas las palabras almacenadas en el archivo
void mostrarPalabras() {
    ifstream archivo("palabras.txt");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string palabra, traduccion, funcionalidad;
            getline(ss, palabra, ',');
            getline(ss, traduccion, ',');
            getline(ss, funcionalidad, ',');
            cout << "Palabra: " << palabra<<"\n" << "Traduccion: " << traduccion <<"\n"<< "Funcionalidad: " << funcionalidad << "\n\n";
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

// Función para actualizar la información de una palabra en el archivo
void actualizarPalabra(const string& palabraBuscada, const Palabra& nuevaPalabra) {
    vector<Palabra> palabras;
    ifstream archivoEntrada("palabras.txt");
    if (archivoEntrada.is_open()) {
        string linea;
        while (getline(archivoEntrada, linea)) {
		    stringstream ss(linea);
		    string palabra, traduccion, funcionalidad;
		    getline(ss, palabra, ',');
		    getline(ss, traduccion, ',');
		    getline(ss, funcionalidad, ',');
		    if (palabra == palabraBuscada) {
		        // Si encontramos la palabra buscada, agregamos la nueva palabra
		        palabras.push_back(nuevaPalabra);
		    } else {
		        // Si no es la palabra buscada, agregamos la palabra original
		        palabras.push_back({palabra, traduccion, funcionalidad});
		    }
		}
        archivoEntrada.close();

        ofstream archivoSalida("palabras.txt");
        if (archivoSalida.is_open()) {
            for (const auto& palabra : palabras) {
                archivoSalida << palabra.palabra << "," << palabra.traduccion << "," << palabra.funcionalidad << endl;
            }
            archivoSalida.close();
            cout << "Palabra actualizada correctamente." << endl;
        } else {
            cout << "Error al abrir el archivo para escritura." << endl;
        }
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

// Función para eliminar una palabra del archivo
void eliminarPalabra(const string& palabraAEliminar) {
    vector<Palabra> palabras;
    ifstream archivoEntrada("palabras.txt");
    if (archivoEntrada.is_open()) {
        string linea;
        while (getline(archivoEntrada, linea)) {
            stringstream ss(linea);
            string palabra, traduccion, funcionalidad;
            getline(ss, palabra, ',');
            getline(ss, traduccion, ',');
            getline(ss, funcionalidad, ',');
            if (palabra != palabraAEliminar) {
                palabras.push_back({palabra, traduccion, funcionalidad});
            }
        }
        archivoEntrada.close();

        ofstream archivoSalida("palabras.txt");
        if (archivoSalida.is_open()) {
            for (const auto& palabra : palabras) {
                archivoSalida << palabra.palabra << "," << palabra.traduccion << "," << palabra.funcionalidad << endl;
            }
            archivoSalida.close();
            cout << "Palabra eliminada correctamente." << endl;
        } else {
            cout << "Error al abrir el archivo para escritura." << endl;
        }
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }
}

int main() {
    int opcion;
    do {
        cout << "\n\t------ Menu ------" << endl;
        cout << "\t1. Agregar palabra" << endl;
        cout << "\t2. Mostrar palabras" << endl;
        cout << "\t3. Actualizar palabra" << endl;
        cout << "\t4. Eliminar palabra" << endl;
        cout << "\t5. Salir\n\n";
        cout << "\t   Seleccione una opcion: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1: {
            	system("cls");
                Palabra nuevaPalabra;
                fflush(stdin);
                cout << "Ingrese la palabra: ";
                cin >> nuevaPalabra.palabra;
                fflush(stdin);
                cout << "Ingrese la traducción: ";
                cin >> nuevaPalabra.traduccion;
                fflush(stdin);
                cout << "Ingrese la funcionalidad: ";
                cin.ignore(); // Para limpiar el buffer del teclado antes de getline
                getline(cin, nuevaPalabra.funcionalidad);
                agregarPalabra(nuevaPalabra);system("pause");
                system("cls");
                break;
            }
            case 2:
            	system("cls");
                cout << "------ Listado de Palabras ------" << endl;
                mostrarPalabras();
                system("pause");
                system("cls");
                break;
            case 3: {
            	system("cls");
                string palabraBuscada;
                cout << "Ingrese la palabra a actualizar: ";
                cin >> palabraBuscada;
                Palabra nuevaPalabra;
                cout << "Ingrese la nueva palabra: ";
                cin >> nuevaPalabra.palabra;
                cout << "Ingrese la nueva traducción: ";
                cin >> nuevaPalabra.traduccion;
                cout << "Ingrese la nueva funcionalidad: ";
                cin.ignore(); // Para limpiar el buffer del teclado antes de getline
                getline(cin, nuevaPalabra.funcionalidad);
                actualizarPalabra(palabraBuscada, nuevaPalabra);
                system("pause");
                system("cls");
                break;
            }
            case 4: {
            	system("cls");
                string palabraAEliminar;
                cout << "Ingrese la palabra a eliminar: ";
                cin >> palabraAEliminar;
                eliminarPalabra(palabraAEliminar);
                system("pause");
                system("cls");
                break;
            }
            case 5:
            	system("cls");
                cout << "Saliendo del programa..." << endl;
                break;
            default:
            	system("cls");
                cout << "Opción inválida. Por favor, seleccione una opción válida." << endl;
                
        }
    } while (opcion != 5);

    return 0;
}