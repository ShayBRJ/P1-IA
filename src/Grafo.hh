#pragma once
#include <iostream>
#include <vector>
#include <sstream>

class Grafo {

public:
  Grafo(int numero_vertices);
  bool InsertCost(int vertice_i, int vertice_j, double coste);
  double Mostrar_Coste_Arista(int, int);

private:
  std::vector<std::vector<double>> Vertices;
};

Grafo::Grafo(int numero_vertices) {
  this->Vertices.resize(numero_vertices);
  for(int i = 0; i < numero_vertices; i++) {
    Vertices.at(i).resize(numero_vertices, -1);
  }
}

bool Grafo::InsertCost(int vertice_i, int vertice_j, double coste){
  if(vertice_i < 0 && vertice_j < 0 && vertice_i >= this->Vertices.size() && 
      vertice_j >= this->Vertices.size()) {
        return false;
    }
  Vertices[vertice_i][vertice_j] = coste;
  return true;
}

double Grafo::Mostrar_Coste_Arista(int i , int j) {
  return this->Vertices[i][j];
}
