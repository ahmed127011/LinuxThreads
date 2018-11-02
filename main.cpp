#include <bits/stdc++.h>
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

using namespace std;

struct arr {
    int n;
    int *arr;
};

void *mergeSorter(void *args) {
    struct arr *myArr;
    myArr = (struct arr *) args;
    int n = myArr->n;
    if (n <=1) {
        pthread_exit(NULL);
    }

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    int mid = n / 2;
    int resultarr [n];
    *resultarr=*myArr->arr;

    arr leftarr, rightarr;
    leftarr.arr = &resultarr[0];
    leftarr.n = n - mid;
    rightarr.arr = &resultarr[n-mid];
    rightarr.n = mid;
    pthread_t lThread, rThread;
    int lt = pthread_create(&lThread, &attr, mergeSorter, (void *) &leftarr);
    int rt = pthread_create(&rThread, &attr, mergeSorter, (void *) &rightarr);
    if (lt != 0 || rt != 0) {
        cout << "error creating thread";
    }

    pthread_attr_destroy(&attr);
    void *status;
    lt = pthread_join(lThread, &status);
    rt = pthread_join(rThread, &status);
    if (lt != 0 || rt != 0) {
        cout << "error joining threads";
    }
    cout<<endl;
    cout<<"before merge:"<<endl;
    for(int i=0;i<n-mid;i++){
        cout<<"a"<<leftarr.arr[i]<<" ";

    }
    cout<<endl;
    for(int i=0;i<mid;i++){
        cout<<rightarr.arr[i]<<" ";
    }
    cout<<endl;
    cout<<"after merge: ";
    int i=0,j=0;
    while(i+j<n){
        if(i>=n-mid){
            resultarr[i+j]=rightarr.arr[j];
            j++;
        }else if(j>=mid){
            resultarr[i+j]=leftarr.arr[i];
            i++;
        }else{
            if(leftarr.arr[i]<rightarr.arr[j]){
                resultarr[i+j]=leftarr.arr[i];
                i++;
            }else{
                resultarr[i+j]=rightarr.arr[j];
                j++;
            }
        }



    }
    for(int i=0;i<n;i++){
        cout<<resultarr[i]<<" ";
    }
    cout<<endl;
    myArr->arr=resultarr;
    pthread_exit(NULL);

}

int main() {
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_t thread;

    struct arr mainArr;
    mainArr.arr=arr;
    mainArr.n=n;


    int th = pthread_create(&thread, &attr, mergeSorter, (void *) &mainArr);
    if(th){
        cout<<"Unable to create main thread";
    }
    //pthread_attr_destroy(attr);
    void *status;
    th = pthread_join(thread, NULL);
    if(th){
        cout<<"Unable to join main thread";
    }
    for(int i=0;i<n;i++){
        cout<<mainArr.arr[i]<<" ";
    }
    pthread_exit(NULL);

    return 0;
}