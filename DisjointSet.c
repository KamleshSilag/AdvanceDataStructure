//
// Created by Kamlesh on 19/03/2018.
// Union find Program

#include<stdio.h>

void initialize(int *a,int *size)
{
    int i;
    for(i=0;i<6;i++)
    {
        size[i]=1;
        a[i]=i;
    }
}

int root(int *a,int i)
{
    while(a[i]!=i)
    {
        i=a[i];
    }
    return i;
}

int find(int *arr,int a,int b)
{
    if(arr[a]==arr[b])
        return 1;
    return 0;
}

void display(int *a,int *size)
{
    int i;
    printf("\n");
    for(i=0;i<6;i++)
    {
        printf("\nArr : %d\t Size : %d",a[i],size[i]);
    }
}

void w_union(int *arr,int *size,int a,int b)
{
    int root_a = root(arr,a);
    int root_b = root(arr,b);

    if(size[root_a]< size[root_b])
    {
        arr[root_a]=arr[root_b];
        size[root_b]=size[root_b]+size[root_a];
    }
    else
    {
        arr[root_b]=arr[root_a];
        size[root_a]=size[root_a]+size[root_b];
    }
}


int main()
{
    int a[6],size[6];
    initialize(a,size);
    display(a,size);

    w_union(a,size,1,2);
    w_union(a,size,4,5);
    display(a,size);

    
    return 0;
}