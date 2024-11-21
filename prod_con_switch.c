#include <stdio.h>
#define MAX_ITEMS 10

int buffer[MAX_ITEMS];
int in = 0, out = 0, count = 0; // Shared variables

void produce() {
    if (count == MAX_ITEMS) {
        printf("Buffer is full! Cannot produce more items.\n");
        return;
    }
    buffer[in] = in + 1; // Produce an item
    printf("Produced: %d\n", buffer[in]);
    in = (in + 1) % MAX_ITEMS; // Circular buffer logic
    count++;
}

void consume() {
    if (count == 0) {
        printf("Buffer is empty! Cannot consume any items.\n");
        return;
    }
    printf("Consumed: %d\n", buffer[out]);
    out = (out + 1) % MAX_ITEMS; // Circular buffer logic
    count--;
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Produce\n2. Consume\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                produce();
                break;
            case 2:
                consume();
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
