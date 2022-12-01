#include <stdio.h>


int isInPages(int* pages, int address, int number_pages, int page_size){
    int inPhysical = 0;
    for(int i = 0; i < number_pages; i++){
        if(pages[i] <= address && pages[i] + page_size > address)
            inPhysical = 1;
    }
    return inPhysical;
}

int main(int argc, char *argv[])  {
    int pageFaults = 0;
    int place = 0;
    int i = 0;
    FILE *fptr;
    fptr = fopen(argv[3], "r");
    int number_pages = atoi(argv[1]);
    int pages[number_pages];
    int page_size = atoi(argv[2]);

    for(int l = 0; l < number_pages; l++)
        pages[l] = -10000;
    while (!feof (fptr))
    {
        fscanf (fptr, "%d", &i);
        if(!isInPages(pages, i, number_pages, page_size)){
            pages[place] = (i/page_size)*page_size;
            place = (place + 1) % number_pages;
            pageFaults ++;
        }
    }
    printf("%d\n", number_pages);
    fclose(fptr);
}