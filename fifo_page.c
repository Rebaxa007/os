#include <stdio.h>

void fifoPageReplacement(int pages[], int n, int frames[], int f) {
    int pageFaults = 0, pageHits = 0, front = 0;

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if the page is already in a frame (Page Hit)
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                pageHits++;
                break;
            }
        }

        // If the page is not in a frame (Page Fault)
        if (!found) {
            frames[front] = pages[i];
            front = (front + 1) % f; // Move to the next frame position
            pageFaults++;
        }

        // Print the current frame status
        printf("Page %d -> ", pages[i]);
        for (int j = 0; j < f; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }

    // Calculate and print hit ratio and miss ratio
    printf("\nTotal Page Hits: %d\n", pageHits);
    printf("Total Page Faults: %d\n", pageFaults);
    printf("Hit Ratio: %.2f\n", (float)pageHits / n);
    printf("Miss Ratio: %.2f\n", (float)pageFaults / n);
}

int main() {
    int n, f;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    int frames[f];
    for (int i = 0; i < f; i++) {
        frames[i] = -1; // Initialize frames as empty
    }

    fifoPageReplacement(pages, n, frames, f);
    return 0;
}
