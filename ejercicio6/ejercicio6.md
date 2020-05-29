# Ejercicio 6

## El juego de la vida

Es posible encontrar una solución paralela del mismo.

Esto se puede lograr de distintas maneras, cada uno con su hoverhead. Por ejemplo:
 - Puede haber un nodo maestro que envíe la información necesaria a cada procesador para resolver el próximo estado de cada célula, que cada procesador puede resolver una fila, columna o cuadrante.
- Otro acercamiento es que cada procesador resuelva por ejemplo una fila y se comunique con las filas vecinas para obtener los valores necesarios para calcular el estado de sus células