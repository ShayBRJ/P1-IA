#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <stack>
#include<bits/stdc++.h>

#include "Utils.hh"

struct SIB //Search Information block
{
  std::vector<int> inspeccionados;
  std::vector<int> camino;
  std::vector<int> generados;
  std::string tipo_busqueda;
  unsigned int nodo_origen;
  unsigned int nodo_destino;
  double coste;
};

class Grafo {

public:
  Grafo(int numero_vertices = 0);
  bool InsertCost(unsigned int vertice_i, unsigned int vertice_j, double coste);
  double MostrarCosteArista(int, int);
  int GetNumVertices();
  
  SIB BusquedaProfundidad(int, int);
  SIB BusquedaAmplitud(int, int);

  static Grafo ConstruccionGrafo(std::ifstream& archivo_lectura);

private:
  int num_vertices;
  std::vector<std::vector<double>> Vertices;
  bool AllVisited(std::vector<double> adyacentes, std::vector<bool> nodos_visitados);
  double CosteCamino(std::vector<int> camino);
};

std::ostream& operator<<(std::ostream& out, const SIB& bloque_info);
