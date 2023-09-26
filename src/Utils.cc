#include "Utils.hh"

std::vector<int> utils::Stack2Vector(std::stack<int> pila) {
  std::vector<int> vector_resultado(pila.size());
  for(int i = pila.size() - 1; i >= 0; i--) {
    vector_resultado[i] = pila.top();
    pila.pop();
  }
  return vector_resultado;
}
