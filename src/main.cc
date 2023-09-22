#include "Grafo.hh"
#include <fstream>
#include <string.h>

int main(int argc, char** argv) {
  std::string fichero_grafo = "Grafo2.txt";
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
    for(int j = i + 1; j < num_vertices; j++) {
      getline(grafo_texto, linea_leida);
      grafo.InsertCost(i,j, atof(linea_leida.c_str()));
      grafo.InsertCost(j, i, atof(linea_leida.c_str()));
    }
  }
  grafo.BusquedaProfundidad(1,5);
  return 0;
}