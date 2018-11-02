#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

using namespace std;

struct arr
{
    int l,r;
    int *arr;
};

void *mergeSorter(void *args)
{
    struct arr *myArr;
    myArr = (struct arr *) args;
    int l = myArr->l;
    int r = myArr->r;
    if(r-l<1)
        pthread_exit(NULL);

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    int mid = (l+r)/2;

    arr leftarr, rightarr;
    leftarr.arr = myArr.arr;
    leftarr.l =l;
    leftarr.r=mid;

    rightarr.arr = myArr.arr;
    rightarr.l = mid+1;
    rightarr.r=r;
    pthread_t lThread, rThread;
    int lt = pthread_create(&lThread, &attr, mergeSorter, (void *) &leftarr);
    int rt = pthread_create(&rThread, &attr, mergeSorter, (void *) &rightarr);
    if (lt != 0 || rt != 0) cout << "error creating thread";

    pthread_attr_destroy(&attr);
    void *status;
    lt = pthread_join(lThread, &status);
    rt = pthread_join(rThread, &status);
    if (lt != 0 || rt != 0)cout << "error joining threads";

    int leftSize=mid-l+1;
    int rightSize=r-mid;
    int left[leftSize];
    int right[rightSize];

    for(int i=0; i<leftSize; i++)
    {
        left[i]=myArr.arr[i+l];
    }
    for(int i=0; i<rightSize; i++)
    {
        right[i]=myArr.arr[i+mid+1];
    }
    int i=0,j=0;
   while(i+j<leftSize+rightSize)
    {
        if(i>=leftSize)
        {
            myArr.arr[l+i+j]=right[j];
            j++;
        }
        else if(j>=rightSize)
        {
            myArr.arr[l+i+j]=left[i];
            i++;
        }
        else if(left[i]<right[j])
        {
            myArr.arr[l+i+j]=left[i];
            i++;
        }
        else
        {
            myArr.arr[l+i+j]=right[j];
            j++;

        }

    }

    }
    myArr->arr=resultarr;
    pthread_exit(NULL);

}

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_t thread;

    struct arr mainArr;
    mainArr.arr=arr;
    mainArr.l=0;
    mainArr.r=n-1;


    int th = pthread_create(&thread, &attr, mergeSorter, (void *) &mainArr);
    if(th)
    {
        cout<<"Unable to create main thread";
    }
    //pthread_attr_destroy(attr);
    void *status;
    th = pthread_join(thread, NULL);
    if(th)
    {
        cout<<"Unable to join main thread";
    }
    for(int i=0; i<n; i++)
    {
        cout<<mainArr.arr[i]<<" ";
    }
    pthread_exit(NULL);

    return 0;
}
