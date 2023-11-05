#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
    int size;
} LinkedList;

LinkedList *createEmptyList() {
    LinkedList *newList = (LinkedList *)malloc(sizeof(LinkedList));
    if (newList == NULL) {
        printf("Erro ao alocar memória para a lista. \n");
        exit(1);
    }
    newList->head = NULL;
    newList->size = 0;
    return newList;
}

void insertAtPosition(LinkedList *list, int position, Node *node) {
    if (position < 0 || position > list->size) {
        printf("Posicao invalida.\n");
        return;
    }
    if (position == 0) {
        node->next = list->head;
        list->head = node;
    } else {
        Node *temp = list->head;
        for (int i = 0; i < position - 1; i++) {
            temp = temp->next;
        }
        node->next = temp->next;
        temp->next = node;
    }
    list->size++;
}

void displayList(LinkedList *list) {
    printf("List: ");
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->key);
        current = current->next;
    }
    printf("\n");
}

float calculateAverage(LinkedList *list) {
    if (list->size == 0) {
        return 0.0;
    }

    float sum = 0.0;
    Node *current = list->head;
    while (current != NULL) {
        sum += current->key;
        current = current->next;
    }

    return sum / list->size;
}

int main() {
    LinkedList *X = createEmptyList();

    Node *N1 = (Node *)malloc(sizeof(Node));
    N1->key = 10;
    Node *N2 = (Node *)malloc(sizeof(Node));
    N2->key = 20;
    Node *N3 = (Node *)malloc(sizeof(Node));
    N3->key = 30;
    Node *N4 = (Node *)malloc(sizeof(Node));
    N4->key = 40;

    insertAtPosition(X, 0, N1);
    insertAtPosition(X, 0, N2);
    insertAtPosition(X, 0, N3);
    insertAtPosition(X, 0, N4);

    printf("Size: %d\n", X->size);
    displayList(X);
    printf("Average: %.2f\n", calculateAverage(X));

    return 0;
}
