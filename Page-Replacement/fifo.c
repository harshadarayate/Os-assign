#include <stdio.h>

void fifo(int pages[], int n, int frames_count) {
    int frames[frames_count];
    for (int i = 0; i < frames_count; i++) {
        frames[i] = -1; // Initialize frames to -1
    }

    int page_hits = 0;
    int page_misses = 0;
    int index = 0; // Index for FIFO

    for (int i = 0; i < n; i++) {
        int symbol = pages[i];
        int found = 0;

        // Check if the page is already in one of the frames
        for (int j = 0; j < frames_count; j++) {
            if (frames[j] == symbol) {
                found = 1;
                break;
            }
        }

        if (found) {
            printf("Page %d is already in memory.\n", symbol);
            page_hits++;
        } else {
            frames[index] = symbol; // Replace the oldest page
            index = (index + 1) % frames_count; // Move to the next frame
            page_misses++;
            printf("Page %d added to memory.\n", symbol);
        }

        // Display current frame state
        printf("Current Frames: ");
        for (int j = 0; j < frames_count; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Total Page Hits: %d\n", page_hits);
    printf("Total Page Misses: %d\n", page_misses);
    printf("Hit Ratio: %.2f\n", (float)page_hits / n);
    printf("Miss Ratio: %.2f\n", (float)page_misses / n);
}

int main() {
    int n, frames_count;

    printf("Enter the number of pages: ");
    scanf("%d", &n);
    
    int pages[n];
    printf("Enter the page numbers:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frames_count);

    fifo(pages, n, frames_count);

    return 0;
}