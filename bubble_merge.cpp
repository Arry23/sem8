#include <bits/stdc++.h>
#include <omp.h>
#include<chrono>
using namespace std;
using namespace std::chrono;

int N = 1000;

void bubble_sort_parallel(int a[], int n) 
{
	#pragma omp parallel shared (a, n)
	{
		int i,j;
		#pragma omp for
		for(int i = 0; i < n-1; i++) 
		{
			for(j = 0; j < n-i-1; j++) 
			{
				if(a[j] > a[j+1]) 
					swap(a[j], a[j+1]); 
			} 
		}
	}
}


void bubble_sort(int a[], int n) 
{
	int i,j;
	for(int i = 0; i < n-1; i++) 
	{
		for(j = 0; j < n-i-1; j++) 
		{
			if(a[j] > a[j+1]) 
				swap(a[j], a[j+1]); 
		} 
	}
}

void merge(int a[], int l, int md, int r) 
{
	vector<int> temp(r - l + 1);
	int i = l, j = md + 1, k = 0;
	while(i <= md && j <= r) 
	{
		if(a[i] <= a[j]) 
			temp[k++] = a[i++];
		else 
			temp[k++] = a[j++];
	} 
	
	while(i <= md) 
		temp[k++] = a[i++];
	while(j <= r) 
		temp[k++] = a[j++];
	for(int i = 0; i < k; i++) 
		a[l+i] = temp[i];

}

void merge_sort(int a[], int l, int r) 
{
	if( l < r)
	{
		int md = (l + r) / 2;
		merge_sort(a, l, md);
		merge_sort(a, md + 1, r);
		merge(a, l, md, r); 
	}
}

void merge_sort_parallel(int a[], int l, int r) 
{
	if( l < r)
	{
		int md = (l + r) / 2;
		#pragma omp parallel sections 
		{
		#pragma omp section
		merge_sort_parallel(a, l, md);
		#pragma omp section
		merge_sort_parallel(a, md + 1, r);
		merge(a, l, md, r); 
		}
	}
}

int main() 
{
	int a[N], a1[N], a2[N], a3[N]; 
	for(int i = 0; i < N; i++)
	{
		a[i] = rand() % N; 
		a1[i] = a[i]; 
		a2[i] = a[i]; 
		a3[i] = a[i];
	}		
	cout << "Array after original Bubble sort: ";
	auto start = high_resolution_clock::now();
	bubble_sort(a, N);
	auto end = high_resolution_clock::now();
	auto dur = duration_cast<microseconds>(end - start);
	for(int i = 0; i < min(N, 100); i++) 
	{
		cout << a[i] <<" ";
	} 
	cout << endl;
	cout << "Time taken : " <<dur.count() << " ms" <<endl; 
	
	
	
	cout << "Array after parallel Bubble sort: ";
	start = high_resolution_clock::now();
	bubble_sort_parallel(a1, N);
	end = high_resolution_clock::now();
	dur = duration_cast<microseconds>(end - start);
	for(int i = 0; i < min(N, 100); i++) 
	{
		cout << a1[i] <<" ";
	} 
	cout << endl;
	cout << "Time taken : " <<dur.count() << " ms" <<endl; 
	
	
	cout << "Array after original Merge sort: ";
	start = high_resolution_clock::now();
	merge_sort(a2, 0, N-1);
	end = high_resolution_clock::now();
	dur = duration_cast<microseconds>(end - start);
	for(int i = 0; i < min(N, 100); i++) 
	{
		cout << a2[i] << " ";
	} 
	cout << endl;
	cout << "Time taken : " <<dur.count() << " ms" <<endl;
	
	cout << "Array after parallel Merge sort: ";
	start = high_resolution_clock::now();
	merge_sort_parallel(a3, 0, N-1);
	end = high_resolution_clock::now();
	dur = duration_cast<microseconds>(end - start);
	for(int i = 0; i < min(N, 100); i++) 
	{
		cout << a3[i] << " ";
	} 
	cout << endl;
	cout << "Time taken : " <<dur.count() << " ms" <<endl; 
}

