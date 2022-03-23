/*
* Student: Spaczai Carla Noemi
* Grupa: 30229
* Am implementat 3 algoritmi de sortare: Insertion Sort, Selection Sort, Bubble Sort.
*
* Primul algoritm implementat este Insertion Sort. Acesta imparte sirul in doua parti. Prima parte e sortata, iar cea de a doua nu este sortata. Algoritmul parcurge
* sirul, alege cate un element si il insereaza la locul lui in prima parte, cea sortata.
* Complexitate: O(n^2). Complexitate Worst Case: O(n^2). Complexitate Best Case: O(n).
* Algoritmul e stabil. (Prin intermediul comparatiei '>'.)
*
* Al doilea algoritm implementat este Selection Sort. Acesta imparte sirul in doua parti. Prima parte e sortata, iar cea de a doua nu este sortata. De data aceasta,
* focusul cade asupra partii nesortate. Algoritmul parcurge sirul, alege minimul din cea de a doua parte si il insereaza la finalul primei parti.
* Complexitate: O(n^2). Complexitate Worst Case: O(n^2). Complexitate Best Case: O(n^2).
* Algoritmul nu e stabil. (Din cauza interschimbarii.)
*
* Al treilea algoritm implementat este Bubble Sort. Acesta parcurge sirul de mai multe ori si compara 2 cate 2 elemente de pe pozitii consecutive. Daca cele 2
* elemente nu sunt ordonate, vor fi interschimbate.
* Complexitate: O(n^2). Complexitate Worst Case: O(n^2). Complexitate Best Case: O(n^2).
* Algoritmul e stabil. (Prin intermediul comparatiei '>'.)
* 
* Comparand cei 3 algoritmi de sortare observam ca:
* Cel mai eficient algoritm in Worst Case este Selection Sort, iar cel mai ineficient este Bubble Sort.
* Cel mai eficient algoritm in Best Case este Bubble Sort, iar cel mai ineficient este Selection Sort.
* Cel mai eficient algoritm in Average Case este Insertion Sort, iar cel mai ineficient este Bubble Sort.
*/

#include <stdio.h>
#include "Profiler.h"

Profiler p("SORTING");

#define MAX_SIZE 1000
#define STEP_SIZE 100
#define NR_TESTS 5

void insertionSort(int v[], int n)
{
	Operation opComp = p.createOperation("Insertion_C", n);
	Operation opAttr = p.createOperation("Insertion_A", n);

	int key, j;
	for (int i = 1; i < n; i++)
	{
		opAttr.count();
		key = v[i];
		j = i - 1;
		opComp.count();
		while (j >= 0 && v[j] > key)
		{
			opAttr.count();
			v[j + 1] = v[j];
			j = j - 1;
		}
		opAttr.count();
		v[j + 1] = key;
	}
}

void selectionSort(int v[], int n)
{
	Operation opComp = p.createOperation("Selection_C", n);
	Operation opAttr = p.createOperation("Selection_A", n);

	for (int i = 0; i < n; i++)
	{
		int key = i;
		for (int j = i + 1; j < n; j++)
		{
			opComp.count();
			if (v[j] < v[key])
			{
				key = j;
			}
		}
		if (i != key)
		{
			opAttr.count(3);
			int x = v[i];
			v[i] = v[key];
			v[key] = x;
		}
	}
}

void BubbleSort(int v[], int n)
{
	Operation opComp = p.createOperation("Bubble_C", n);
	Operation opAttr = p.createOperation("Bubble_A", n);

	for (int i = 0; i < n - 1; i++)
	{
		int y = 0;
		for (int j = 0; j < n - i - 1; j++)
		{
			opComp.count();
			if (v[j] > v[j + 1])
			{
				y = y + 1;
				opAttr.count(3);
				int x = v[j];
				v[j] = v[j + 1];
				v[j + 1] = x;
			}
		}
		if (y == 0)
		{
			break;
		}
	}
}

void demo()
{
	int v[] = { 7, 2, 8, 9, -1, 2, 4, 1, 3, 6 };
	int n = sizeof(v) / sizeof(v[0]);

	//insertionSort(v, n);
	//printf("Insertion Sort: ");
	//selectionSort(v, n);
	//printf("Selection Sort: ");
	BubbleSort(v, n);
	printf("Bubble Sort: ");

	for (int i = 0; i < n; i++)
	{
		printf("%d ", v[i]);
	}
}

void perf(int order)
{
	int v1[MAX_SIZE], v2[MAX_SIZE], v3[MAX_SIZE];
	int n;
	for (n = STEP_SIZE; n <= MAX_SIZE; n += STEP_SIZE)
	{
		for (int test = 0; test < NR_TESTS; test++)
		{
			FillRandomArray(v1, n, 10, 50000, false, order);
			CopyArray(v2, v1, n);
			CopyArray(v3, v1, n);
			insertionSort(v1, n);
			selectionSort(v2, n);
			BubbleSort(v3, n);
		}
	}

	p.divideValues("Insertion_A", NR_TESTS);
	p.divideValues("Insertion_C", NR_TESTS);
	p.addSeries("Insertion", "Insertion_A", "Insertion_C");

	p.divideValues("Selection_A", NR_TESTS);
	p.divideValues("Selection_C", NR_TESTS);
	p.addSeries("Selection", "Selection_A", "Selection_C");

	p.divideValues("Bubble_A", NR_TESTS);
	p.divideValues("Bubble_C", NR_TESTS);
	p.addSeries("Bubble", "Bubble_A", "Bubble_C");

	p.createGroup("Sort_A", "Insertion_A", "Selection_A", "Bubble_A");
	p.createGroup("Sort_C", "Insertion_C", "Selection_C", "Bubble_C");
	p.createGroup("Total", "Insertion", "Selection", "Bubble");

	p.showReport();
}

void perf_all()
{
	perf(UNSORTED);
	p.reset("Best Case");
	perf(ASCENDING);
	p.reset("Worst Case");
	perf(DESCENDING);
	p.showReport();
}

int main()
{
	demo();
	//perf_all();
	return 0;
}