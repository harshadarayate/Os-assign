#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

// Function to find the index of the least recently used page
int findLRUPage(int pageIndex[], int frames) {
    int lruIndex = 0;
    for (int i = 1; i < frames; i++) {
        if (pageIndex[i] < pageIndex[lruIndex]) {
            lruIndex = i; // Update to the least recently used index
        }
    }
    return lruIndex; // Return the index of the LRU page
}

// Function to implement the Least Recently Used (LRU) page replacement algorithm
void lruPageReplacement(int pages[], int n, int frames) {
    int pageFaults = 0;
    int pageHits = 0;
    int pageCount[MAX_FRAMES] = {-1}; // Array to store pages in frames
    int pageIndex[MAX_FRAMES] = {-1}; // Array to store the last used index of pages in frames

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int j;

        // Check if the page is already in one of the frames
        int pageFound = 0;
        for (j = 0; j < frames; j++) {
            if (pageCount[j] == page) {
                pageFound = 1;
                pageHits++; // Increment page hits if the page is found
                // Update the last used index of this page
                pageIndex[j] = i;
                printf("Page %d already in frame\n", page);
                break;
            }
        }

        // If the page is not found, we have a page fault
        if (!pageFound) {
            // If there is an empty frame, use it
            for (j = 0; j < frames; j++) {
                if (pageCount[j] == -1) {
                    pageCount[j] = page;
                    pageIndex[j] = i; // Update the last used index
                    printf("Page %d added to frame %d\n", page, j);
                    pageFaults++;
                    break;
                }
            }

            // If no empty frame is found, replace the least recently used page
            if (j == frames) {
                int lruPageIndex = findLRUPage(pageIndex, frames);
                printf("Replacing page %d with %d in frame %d\n", 
                       pageCount[lruPageIndex], 
                       page, 
                       lruPageIndex);
                pageCount[lruPageIndex] = page; // Replace the LRU page
                pageIndex[lruPageIndex] = i; // Update the last used index
                pageFaults++;
            }
        }

        // Print the current state of frames
        printf("Current frames: ");
        for (int k = 0; k < frames; k++) {
            if (pageCount[k] != -1) {
                printf("%d ", pageCount[k]);
            } else {
                printf("- "); // Indicate empty frame with a dash
            }
        }
        printf("\n");
    }

    // Calculate and display hit and miss ratios
    int totalReferences = n;
    double hitRatio = (double)pageHits / totalReferences;
    double missRatio = (double)pageFaults / totalReferences;

    printf("Total Page Faults: %d\n", pageFaults);
    printf("Total Page Hits: %d\n", pageHits);
    printf("Hit Ratio: %.2f\n", hitRatio);
    printf("Miss Ratio: %.2f\n", missRatio);
}

int main() {
    int pages[MAX_PAGES];
    int n, frames;

    // Input the number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    
    // Input the reference string
    printf("Enter the reference string (space-separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Input the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    // Call the LRU Page Replacement function
    lruPageReplacement(pages, n, frames);

    return 0;
}
