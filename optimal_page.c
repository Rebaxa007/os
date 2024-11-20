#include <stdio.h>
#define MAX 100

int main()
{
    int nPages, nFrames, pages[MAX], frames[MAX];
    int pageFaults = 0, hits = 0;

    // Input the number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &nPages);

    // Input the page reference string
    printf("Enter the page reference string: ");
    for (int i = 0; i < nPages; i++)
    {
        scanf("%d", &pages[i]);
    }

    // Input the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &nFrames);

    // Initialize frames
    for (int i = 0; i < nFrames; i++)
    {
        frames[i] = -1;
    }

    printf("\nPage\tFrames\n");

    // Process each page in the reference string
    for (int i = 0; i < nPages; i++)
    {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in a frame
        for (int j = 0; j < nFrames; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                hits++;
                break;
            }
        }

        if (!found)
        { // Page fault
            pageFaults++;

            // Find the replacement index
            int replaceIndex = -1, farthest = -1;

            for (int j = 0; j < nFrames; j++)
            {
                if (frames[j] == -1)
                { // Empty frame
                    replaceIndex = j;
                    break;
                }

                // Look ahead in the reference string
                int nextUse = MAX;
                for (int k = i + 1; k < nPages; k++)
                {
                    if (frames[j] == pages[k])
                    {
                        nextUse = k;
                        break;
                    }
                }

                if (nextUse > farthest)
                {
                    farthest = nextUse;
                    replaceIndex = j;
                }
            }

            // Replace the page
            frames[replaceIndex] = page;
        }

        // Print the current state of frames
        printf("%d\t", page);
        for (int j = 0; j < nFrames; j++)
        {
            if (frames[j] != -1)
            {
                printf("%d ", frames[j]);
            }
            else
            {
                printf("- ");
            }
        }
        printf("\n");
    }

    // Print results
    printf("\nPage Faults: %d\n", pageFaults);
    printf("Page Hits: %d\n", hits);
    printf("Hit Ratio: %.2f\n", (float)hits / nPages);
    printf("Miss Ratio: %.2f\n", (float)pageFaults / nPages);

    return 0;
}
