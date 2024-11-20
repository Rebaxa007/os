#include <stdio.h>

#define MAX_FRAMES 3  // Fixed number of frames in memory

// Function to find the least recently used page
int findLRU(int time[], int n) {
    int min = time[0], index = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            index = i;
        }
    }
    return index;
}

// Function to implement LRU page replacement algorithm
void LRU(int pages[], int n) {
    int frames[MAX_FRAMES], time[MAX_FRAMES];
    int pageFaults = 0, pageHits = 0;

    // Initialize frames with -1 (empty) and time with -1
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
        time[i] = -1;
    }

    // Process each page in the page reference string
    for (int i = 0; i < n; i++) {
        int hit = 0;

        // Check if the page is already in one of the frames (page hit)
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                time[j] = i;  // Update the time when the page was accessed
                break;
            }
        }

        // If it was a page miss, replace the least recently used page
        if (!hit) {
            int lru = findLRU(time, MAX_FRAMES);

            // Replace the LRU page with the new page
            frames[lru] = pages[i];
            time[lru] = i;  // Update the time of the newly loaded page
            pageFaults++;  // A page fault occurred
        } else {
            pageHits++;  // A page hit occurred
        }
    }

    // Calculate the hit and miss ratios
    float hitRatio = (float)pageHits / n;
    float missRatio = (float)pageFaults / n;

    // Output the result
    printf("Total Page Hits: %d\n", pageHits);
    printf("Total Page Faults: %d\n", pageFaults);
    printf("Hit Ratio: %.2f\n", hitRatio);
    printf("Miss Ratio: %.2f\n", missRatio);
}

int main() {
    int n;

    // Get the number of page requests
    printf("Enter the number of page requests: ");
    scanf("%d", &n);

    int pages[n];

    // Get the page reference string from the user
    printf("Enter the page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Call the LRU function
    LRU(pages, n);

    return 0;
}
