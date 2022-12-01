#include <stdio.h>


int isInPages(int* pages, int* timeLastUsed, int address, int number_pages, int page_size){
    int inPhysical = 0;
    for(int i = 0; i < number_pages; i++){
        timeLastUsed[i]++;
        if(pages[i] <= address && pages[i] + page_size > address){
            inPhysical = 1;
            timeLastUsed[i] = 0;
        }
    }
    //printf("\n");
    return inPhysical;
}

int main(int argc, char *argv[])  {
    int pageFaults = 0;
    int i = 0;
    FILE *fptr;
    fptr = fopen(argv[3], "r");
    int number_pages = atoi(argv[1]);
    int pages[number_pages];
    int timeLastUsed[number_pages];
    int page_size = atoi(argv[2]);

    for(int l = 0; l < number_pages; l++){
        pages[l] = -10000;
        timeLastUsed[l] = 0;
    }
    while (!feof (fptr))
    {
        fscanf (fptr, "%d", &i);
        if(!isInPages(pages, timeLastUsed, i, number_pages, page_size)){
            int max = timeLastUsed[0];
            int maxIndex = 0;
            for(int page = 1; page < number_pages; page++){
                if(timeLastUsed[page] > max){
                    max = timeLastUsed[page];
                    maxIndex = page;
                } 
            }
            pages[maxIndex] = (i/page_size)*page_size;
            timeLastUsed[maxIndex] = 0;
            pageFaults ++; 
        }
    }
    printf("%d\n",pageFaults);
    fclose(fptr);
}