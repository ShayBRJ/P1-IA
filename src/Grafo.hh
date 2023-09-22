#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <stack>

class Grafo {

public:
  Grafo(int numero_vertices);
  bool InsertCost(int vertice_i, int vertice_j, double coste);
  double Mostrar_Coste_Arista(int, int);
  void BusquedaProfundidad(int, int);

private:
  int num_vertices;
  std::vector<std::vector<double>> Vertices;
};

Grafo::Grafo(int numero_vertices) {
  this->Vertices.resize(numero_vertices);
  this->num_vertices = numero_vertices;
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

void Grafo::BusquedaProfundidad(int origen, int destino) {
  int iterador = 0;
  origen--, destino--;
  std::vector<bool> visitados;
  visitados.resize(this->num_vertices, false);
  std::stack<int> pila;
  std::vector<int> recorrido;
  recorrido.resize(this->num_vertices, -1);
  visitados.at(origen) = true;
  pila.push(origen);
  while(!pila.empty()) {
    auto const& nodo_visitado = pila.top();
    recorrido[iterador] = nodo_visitado;
    iterador++;
    pila.pop();
    auto const& adyacentes = this->Vertices.at(nodo_visitado);
    for(int i = 0; i < adyacentes.size(); i++) {
      if(adyacentes[i] != -1) {
        if(i == destino) {
          recorrido[iterador] = i;
          iterador++;
          visitados.at(i) = true;
          return;
        }
        if(visitados[i] == false) {
          visitados[i] = true;
          pila.push(i);
        }
      }
      
    }
  }
}
