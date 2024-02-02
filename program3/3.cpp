#include <iostream>
#include <cstdlib>
#include <string.h>
#include <ctime>
#define N 500

using namespace std;

void Setup(int arr[], int size)
{
          for (int i = 0; i < size; i++)
          {
                    arr[i] = rand()%101; //0-100
          }
}

void Output(int arr[], int size)
{
          for (int i = 0; i < size; i++)
                    cout << arr[i] << " ";
          cout << endl;
}

void merge(int arr[], int left, int mid, int right)
{
          int sizeL = mid - left + 1;
          int sizeR = right - mid;
          int L[sizeL], R[sizeR];

         for (int i = 0; i < sizeL; i++)
                    L[i] = arr[left + i];
          for (int j = 0; j < sizeR; j++)
                    R[j] = arr[mid + 1 + j];

          int i = 0; //L
          int j = 0; //R
          int k = left; //arr
          while (i < sizeL && j < sizeR)
          {
                    if (L[i] <= R[j])
                    {
                              arr[k] = L[i];
                              i++;
                    }
                    else
                    {
                              arr[k] = R[j];
                              j++;
                    }
                    k++;
          }
          while (i < sizeL)
          {
                    arr[k] = L[i];
                    i++;
                    k++;
          }
          while (j < sizeR)
          {
                    arr[k] = R[j];
                    j++;
                    k++;
          }
}

void MergeSort(int arr[], int left, int right)
{
          if  (right > left)
          {
                    int mid = left + (right-left)/2;
                    MergeSort(arr, left, mid);
                    MergeSort(arr, mid+1, right);
                    merge(arr, left, mid, right);
          }
}

int main()
{
          srand(time(NULL));
          int data[N];
          Setup(data, N);
          cout << "BEFORE:" << endl;
          Output(data, N);
          MergeSort(data, 0, N-1);
          cout << "AFTER:" << endl;
          Output(data,N);
          return 0;
}
