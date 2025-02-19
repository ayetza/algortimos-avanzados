#ifndef _MERGESORT_H
#define _MERGESORT_H

#include <vector>

// Complejidad O(n)
// Funcion para fusionar dos mitades ordenadas
void merge(std::vector<double> &arr, int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;
    std::vector<double> L(n1), R(n2);

    // Copiar datos a los arreglos temporales L y R
    for (int i = 0; i < n1; i++)
        L[i] = arr[low + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Fusionar los arreglos L y R en orden descendente
    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2)
    {
        if (L[i] >= R[j])
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

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
}

// Complejidad O(n log n)
void mergeSort(std::vector<double> &arr, int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

#endif