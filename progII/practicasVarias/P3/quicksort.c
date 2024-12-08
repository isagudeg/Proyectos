
#include <stdlib.h>
#include <stdbool.h>
#include "vectordinamico.h"


void quicksort(vectorD *v1, unsigned long int beg, unsigned long int end) {
    if(end > beg+1){
        TELEMENTO piv=Componentei(*v1,beg);
        unsigned long l=beg+1, r=end;

        while(l<r){
            if(Componentei(*v1,l)<=piv){
                l++;
            }
            else{
                r--;
                swap(v1,l,r);
            }
        }   
        l--;
        swap(v1,l,beg);
        quicksort(v1,beg,l);
        quicksort(v1,r,end);
    }
}
