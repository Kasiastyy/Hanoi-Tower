#include <iostream>
using namespace std;

// Struktura węzła reprezentująca krążek w stosie
struct Node {
    int disk = 0;
    Node* next = nullptr;
};

// Struktura stosu zawierająca wskaźnik na wierzchołek stosu
struct Stack {
    Node* top = nullptr;
};

// Funkcja do dodania krążka na wierzchołek stosu
void push(Stack *stack, int disk) {
    Node* newNode = new Node;
    newNode->disk = disk;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Funkcja do usunięcia krążka z wierzchołka stosu
int pop(Stack *stack) {
    int disk = 0;
    if (stack->top == nullptr) {
        return 0;  // Zwraca 0, jeśli stos jest pusty
    } else {
        Node* temp = stack->top;
        stack->top = stack->top->next;
        disk = temp->disk;
        delete temp;  // Usuwa węzeł z pamięci
    }
    return disk;
}

// Funkcja do ustawienia początkowych krążków na stosie
void setup(Stack *stack, int numDisks) {
    for (int i = numDisks; i >= 1; i--) {
        push(stack, i);  // Dodaje krążki od największego do najmniejszego
    }
}

// Funkcja do przenoszenia krążka z jednego stosu na drugi
void moveDisk(Stack *from, Stack *to) {
    if (from->top == nullptr) {
        cout << "-----Brak krążków do zabrania-----" << endl;
        return;
    }
    if (to->top != nullptr && from->top->disk > to->top->disk) {
        cout << "-----Niezgodne z zasadami-----" << endl;
    } else {
        push(to, pop(from));  // Przenosi krążek z jednego stosu na drugi
    }
}

// Funkcja do wyświetlania zawartości stosów (wież)
void displayTowers(Stack *A, Stack *B, Stack *C) {
    cout << "Wieża A" << endl;
    if (A->top == nullptr) {
        cout << "puste" << endl;
    } else {
        Node* curr = A->top;
        while (curr != nullptr) {
            cout << curr->disk << endl;  // Wyświetla krążki na wieży A
            curr = curr->next;
        }
    }

    cout << "Wieża B" << endl;
    if (B->top == nullptr) {
        cout << "puste" << endl;
    } else {
        Node* curr = B->top;
        while (curr != nullptr) {
            cout << curr->disk << endl;  // Wyświetla krążki na wieży B
            curr = curr->next;
        }
    }

    cout << "Wieża C" << endl;
    if (C->top == nullptr) {
        cout << "puste" << endl;
    } else {
        Node* curr = C->top;
        while (curr != nullptr) {
            cout << curr->disk << endl;  // Wyświetla krążki na wieży C
            curr = curr->next;
        }
    }
}

// Funkcja obsługująca logikę gry Hanoi
void playHanoi(int numDisks) {
    Stack A = {};
    Stack B = {};
    Stack C = {};
    setup(&A, numDisks);  // Ustawia początkowy stos na wieży A

    int choice;
    while (true) {
        displayTowers(&A, &B, &C);  // Wyświetla aktualny stan wież

        // Menu wyboru
        cout << "Wybierz opcję:" << endl;
        cout << "1. Przenieś z A do B" << endl;
        cout << "2. Przenieś z A do C" << endl;
        cout << "3. Przenieś z B do A" << endl;
        cout << "4. Przenieś z B do C" << endl;
        cout << "5. Przenieś z C do A" << endl;
        cout << "6. Przenieś z C do B" << endl;
        cout << "0. Wyjdź" << endl;

        cin >> choice;

        // Obsługuje wybór gracza
        switch (choice) {
            case 1:
                moveDisk(&A, &B);
                break;
            case 2:
                moveDisk(&A, &C);
                break;
            case 3:
                moveDisk(&B, &A);
                break;
            case 4:
                moveDisk(&B, &C);
                break;
            case 5:
                moveDisk(&C, &A);
                break;
            case 6:
                moveDisk(&C, &B);
                break;
            case 0:
                cout << "-----Zakończenie gry-----" << endl;
                return;
            default:
                cout << "-----Nieprawidłowy wybór. Spróbuj ponownie-----" << endl;
        }

        cout << endl;
    }
}

int main() {
    int numDisks;
    cout << "Podaj startową ilość krążków: ";
    cin >> numDisks;
    playHanoi(numDisks);  // Rozpoczyna grę Hanoi
}
