#include "../include/Grafo.hh"

Grafo::Grafo(int numero_vertices) {
  this->Vertices.resize(numero_vertices);
  this->num_vertices = numero_vertices;
  for(int i = 0; i < numero_vertices; i++) {
    Vertices.at(i).resize(numero_vertices, -1);
  }
}

bool Grafo::InsertCost(unsigned int vertice_i, unsigned int vertice_j, double coste){
  if(vertice_i < 0 && vertice_j < 0 && vertice_i >= this->Vertices.size() && 
      vertice_j >= this->Vertices.size()) {
        return false;
    }
  Vertices[vertice_i][vertice_j] = coste;
  return true;
}

double Grafo::MostrarCosteArista(int i , int j) {
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
  bloque_info.tipo_busqueda = "Búsqueda Profundidad";
  bloque_info.nodo_origen = origen + 1;
  bloque_info.nodo_destino = destino + 1;
  bloque_info.inspeccionados.resize(this->num_vertices, -1);
  bloque_info.generados.resize(this->num_vertices, -1);
  pila.push(origen);
  bloque_info.generados.at(origen) = origen;
  while(!pila.empty()) {
    auto const& nodo_visitado = pila.top();
    pila.pop();
    camino_pila.push(nodo_visitado);
    visitados.at(nodo_visitado) = true;
    bloque_info.inspeccionados[iterador] = nodo_visitado;
    iterador++;
    auto const& adyacentes = this->Vertices.at(nodo_visitado);
    if(nodo_visitado == destino) {
      bloque_info.camino = utils::Stack2Vector(camino_pila);
      bloque_info.coste = this->CosteCamino(bloque_info.camino);
      return bloque_info;
    }
    while(!camino_pila.empty()){
      if(AllVisited(this->Vertices.at(camino_pila.top()), visitados)) camino_pila.pop();
      else break;
    }
    for(unsigned int i = 0; i < adyacentes.size(); i++) {
      if(adyacentes[i] != -1) {
        if(visitados[i] == false) {
          bloque_info.generados.at(i) = i;
          pila.push(i);
        }
      }
    }
  }
  return bloque_info;
}

SIB Grafo::BusquedaAmplitud(int origen, int destino) {
  int iter_inspec = 0;
  if(origen > this->num_vertices || origen < 1) return SIB();
  origen--, destino--;
  std::vector<bool> visitados;
  std::queue<int> cola;
  std::stack<std::pair<int, int>> camino_pila;
  SIB bloque_info;
  bloque_info.tipo_busqueda = "Búsqueda Amplitud";
  bloque_info.nodo_origen = origen + 1;
  bloque_info.nodo_destino = destino + 1;
  visitados.resize(this->num_vertices, false);
  bloque_info.inspeccionados.resize(this->num_vertices, -1);
  bloque_info.generados.resize(this->num_vertices, -1);
  bloque_info.camino.resize(this->num_vertices, -1);
  cola.push(origen);
  visitados.at(origen) = true;
  bloque_info.generados.at(origen) = origen;
  while(!cola.empty()) {
    auto const& nodo_visitado = cola.front();
    cola.pop();
    bloque_info.inspeccionados.at(iter_inspec) = nodo_visitado;
    iter_inspec++;
    if(nodo_visitado == destino) {
      int iterador = 0;
      while(!camino_pila.empty() && camino_pila.top().second != destino) camino_pila.pop();
      while(!camino_pila.empty()) {
        bloque_info.camino.at(iterador) = camino_pila.top().second;
        iterador++;
        int padre = camino_pila.top().first;
        camino_pila.pop();
        while(!camino_pila.empty() && camino_pila.top().second != padre) camino_pila.pop();
      }
      bloque_info.camino.at(iterador) = origen;
      std::reverse(bloque_info.camino.begin(), bloque_info.camino.end());
      bloque_info.coste = CosteCamino(bloque_info.camino);
      return bloque_info;
    }
    auto adyacentes = Vertices.at(nodo_visitado);
    for(unsigned int i = 0; i < adyacentes.size(); i++) {
      if(adyacentes[i] != -1 && visitados.at(i) == false) {
        camino_pila.push(std::make_pair(nodo_visitado, i));
        cola.push(i);
        bloque_info.generados.at(i) = i;
        visitados.at(i) = true;
      }
    }
  }
  return bloque_info;
}


  bool Grafo::AllVisited(std::vector<double> adyacentes, std::vector<bool> nodos_visitados) {
    for(unsigned int i = 0; i < adyacentes.size(); i++) {
      if(adyacentes[i] >= 0 && nodos_visitados[i] == false) {
        return false;
      }
    }
    return true;
  }

int Grafo::GetNumVertices() {
  return this->num_vertices;
}

double Grafo::CosteCamino(std::vector<int> camino) {
  double coste_resultado{0};
  for(unsigned int i = 0; i < camino.size() - 1; i++) {
    if(camino.at(i) < 0) continue;
    coste_resultado += MostrarCosteArista(camino.at(i), camino.at(i + 1));
  }
  return coste_resultado;
}

Grafo Grafo::ConstruccionGrafo(std::ifstream& archivo_lectura) {
  std::string linea_leida;
  getline(archivo_lectura, linea_leida);
  int num_vertices = atoi(linea_leida.c_str());
  Grafo grafo(num_vertices);
  for(int i = 0; i < num_vertices; i++) {
      grafo.InsertCost(i, i, 0);
    for(int j = i + 1; j < num_vertices; j++) {
      getline(archivo_lectura, linea_leida);
      grafo.InsertCost(i,j, atof(linea_leida.c_str()));
      grafo.InsertCost(j, i, atof(linea_leida.c_str()));
    }
  }
    if(grafo.GetNumVertices() <= 0) {
    std::cerr << "El grafo debe contener al menos un nodo\n";
    std::exit(1);
  }
  archivo_lectura.seekg(0);
  return grafo;
}

std::ostream& operator<<(std::ostream& out, const SIB& bloque_info) {
  out << "\t\t\t\t" << bloque_info.tipo_busqueda.c_str() << std::endl;
  out << "Nodo origen: " << bloque_info.nodo_origen << std::endl;
  out << "Nodo destino: " << bloque_info.nodo_destino << std::endl;
  out << "Los nodos inspeccionados son: ";

  for(auto x : bloque_info.inspeccionados) {
    if(x == -1) continue;
    out << x + 1 << " ";
  }
  out << "\n";
  out << "El camino es: ";
  for(auto x : bloque_info.camino) {
  if(x == -1) continue;
    out << "->" << x + 1 << " ";
  }
  out << "\n";
  out << "Los nodos generados son: ";
  for(auto x : bloque_info.generados) {
    if(x == -1) continue;
    out << x + 1 << " ";
  }
  out << "\n";
  out << "El coste de dicho camino es: " << bloque_info.coste << std::endl;
  out << std::endl;
  return out;
}
