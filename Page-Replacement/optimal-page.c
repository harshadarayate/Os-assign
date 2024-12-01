#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

// Function to find the index of the page that will not be used for the longest period of time
int findOptimalPage(int pages[], int pageIndex[], int n, int pageCount[], int frames) {
    int farthestIndex = -1;
    int optimalPage = -1;

    for (int i = 0; i < frames; i++) {
        int j;
        for (j = pageIndex[i] + 1; j < n; j++) {
            if (pages[j] == pageCount[i]) {
                if (j > farthestIndex) {
                    farthestIndex = j;
                    optimalPage = i;
                }
                break;
            }
        }
        if (j == n) {
            return i; // This page is not going to be used again
        }
    }
    return optimalPage; // Return the index of the optimal page to replace
}

// Function to implement the Optimal Page Replacement algorithm
void optimalPageReplacement(int pages[], int n, int frames) {
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

            // If no empty frame is found, replace the optimal page
            if (j == frames) {
                int optimalPage = findOptimalPage(pages, pageIndex, n, pageCount, frames);
                printf("Replacing page %d with %d in frame %d\n", 
                       pageCount[optimalPage], 
                       page, 
                       optimalPage);
                pageCount[optimalPage] = page; // Replace the optimal page
                pageIndex[optimalPage] = i; // Update the last used index
                pageFaults++;
            }
        } else {
            // Update the last used index of the found page
            printf("Page %d already in frame\n", page);
            pageIndex[j] = i;
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

    // Call the Optimal Page Replacement function
    optimalPageReplacement(pages, n, frames);

    return 0;
}
