/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Complejidad Computacional P02
  *
  * @author Diego Rodríguez Martín
  * @since 24-10-2024
  * @brief Implementación de la clase Transition.
  *
*/

#include "transition.h"

/**
 * Sobrecarga del operador de inserción
 */
std::ostream& operator<<(std::ostream& os, const Transition& transition) {
  os << transition.GetFromState() << " " << transition.GetStringSymbol() << " " << transition.GetStackSymbol() << " " << transition.GetToState() << " ";
  for (Symbol symbol : transition.GetAddToStack()) {
    os << symbol;
  }
  return os;
}