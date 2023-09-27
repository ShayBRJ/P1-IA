#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <stack>

#include "Utils.hh"

struct SIB //Search Information block
{
  std::vector<int> recorrido;
  std::vector<int> camino;
};

class Grafo {

public:
  Grafo(int numero_vertices = 0);
  bool InsertCost(int vertice_i, int vertice_j, double coste);
  double Mostrar_Coste_Arista(int, int);
  int GetNumVertices();
  
  SIB BusquedaProfundidad(int, int);

private:
  int num_vertices;
  std::vector<std::vector<double>> Vertices;
  bool all_visited(std::vector<double> adyacentes, std::vector<bool> nodos_visitados);
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

SIB Grafo::BusquedaProfundidad(int origen, int destino) {
  int iterador = 0;
  if(origen > this->num_vertices || origen < 1) return SIB();
  origen--, destino--;
  std::vector<bool> visitados;
  visitados.resize(this->num_vertices, false);
  std::stack<int> pila;
  std::stack<int> camino_pila;
  SIB bloque_info;
  bloque_info.recorrido.resize(this->num_vertices, -1);
  pila.push(origen);
  while(!pila.empty()) {
    auto const& nodo_visitado = pila.top();
    pila.pop();
    camino_pila.push(nodo_visitado);
    visitados.at(nodo_visitado) = true;
    bloque_info.recorrido[iterador] = nodo_visitado;
    iterador++;
    auto const& adyacentes = this->Vertices.at(nodo_visitado);
    if(nodo_visitado == destino) {
      bloque_info.camino = utils::Stack2Vector(camino_pila);
      return bloque_info;
    }
    while(!camino_pila.empty()){
      if(all_visited(this->Vertices.at(camino_pila.top()), visitados)) camino_pila.pop();
      else break;
    }
    for(int i = 0; i < adyacentes.size(); i++) {
      if(adyacentes[i] != -1) {
        if(visitados[i] == false) {
          pila.push(i);
        }
      }
    }
  }
  return bloque_info;
}

  bool Grafo::all_visited(std::vector<double> adyacentes, std::vector<bool> nodos_visitados) {
    for(int i = 0; i < adyacentes.size(); i++) {
      if(adyacentes[i] >= 0 && nodos_visitados[i] == false) {
        return false;
      }
    }
    return true;
  }
int Grafo::GetNumVertices() {
  return this->num_vertices;
}