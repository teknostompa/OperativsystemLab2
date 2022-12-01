#include <stdio.h>

#include <stdlib.h>

int isInPages(int * pages, int address, int number_pages, int page_size) {
    for (int i = 0; i < number_pages; i++)
        if (pages[i] <= address && pages[i] + page_size > address)
            return 1;
    return 0;
}

int predict(int * pages, int * memoryAddresses, int number_addresses, int number_pages, int page_size, int start) {
    int pages_dist[number_pages];
    for (int l = 0; l < number_pages; l++)
        pages_dist[l] = 1000000000;
        for (int i = start + 1; i < number_addresses; i++)
            for (int j = 0; j < number_pages; j++)
                if (pages[j] == (memoryAddresses[i] / page_size) * page_size)
                    if (i - start < pages_dist[j])
                        pages_dist[j] = i - start;
    int max = 0;
    int maxIndex;
    for (int i = 0; i < number_pages; i++)
        if (pages_dist[i] > max) {
            max = pages_dist[i];
            maxIndex = i;
        }
    return maxIndex;
}

int main(int argc, char * argv[]) {
    FILE * fptr;
    int memoryAddresses[1000000];
    int i = 0, index = 0;
    fptr = fopen(argv[3], "r");
    while (!feof(fptr)) {
        fscanf(fptr, "%d", & i);
        memoryAddresses[index] = i;
        index++;
    }
    fclose(fptr);
    int pageFaults = 0, number_pages = atoi(argv[1]), page_size = atoi(argv[2]);
    int pages[number_pages];
    for (int l = 0; l < number_pages; l++) {
        pages[l] = 1000000000;
    }
    for (int j = 0; j < index; j++) {
        if (!isInPages(pages, memoryAddresses[j], number_pages, page_size)) {
            pages[predict(pages, memoryAddresses, index, number_pages, page_size, j)] = (memoryAddresses[j] / page_size) * page_size;
            pageFaults++;
        }
    }
    printf("%d\n", pageFaults);
}