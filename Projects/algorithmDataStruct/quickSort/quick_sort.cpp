#include<iostream>
#include<cmath>
#include<string>
#include<cassert>
#include<fstream>
#include<cstdlib>
#include<ctime>


void swap(int& a, int& b)
{
  int temp = a;

  a=b;

  b = temp;

}




int partition_function(int arr[], int start, int end)
{
  int pivot = arr[end];
  int index_partition = start; 

  for(int i=start; i< end ; i++)
    {

      if(arr[i] <= pivot)
	{
	  swap(arr[i], arr[index_partition]);
	  index_partition++;
	}

    }

  swap(arr[index_partition], arr[end]);

 
  return index_partition;
}







void quickSort(int arr[], int start, int end)
{
  if (start < end)
    {
      int partition_index = partition_function(arr, start,end);
      quickSort(arr, start, partition_index-1);
      quickSort(arr, partition_index+1, end);
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
 
  quickSort(arr, 0, arr_size - 1);
 
  std::cout << "Sorted array is "<< std::endl;
  printArray(arr, arr_size);

  return 0;
}
