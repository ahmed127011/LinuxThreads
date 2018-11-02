#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void mergeSort(int arr[],int l,int r)
{
    if(r-l<1)
        return;
    int mid =(l+r) / 2;
    mergeSort(arr,l,mid);
    mergeSort(arr,mid+1,r);

    int leftSize=mid-l+1;
    int rightSize=r-mid;
    int left[leftSize];
    int right[rightSize];
    for(int i=0; i<leftSize; i++)
    {
        left[i]=arr[i+l];
    }
    for(int i=0; i<rightSize; i++)
    {
        right[i]=arr[i+mid+1];
    }
    int i=0,j=0;
    while(i+j<leftSize+rightSize)
    {
        if(i>=leftSize)
        {
            arr[l+i+j]=right[j];
            j++;
        }
        else if(j>=rightSize)
        {
            arr[l+i+j]=left[i];
            i++;
        }
        else if(left[i]<right[j])
        {
            arr[l+i+j]=left[i];
            i++;
        }
        else
        {
            arr[l+i+j]=right[j];
            j++;

        }

    }


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

    mergeSort(arr,0,n-1);

for (int i = 0; i < n; i++)
    {
        cout<< arr[i]<<" ";
    }    return 0;
}
