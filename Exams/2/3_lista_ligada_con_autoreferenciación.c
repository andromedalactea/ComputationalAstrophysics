/*
  Programa de Lista Ligada en C
  
  Este programa demuestra la implementación de una lista ligada simple
  Una lista ligada es una estructura de datos compuesta por nodos que se enlazan mediante punteros.
  Cada nodo contiene dos partes:
    1. 'data': un entero que almacena el valor del nodo.
    2. 'next': un puntero al siguiente nodo en la lista.
  
  Funcionalidades del programa:
    - Crear nuevos nodos.
    - Agregar nodos al final de la lista.
    - Imprimir todos los nodos presentes en la lista.
    - Liberar la memoria utilizada por la lista ligada.
  
  El programa empieza con una lista vacía y agrega nodos con valores enteros.
  Después de añadir los nodos, el contenido de la lista se muestra en la pantalla.
  Finalmente, antes de terminar, el programa libera la memoria asignada a la lista ligada
  para asegurar una gestión de memoria adecuada.
 */

// Librerías utilizadas en el programa
#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura de un nodo para una lista ligada
typedef struct Node {
    int data;                // Campo de datos donde se guarda el valor del nodo
    struct Node *next;       // Puntero al siguiente nodo en la lista ligada
} Node;

// Prototipos de funciones
Node* createNode(int data);
void appendNode(Node **head, int data);
void printList(Node *node);
void freeList(Node *node);

// Función principal del programa
int main() {
    Node *head = NULL; // Inicializa la cabeza de la lista ligada como NULL

    // Agregando elementos a la lista
    appendNode(&head, 10);
    appendNode(&head, 20);
    appendNode(&head, 30);
    appendNode(&head, 40);

    // Mostrando la lista
    printf("La lista ligada contiene: \n");
    printList(head); // Imprime todos los nodos de la lista

    // Liberando la memoria de la lista
    freeList(head); // Libera toda la memoria utilizada por la lista

    return 0; // Termina la ejecución del programa
}

// Función para crear un nuevo nodo
Node* createNode(int data) {
    // Solicita memoria para un nuevo nodo
    Node* newNode = (Node*) malloc(sizeof(Node));
    // Verifica si la memoria fue asignada correctamente
    if (newNode == NULL) {
        fprintf(stderr, "Error en la alocación de memoria\n"); // Imprime un mensaje de error si no hay memoria
        exit(EXIT_FAILURE); // Sale del programa indicando que hubo un fallo
    }
    newNode->data = data; // Asigna el valor del dato al nodo
    newNode->next = NULL; // Inicializa el puntero al siguiente nodo como NULL
    return newNode; // Retorna el puntero al nuevo nodo creado
}

// Función para agregar un nodo al final de la lista ligada
void appendNode(Node **head, int data) {
    Node* newNode = createNode(data); // Crea un nuevo nodo con el dato proporcionado
    if (*head == NULL) { // Verifica si la lista está vacía
        *head = newNode; // Establece el nuevo nodo como la cabeza de la lista
    } else {
        Node *current = *head; // Inicia un puntero para recorrer la lista desde la cabeza
        while (current->next != NULL) { // Recorre la lista hasta llegar al último nodo
            current = current->next;
        }
        current->next = newNode; // Conecta el último nodo de la lista al nuevo nodo
    }
}

// Función para imprimir todos los nodos en la lista ligada
void printList(Node *node) {
    while (node != NULL) { // Recorre cada nodo en la lista
        printf("%d -> ", node->data); // Imprime el valor del nodo actual
        node = node->next; // Avanza al siguiente nodo
    }
    printf("NULL\n"); // Indica el final de la lista ligada
}

// Función para liberar la memoria de la lista ligada
void freeList(Node *node) {
    Node *tmp; // Crea un puntero temporal para ayudar en la liberación
    while (node != NULL) { // Recorre todos los nodos de la lista
        tmp = node; // Guarda el nodo actual en temporal
        node = node->next; // Avanza al siguiente nodo
        free(tmp); // Libera la memoria del nodo temporal
    }
}
