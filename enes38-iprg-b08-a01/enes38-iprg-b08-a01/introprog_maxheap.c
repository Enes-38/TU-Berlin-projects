#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "introprog_heap.h"

/* Reserviere Speicher für einen Heap
 *
 * Der Heap soll dabei Platz für capacity Elemente bieten.
 *
 * Um konsistent mit den Parametern für malloc zu sein, ist
 * capacity als size_t (entspricht unsigned long auf x86/64)
 * deklariert.
 * Da es sauberer ist, sind auch alle Indizes in dieser Aufgabe
 * als size_t deklariert. Ob man size_t oder int als Index für
 * ein Array verwendet, macht in der Praxis (auf x86/64) nur
 * bei Arrays mit mehr als 2.147.483.647 Elementen einen
 * Unterschied.
 */
heap* heap_create(size_t capacity) {
	heap * new_heap = malloc(sizeof(heap));       //dynamischer Speicher (reserviert) und neuer heap
	
    new_heap -> capacity = capacity;
    new_heap -> size = 0;
    new_heap -> elements = (int*)malloc((new_heap -> capacity) * sizeof(int));
	
    return new_heap;
}


/* Stellt die Heap Bedingung an Index i wieder her
 *
 * Vorraussetzung: Der linke und rechte Unterbaum von i
 * erfüllen die Heap-Bedingung bereits.
 */
void heapify(heap* h, size_t i) {
	size_t left = (2 * i + 1);
	size_t right = (2 * i + 2);
	size_t largest;
	size_t swap;
	
	if (left < h -> size && h -> elements[left] > h -> elements[i]) {
		largest = left;
	} else {
		largest = i;
	}
	if (right < h -> size && h -> elements[right] > h -> elements[largest]) {
		largest = right;
	}
	if (largest != i) {
		swap = h -> elements[i];    //Da hier die Werte getauscht werden, wird der Wert in eine 3. Variable gespeichert (swap), dann wieder zu (largest)
		h -> elements[i] = h -> elements[largest];
		h -> elements[largest] = swap;
		heapify(h, largest);
	} 
}

/* Holt einen Wert aus dem Heap
 *
 * Wenn der Heap nicht leer ist, wird die größte Zahl
 * zurückgegeben. Wenn der Heap leer ist, wird -1 zurückgegeben.
 */
int heap_extract_max(heap* h) {
	
	if (h -> size < 1) {
		return -1;	     //return -1, weil kein Element vorhanden ist
	}
	size_t max = h -> elements[0];
    h -> elements[0] = h -> elements[h -> size - 1];
	h -> size = h -> size - 1;
	heapify(h, 0);
	return max;
}

/* Fügt einen Wert in den Heap ein
 *
 * Wenn der Heap bereits voll ist, wird -1 zurückgegeben.
 */
int heap_insert(heap* h, int key) {
	size_t i;
	//size_t parent = (i - 1) / 2;
	
	if (h -> size < h -> capacity) {
	h -> size = h -> size + 1;
	i = h -> size - 1;
	while (i > 0 && h -> elements[(i - 1) / 2] < key) {
		h -> elements[i] = h -> elements[(i - 1) / 2];
		i = (i - 1) / 2;
	   }
	h -> elements[i] = key;
	} else {
		return -1;
	}
	
	return 0;
}

/* Gibt den Speicher von einem Heap wieder frei
 */
void heap_free(heap* h) {
	free(h -> elements);         //speicher freigeben
	free(h);
	
}
