#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, string> palabrasTraducidas;

// Función para cargar las palabras y sus traducciones desde el archivo
void cargarTraducciones() {
    ifstream archivo("palabras.txt");
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string palabra, traduccion, funcionalidad;
            getline(ss, palabra, ',');
            getline(ss, traduccion, ',');
            palabrasTraducidas[palabra] = traduccion;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo de traducciones." << endl;
    }
}

// Función para traducir una palabra si está presente en el diccionario
string traducirPalabra(const string& palabra) {
    auto it = palabrasTraducidas.find(palabra);
    if (it != palabrasTraducidas.end()) {
        return it->second;
    } else {
        return palabra;
    }
}

// Función para traducir una línea de código
string traducirLinea(const string& linea) {
    stringstream ss(linea);
    string palabra, traduccion, resultado;
    bool esFuncion = false;
    while (ss >> palabra) {
        if (palabra == "if" || palabra == "else" || palabra == "for" || palabra == "while" || palabra == "do" || palabra == "switch") {
            resultado += traducirPalabra(palabra) + " (";
        } else if (palabra == "int" || palabra == "string" || palabra == "double" || palabra == "float" || palabra == "char" || palabra == "bool") {
            resultado += traducirPalabra(palabra) + " ";
        } else if (palabra == "cin" || palabra == "cout") {
            resultado += traducirPalabra(palabra) + " ";
        } else if (palabra == "{" && !esFuncion) {
            resultado += "inicio ";
        } else if (palabra == "}" && !esFuncion) {
            resultado += "fin ";
        } else if (palabra == "(") {
            esFuncion = true;
            resultado += "(";
        } else if (palabra == ")") {
            esFuncion = false;
            resultado += ")";
        } else {
            resultado += traducirPalabra(palabra) + " ";
        }
    }
    return resultado;
}

int main() {
	
	char letra;
	
	do{
		system("cls");
	    cargarTraducciones();
	
	    cout << "Ingrese el codigo en C++ (presione Ctrl+Z seguido de enter para finalizar):\n\n";
	
	    stringstream ss;
	    ss << cin.rdbuf(); // Lee todo el contenido de cin
	
	    string linea;
	    string codigo = ss.str(); // Convertimos el contenido leído a string
	
	    stringstream codigoStream(codigo);
	    
	    cout<<"\n------------------------------------------------------------\n";
	    cout<<"\nTraduccion del codigo\n\n";
	
	    while (getline(codigoStream, linea)) {
	        cout <<traducirLinea(linea) << endl;
	    }
	    cout<<"\n------------------------------------------------------------\n";
	    cout<<"\nDesea agregar otro codigo?\n";
	    cout<<"S = si	N = no\n";
	    cin>>letra;
	}while(letra == 'S' || letra == 's');
	    

    return 0;
}