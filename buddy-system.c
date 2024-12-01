#include <stdio.h>
#include <stdlib.h>

#define MAX_MEMORY 1000
#define MIN_BLOCK_SIZE 16

typedef struct Block
{
    int size;
    int free;
    struct Block *next;
} Block;

Block *head = NULL;

void initialize()
{
    head = (Block *)malloc(sizeof(Block));
    head->size = MAX_MEMORY;
    head->free = 1;
    head->next = NULL;
}

void split(Block *block, int size)
{
    Block *newBlock = (Block *)malloc(sizeof(Block));
    newBlock->size = block->size - size;
    newBlock->free = 1;
    newBlock->next = block->next;
    block->size = size;
    block->next = newBlock;
}

void *allocate(int size) //100
{
    Block *current = head;
    while (current != NULL)
    {
        if (current->free && current->size >= size)
        {
            if (current->size > size + MIN_BLOCK_SIZE)
            {
                split(current, size);
            }
            current->free = 0;
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void deallocate(void *ptr)
{
    Block *current = head;
    while (current != NULL)
    {
        if (current == ptr)
        {
            current->free = 1;
            if (current->next != NULL && current->next->free)
            {
                current->size += current->next->size;
                current->next = current->next->next;
            }
            return;
        }
        current = current->next;
        
    }
}

void printMemory()
{
    Block *current = head;
    printf("Memory Allocation Table:\n");
    printf("Size\tAllocated\n");
    while (current != NULL)
    {
        printf("%d\t%d\n", current->size, !current->free);
        current = current->next;
    }
}

int main()
{
    initialize();
    int choice, size;
    while (1)
    {
        printf("\n1. Allocate Memory\n");
        printf("2. Deallocate Memory\n");
        printf("3. Print Memory Allocation Table\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the size of memory to allocate: ");
            scanf("%d", &size);
            if (allocate(size) != NULL)
            {
                printf("Memory allocated successfully.\n");
            }
            else
            {
                printf("Memory allocation failed.\n");
            }
            break;
        case 2:
            printf("Enter the size of memory to deallocate: ");
            scanf("%d", &size);
            Block *current = head;
            while (current != NULL)
            {
                if (current->size == size && !current->free)
                {
                    deallocate(current);
                    printf("Memory deallocated successfully.\n");
                    break;
                }
                current = current->next;
            }
            if (current == NULL)
            {
                printf("Memory deallocation failed.\n");
            }
            break;
        case 3:
            printMemory();
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}