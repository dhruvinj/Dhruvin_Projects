#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<ctime>

void merge(int arr[], int l, int m, int r)
{
  int i, j, k;
  int n1 = m - l + 1;
  int n2 =  r - m;
  std::cout << n1 << " " << n2 << std::endl;
  /* left and right arrays */
  int L[n1], R[n2];
 
  /* Copy data t0 Left[] and Right[] */
  for(i = 0; i < n1; i++){
    L[i] = arr[l + i];
  }
  for(j = 0; j < n2; j++){
    R[j] = arr[m + 1+ j];
  }
 
  /* Merge the temp arrays back into arr[l..r]*/
  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2)
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
 
  /*  remaining elements of L[]*/
  while (i < n1)
    {
      arr[k] = L[i];
      i++;
      k++;
    }
 
  /* remaining elements of R[] */
  while (j < n2)
    {
      arr[k] = R[j];
      j++;
      k++;
    }
}







void mergeSort(int arr[], int l, int r)
{
  if (l < r)
    {
      int m = l+(r-l)/2; //Same as (l+r)/2, but avoids overflow for large l and h
      mergeSort(arr, l, m);
      mergeSort(arr, m+1, r);
      merge(arr, l, m, r);
    }
}



void printArray(int A[], int size)
{
  int i;
  for (i=0; i < size; i++)
    {
      std::cout << A[i] << std::endl;
    }
}


int main(int argc, char* argv[])
{

  int arr[] = {22, 111, 13, 15, 60, 87};
  int arr_size = sizeof(arr)/sizeof(arr[0]);
 
  std::cout << "Given array is " << std::endl;
  printArray(arr, arr_size);
 
  mergeSort(arr, 0, arr_size - 1);
 
  // std::cout << "Sorted array is "<< std::endl;
  // printArray(arr, arr_size);

  return 0;
}
