#include<stdio.h>
#include<stdlib.h>

int linear_search(int arr[],int n,int item){
    for(int i=0; i<n; i++){
        if(arr[i]==item){
        printf("the item is at index %d", i);
        return 0;
    }

}
    printf("the item is not found in the array");
    return 0;
}

int main(){
    int arr[]={11,33,54,656,6};

    linear_search(arr,5,11);
    printf("\n");
}
    