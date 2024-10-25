# P02-Stack-Automaton-Complejidad-Computacional
- Diego Rodríguez Martín
- alu0101464992@ull.edu.es

Se ha implementado el Autómata por vaciado de pila.  
**Compilación**: `g++ -o automaton Alphabet/alphabet.cc MyStack/my_stack.cc StackAutomaton/stack_automaton.cc State/state.cc Symbol/symbol.cc Transition/transition.cc main.cc`

**Ejecución**: `./automaton fichero_automata [cadenas] --trace`  
**Ejemplo**: `./automaton APv2.txt 1001 001 0000 0110 --trace`
             `./automaton APv1.txt aabb ab a aaabbb`
Este último parámetro ha de ponerse sólo si se quiere ver la traza.
