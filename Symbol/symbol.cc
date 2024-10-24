/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Complejidad Computacional P02
  *
  * @author Diego Rodríguez Martín
  * @since 24-10-2024
  * @brief Implementación de la clase Symbol.
  *
*/

#include "symbol.h"

/**
 * Sobrecarga del operador de inserción para imprimir el símbolo.
 */
std::ostream& operator<<(std::ostream& os, const Symbol& symbol) {
  os << symbol.GetSymbol();
  return os;
}