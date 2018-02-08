/**
   Created by Gabriella Uwadiegwu on 10/09/2017.
   Data Structures (CSC 430) Project 1
   Prof. Salvati

   Analysis of Sorting Techniques

**/
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

    /**
    Initialization of arrays and counters as global variables. Icky but needed
    **/

    int swaps;
    int comparisons;
    int inverse100[100];
    int random100[100];
    int almost100[100];
    int inverse1000[1000];
    int random1000[1000];
    int almost1000[1000];

    /**
     To reset array after each usage by sorting funtion
     **/
    void setDefaultArrays();

    /**
     * Major functions
     * */
    void swap(int &, int &);
    void SelectionSort(int [], int );
    void InsertionSort(int[], int);
    void GnomeSort(int [], int);
    void Merge(int[], int, int, int);
    void MergeSort(int [], int, int);
    void quickSort(int [], int, int);
    int partition(int[], int, int);
    void Heap(int[], int, int);
    void HeapSort(int[], int);

    /**Functions that calls the sorting algorithms and put their output to file*/
    void SelectionFile();
    void InsertionFile();
    void GnomeFile();
    void MergeFile();
    void QuickFile();
    void HeapFile();

     int main(){

         setDefaultArrays();
         SelectionFile();

         setDefaultArrays();
         InsertionFile();

         setDefaultArrays();
         GnomeFile();

         setDefaultArrays();
         MergeFile();

         setDefaultArrays();
         QuickFile();

         setDefaultArrays();
         HeapFile();
    }

    void swap(int &x,int &y) {
        int temp=x;
        x=y;
        y=temp;
    }

   void SelectionSort(int arr[], int n) {

       swaps = 0;
       comparisons = 0;

       int i, j, min_idx;

       for (i = 0; i < n-1; i++)
       {
           min_idx = i;
           for (j = i+1; j < n; j++) {
               if (arr[j] < arr[min_idx]) {
                   min_idx = j;
               }
               comparisons++;
           }
           swap(arr[min_idx], arr[i]);
           swaps++;
       }
    }

   void InsertionSort(int arr[], int n) {

        swaps = 0;
        comparisons = 0;
        int i, temp, j;
        for (i = 1; i < n; i++) {
            temp = arr[i];
            j = i-1;
            while (j >= 0 && arr[j] > temp) {
                swap(arr[j+1],arr[j]);
                j = j-1;
                swaps++;
                comparisons++;
            }
        }
    }

   void GnomeSort(int arr[], int n) {

        int index = 0;
        swaps = 0;
        comparisons = 0;
        while (index < n) {
            if (index == 0) {
                index++;
                comparisons++;
            }
            if (arr[index] >= arr[index-1]) {
                index++;
                comparisons++;
            }
            else {
                swap(arr[index--], arr[index-1]);
                swaps++;
                comparisons++;
            }
        }
    }

   int partition (int arr[], int low, int high){

        int pivot = arr[high];    // pivot
        int i = (low - 1);  // Index of smaller element

        for (int j = low; j <= high - 1; j++) {
            if (arr[j] <= pivot) {
                swap(arr[++i], arr[j]);
                swaps++;
                comparisons++;
            }
        }
        swap(arr[i + 1], arr[high]);
        swaps++;
        return (i + 1);
    }

   void quickSort(int arr[], int low, int high){

        if (low < high) {
            comparisons++;
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

   void Merge(int a[], int low, int high, int mid) {

        // We have teh two parts of the array already sorted.
        int i, j, k, temp[high-low+1];
        i = low;
        k = 0;
        j = mid + 1;

        // Merge the two parts into temp[].
        while (i <= mid && j <= high) {

            if (a[i] < a[j])
                temp[k] = a[i];
            else
              temp[k++] = a[j++];
            comparisons++;
        }
        while (i <= mid) {
            temp[k++] = a[i++];
            comparisons++;
        }
        while (j <= high) {
            temp[k++] = a[j++];
            comparisons++;
        }
         // Assigning sorted numbers in temp[] to a[].
        for (i = low; i <= high; i++) {
            a[i] = temp[i - low];
            swaps++;
        }
    }

   void MergeSort(int a[], int low, int high) {
        int mid;
        if (low < high) {
            comparisons++;
            mid = (low + high) / 2;

            // Splitting the data into two half.
            MergeSort(a, low, mid);
            MergeSort(a, mid + 1, high);

            // Merging to get sorted output.
            Merge(a, low, high, mid);
        }
    }
   void Heap(int arr[], int n, int i) {

        int largest = i;  // Initialize largest as root
        int l = 2*i + 1;  // left = 2*i + 1
        int r = 2*i + 2;  // right = 2*i + 2

        // Left child larger than root
        if (l < n && arr[l] > arr[largest]) {
            largest = l;
            comparisons++;
        }
        // Right child larger than root
        if (r < n && arr[r] > arr[largest]) {
            largest = r;
            comparisons++;
        }
        // if largest is not the root
        if (largest != i)
        {
            swap(arr[i], arr[largest]);
            swaps++;
            comparisons++;
            //recursively heap the tree
            Heap(arr, n, largest);
        }

    }

   void HeapSort(int arr[], int n) {

        // to build heap
        for (int i = n / 2 - 1; i >= 0; i--)
            Heap(arr, n, i);
        // extracting each element from heap
        for (int i=n-1; i>=0; i--)
        {
            swap(arr[0], arr[i]); // Move current root to end
            swaps++;
            Heap(arr, i, 0); // call max heap on the reduced heap
        }
    }
    /**
     To reset all arrays and count before calling functions
     **/
   void setDefaultArrays() {

        swaps = 0;
        comparisons = 0;
        for (int i = 0, j = 100; i < 100, j >= 1; i++, j--)
            inverse100[i] = j;

        for (int i = 0; i < 100; i++)
            random100[i] = (rand() % 100 + 1);

        for (int i = 0; i <= 99; i++)
            almost100[i] = i+1;
        swap(almost100[99], almost100[98]),
        swap(almost100[56], almost100[57]);

        for (int i = 0, j = 1000; i < 1000, j >= 1; i++, j--)
            inverse1000[i] = j;

        for (int i = 0; i < 1000; i++)
            random1000[i] = (rand() % 1000 + 1);

        for (int i = 0; i <= 999; i++)
            almost1000[i] = i+1;
        swap(almost1000[999],almost1000[998]);
        swap(almost1000[456], almost1000[457]);
    }

    /**
     Calling of Algorithms and Putting to file
     **/
   void SelectionFile(){//aware this is a lot of lines, but its necessary.

        ofstream myFile;
        myFile.open("Selection_Sort_File.txt");     myFile<<"\nSelection sort swaps and comparisons"<<endl;
        SelectionSort(almost100, 100);              myFile<<"\nAlmost100 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl;
        SelectionSort(almost1000, 1000);            myFile<<"\nAlmost1000 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl;
        SelectionSort(random100, 100);              myFile<<"\nRandom100 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl;
        SelectionSort(random1000, 1000);            myFile<<"\nRandom1000 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl;
        SelectionSort(inverse100, 100);             myFile<<"\nInverse100 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl;
        SelectionSort(inverse1000, 1000);           myFile<<"\nInverse1000 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl;

        myFile<<"\n\nSorted List for for Almost, Random and Inverse"<<endl;
        myFile<<"\nFor 100's"<<endl;
        myFile<<"Almost 100\t"<<"Random 100 \t"<<"Inverse 100"<<endl;
        for(int i = 0; i<100; i++) {
            myFile<<almost100[i]<< "\t\t"<<random100[i]<<"\t\t"<<inverse100[i]<<endl;
        }
        myFile<<"\nFor 1000's "<<endl;
        myFile<<"Almost 1000\t"<<"Random 1000 \t"<<"Inverse 1000"<<endl;
        for(int i = 0; i<1000; i++) {
            myFile<<almost1000[i]<< "\t\t"<<random1000[i]<<"\t\t"<<inverse1000[i]<<endl;
        }
        myFile.close();
    }

   void InsertionFile(){

        ofstream myFile;
        myFile.open("Insertion_Sort_File.txt");     myFile<<"\nInsertion sort swaps and comparisons"<<endl;
        InsertionSort(almost100, 100);              myFile<<"\nAlmost100 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl;
        InsertionSort(almost1000, 1000);            myFile<<"\nAlmost1000 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl;
        InsertionSort(random100, 100);              myFile<<"\nRandom100 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl;
        InsertionSort(random1000, 1000);            myFile<<"\nRandom1000 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl;
        InsertionSort(inverse100, 100);             myFile<<"\nInverse100 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl;
        InsertionSort(inverse1000, 1000);           myFile<<"\nInverse1000 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl;

        myFile<<"\n\nSorted List for for Almost, Random and Inverse"<<endl;
        myFile<<"\nFor 100's"<<endl;
        myFile<<"Almost 100\t"<<"Random 100 \t"<<"Inverse 100"<<endl;
        for(int i = 0; i<100; i++) {
            myFile<<almost100[i]<< "\t\t"<<random100[i]<<"\t\t"<<inverse100[i]<<endl;
        }
        myFile<<"\nFor 1000's "<<endl;
        myFile<<"Almost 1000\t"<<"Random 1000 \t"<<"Inverse 1000"<<endl;
        for(int i = 0; i<1000; i++) {
            myFile<<almost1000[i]<< "\t\t"<<random1000[i]<<"\t\t"<<inverse1000[i]<<endl;
        }
        myFile.close();
    }

   void GnomeFile(){

        ofstream myFile;
        myFile.open("Gnome_Sort_File.txt");     myFile<<"\nGnome sort swaps and comparisons"<<endl;
        GnomeSort(almost100, 100);              myFile<<"\nAlmost100 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl;
        GnomeSort(almost1000, 1000);            myFile<<"\nAlmost1000 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl;
        GnomeSort(random100, 100);              myFile<<"\nRandom100 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl;
        GnomeSort(random1000, 1000);            myFile<<"\nRandom1000 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl;
        GnomeSort(inverse100, 100);             myFile<<"\nInverse100 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl;
        GnomeSort(inverse1000, 1000);           myFile<<"\nInverse1000 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl;

        myFile<<"\n\nSorted List for for Almost, Random and Inverse"<<endl;
        myFile<<"\nFor 100's"<<endl;
        myFile<<"Almost 100\t"<<"Random 100 \t"<<"Inverse 100"<<endl;
        for(int i = 0; i<100; i++) {
            myFile<<almost100[i]<< "\t\t"<<random100[i]<<"\t\t"<<inverse100[i]<<endl;
        }
        myFile<<"\nFor 1000's "<<endl;
        myFile<<"Almost 1000\t"<<"Random 1000 \t"<<"Inverse 1000"<<endl;
        for(int i = 0; i<1000; i++) {
            myFile<<almost1000[i]<< "\t\t"<<random1000[i]<<"\t\t"<<inverse1000[i]<<endl;
        }
        myFile.close();
    }

   void MergeFile(){

        ofstream myFile;
        myFile.open("Merge_Sort_File.txt");       myFile<<"\nMerge sort swaps and comparisons"<<endl;
        MergeSort(almost100, 0, 99);
        myFile<<"\nAlmost100 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl; swaps = 0; comparisons = 0;
        MergeSort(almost1000,0, 999);
        myFile<<"\nAlmost1000 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl; swaps = 0; comparisons = 0;
        MergeSort(random100, 0, 99);
        myFile<<"\nrandom100 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl; swaps = 0; comparisons = 0;
        MergeSort(random1000, 0, 999);
        myFile<<"\nRandom1000 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl; swaps = 0; comparisons = 0;
        MergeSort(inverse100, 0,  99);
        myFile<<"\nInverse100 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl; swaps = 0; comparisons = 0;
        MergeSort(inverse1000, 0, 999);
        myFile<<"\nInverse1000 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl; swaps = 0; comparisons = 0;

        myFile<<"\n\nSorted List for for Almost, Random and Inverse"<<endl;
        myFile<<"\nFor 100's"<<endl;
        myFile<<"Almost 100\t"<<"Random 100 \t"<<"Inverse 100"<<endl;
        for(int i = 0; i<100; i++) {
            myFile<<almost100[i]<< "\t\t"<<random100[i]<<"\t\t"<<inverse100[i]<<endl;
        }
        myFile<<"\nFor 1000's "<<endl;
        myFile<<"Almost 1000\t\t "<<"Random 1000 \t\t"<<"Inverse 1000"<<endl;
        for(int i = 0; i<1000; i++) {
            myFile<<almost1000[i]<< "\t\t"<<random1000[i]<<"\t\t"<<inverse1000[i]<<endl;
        }
        myFile.close();
    }

   void QuickFile(){

        ofstream myFile;
        myFile.open("Quick_Sort_File.txt");       myFile<<"\nQuick sort swaps and comparisons"<<endl;
        quickSort(almost100, 0, 99);
        myFile<<"\nAlmost100 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl; swaps = 0; comparisons = 0;
        quickSort(almost1000,0, 999);
        myFile<<"\nAlmost1000 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl; swaps = 0; comparisons = 0;
        quickSort(random100, 0, 99);
        myFile<<"\nRandom100 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl; swaps = 0; comparisons = 0;
        quickSort(random1000, 0, 999);
        myFile<<"\nRandom1000 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl; swaps = 0; comparisons = 0;
        quickSort(inverse100, 0,  99);
        myFile<<"\nInverse100 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl; swaps = 0; comparisons = 0;
        quickSort(inverse1000, 0, 999);
        myFile<<"\nInverse1000 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl; swaps = 0; comparisons = 0;

        myFile<<"\n\nSorted List for for Almost, Random and Inverse"<<endl;
        myFile<<"\nFor 100's"<<endl;
        myFile<<"Almost 100\t"<<"Random 100 \t"<<"Inverse 100"<<endl;
        for(int i = 0; i<100; i++) {
            myFile<<almost100[i]<< "\t\t"<<random100[i]<<"\t\t"<<inverse100[i]<<endl;
        }
        myFile<<"\nFor 1000's "<<endl;
        myFile<<"Almost 1000\t"<<"Random 1000 \t"<<"Inverse 1000"<<endl;
        for(int i = 0; i<1000; i++) {
            myFile<<almost1000[i]<< "\t\t"<<random1000[i]<<"\t\t"<<inverse1000[i]<<endl;
        }
        myFile.close();
    }

   void HeapFile(){

        ofstream myFile;
        myFile.open("Heap_Sort_File.txt");        myFile<<"\n Heap sort counts"<<endl;
        HeapSort(almost100, 100);
        myFile<<"\nAlmost100 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl; swaps = 0; comparisons = 0;
        HeapSort(almost1000, 1000);
        myFile<<"\nAlmost1000 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl; swaps = 0; comparisons = 0;
        HeapSort(random100, 100);
        myFile<<"\nRandom100 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl; swaps = 0; comparisons = 0;
        HeapSort(random1000, 1000);
        myFile<<"\nRandom1000 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl; swaps = 0; comparisons = 0;
        HeapSort(inverse100, 100);
        myFile<<"\nInverse100 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl; swaps = 0; comparisons = 0;
        HeapSort(inverse1000, 1000);
        myFile<<"\nInverse1000 \t Swaps: "<<swaps<<"\tComparisons: "<<comparisons<<endl; swaps = 0; comparisons = 0;

        myFile<<"\n\nSorted List for for Almost, Random and Inverse"<<endl;
        myFile<<"\nFor 100's"<<endl;
        myFile<<"Almost 100\t"<<"Random 100 \t"<<"Inverse 100"<<endl;
        for(int i = 0; i<100; i++) {
            myFile<<almost100[i]<< "\t\t"<<random100[i]<<"\t\t"<<inverse100[i]<<endl;
        }
        myFile<<"\nFor 1000's "<<endl;
        myFile<<"Almost 1000\t"<<"Random 1000 \t"<<"Inverse 1000"<<endl;
        for(int i = 0; i<1000; i++) {
            myFile<<almost1000[i]<< "\t\t"<<random1000[i]<<"\t\t"<<inverse1000[i]<<endl;
        }
        myFile.close();
}