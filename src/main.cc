#include "../include/Grafo.hh"
#include "../include/Utils.hh"
#include <fstream>
#include <string.h>


void MostrarMenu() {
  std::cout << "\tMENÚ PRINCIPAL\n";
  std::cout << "Opciones: \n";
  std::cout << "1) Seleccionar fichero de lectura\n";
  std::cout << "2) Seleccionar fichero de salida\n";
  std::cout << "3) Busqueda por profundidad\n";
  std::cout << "4) Busqueda por amplitud\n";
  std::cout << "5) Salir\n";

}

void NuevoArchivoLectura(std::ifstream& fichero_lectura, bool& archivo_lectura_abierto) {
  system("clear");
  std::cin.ignore();
  fichero_lectura.close();
  std::string linea_lectura;
  std::cout << "Ingresa el fichero de lectura: ";
  getline(std::cin, linea_lectura);
  fichero_lectura.open(linea_lectura, std::ios_base::in);
  archivo_lectura_abierto = true;
  if(!fichero_lectura.is_open()) {
    std::cout << "El fichero no ha podido abrirse, intentelo de nuevo\n";
    std::getchar();
    archivo_lectura_abierto = false;
  }
}

void NuevoArchivoSalida(std::ofstream& fichero_salida, bool& archivo_salida_abierto) {
  system("clear");
  fichero_salida.close();
  std::cin.ignore();
  std::string linea_lectura;
  std::cout << "Ingresa el fichero de salida: ";
  std::getline(std::cin, linea_lectura);
  fichero_salida.open(linea_lectura, std::ios_base::out);
  archivo_salida_abierto = true;
  if(!fichero_salida.is_open()) {
    std::cout << "El fichero no ha podido crearse, intentelo de nuevo\n";
    archivo_salida_abierto = false;
  }
}

void BusquedaProfundidadOpcion(bool& archivo_lectura_abierto, bool& archivo_salida_abierto, 
                                std::ifstream& fichero_lectura, std::ofstream& fichero_salida) {
  system("clear");
  if(archivo_lectura_abierto != true || archivo_salida_abierto != true) {
    std::cout << "Se necesita un fichero de lectura y salida correcto\n";
    getchar();
    getchar();
    return;
  }
  int nodo_origen, nodo_destino;
  Grafo grafo = Grafo::ConstruccionGrafo(fichero_lectura);
  std::cout << "Indica el nodo (1 - " << grafo.GetNumVertices() << ") de origen: ";
  std::cin >> nodo_origen;
  std::cout << "Indica el nodo (1 - " << grafo.GetNumVertices() << ") de destino: ";
  std::cin >> nodo_destino;
  SIB informacion_salida = grafo.BusquedaProfundidad(nodo_origen, nodo_destino);
  fichero_salida << informacion_salida;
}

void BusquedaAmplitudOpcion(bool& archivo_lectura_abierto, bool& archivo_salida_abierto, 
                                std::ifstream& fichero_lectura, std::ofstream& fichero_salida){
  system("clear");
  if(archivo_lectura_abierto != true || archivo_salida_abierto != true) {
    std::cout << "Se necesita un fichero de lectura y salida correcto\n";
    getchar();
    getchar();
    return;
  }
  int nodo_origen, nodo_destino;
  Grafo grafo = Grafo::ConstruccionGrafo(fichero_lectura);
  std::cout << "Indica el nodo (1 - " << grafo.GetNumVertices() << ") de origen: ";
  std::cin >> nodo_origen;
  std::cout << "Indica el nodo (1 - " << grafo.GetNumVertices() << ") de destino: ";
  std::cin >> nodo_destino;
  SIB informacion_salida = grafo.BusquedaAmplitud(nodo_origen, nodo_destino);
  fichero_salida << informacion_salida;
  
}

int main(int argc, char** argv) {
  int opcion;
  bool archivo_lectura_abierto = false, archivo_salida_abierto = false;
  std::string linea_lectura;  
  std::ifstream fichero_lectura;
  std::ofstream fichero_salida;
  do {
    system("clear");
    MostrarMenu();
    std::cout << "Seleccionar la opcion: ";
    std::cin >> opcion;
    switch (opcion)
    {
    case 1:
      NuevoArchivoLectura(fichero_lectura, archivo_lectura_abierto);
      break;
    case 2:
      NuevoArchivoSalida(fichero_salida, archivo_salida_abierto);
      break;
    case 3:
      BusquedaProfundidadOpcion(archivo_lectura_abierto, archivo_salida_abierto, fichero_lectura, fichero_salida);
    break;
    case 4:
      BusquedaAmplitudOpcion(archivo_lectura_abierto, archivo_salida_abierto, fichero_lectura, fichero_salida);
      break;
    default:
      return 0;
    }
  }while(opcion > 0 && opcion < 6);
  return 0;
}