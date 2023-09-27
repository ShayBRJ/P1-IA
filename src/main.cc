#include "../include/Grafo.hh"
#include "../include/Utils.hh"
#include <fstream>
#include <string.h>

int main(int argc, char** argv) {
  if(argc != 2) {
    std::cout << "Se necesita un fichero que contenga el grafo a analizar\n";
    return 1;
  }
  std::string fichero_grafo = argv[1];
  std::ifstream grafo_texto(fichero_grafo, std::ios_base::in);
  if(!grafo_texto.is_open()) {
    std::cerr << "El fichero no se encuentra disponible para su lectura." << std::endl;
    return 1;
  }
  std::string linea_leida;
  getline(grafo_texto, linea_leida);
  int num_vertices = atoi(linea_leida.c_str());
  Grafo grafo(num_vertices);
  for(int i = 0; i < num_vertices; i++) {
      grafo.InsertCost(i, i, 0);
    for(int j = i + 1; j < num_vertices; j++) {
      getline(grafo_texto, linea_leida);
      grafo.InsertCost(i,j, atof(linea_leida.c_str()));
      grafo.InsertCost(j, i, atof(linea_leida.c_str()));
    }
  }
  if(grafo.GetNumVertices() <= 0) {
    std::cerr << "El grafo debe contener al menos un nodo\n";
    return 1;
  }
  int nodo_origen, nodo_destino;
  std::cout << "Indica el nodo (1 - " << grafo.GetNumVertices() << ") de origen: ";
  std::cin >> nodo_origen;
  std::cout << "Indica el nodo (1 - " << grafo.GetNumVertices() << ") de destino: ";
  std::cin >> nodo_destino;
  
  std::cout << "El recorrido es: ";
    for(auto x : grafo.BusquedaProfundidad(nodo_origen, nodo_destino).recorrido) {
      if(x == -1) continue;
      std::cout << x + 1 << " ";
    }
    std::cout << "\n";
    std::cout << "El camino es: ";
    for(auto x : grafo.BusquedaProfundidad(nodo_origen, nodo_destino).camino) {
      if(x == -1) continue;
      std::cout << x + 1 << " ";
    }
    std::cout << "\n";
    
  return 0;
}