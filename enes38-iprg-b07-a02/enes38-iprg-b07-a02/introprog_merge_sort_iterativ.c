#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "introprog_input_merge_sort.h"

/*
 * Diese Funktion fügt zwei bereits sortierte Arrays zu einem
 * sortierten Array zusammen
 *
 * array : Pointer auf das Array
 * first : Index des ersten Elemements (Beginn) des (Teil-)Array
 * middle: Index des mittleren Elements des (Teil-)Array
 * last  : Index des Letzten Elements (Ende) des (Teil-)Array
 */
void merge(int* array, int first, int middle, int last)
{
    // HIER Funktion merge() implementieren
  int* B = (int*) malloc((100000) * sizeof(int));   //Hilfsarray zum mergen (Länge: r-p+1 (last - first + 1))
  int k, m;         //Hilfvariablen, k für linke Seite. m für rechte Seite.
  int i;            //Laufvariable für das gemergte Array
  
  k = first;
  m = middle + 1;
  i = 1;
  
  while (k <= middle && m <= last) {
	if (array[k] <= array[m]) {
	    B[i] = array[k];
		k = k + 1;
	}  else {
		B[i] = array[m];
		m = m + 1;
	}
	i = i + 1;
  }
  while (k <= middle) {
	B[i] = array[k];
	k = k + 1;
	i = i + 1;
  }
  while (m <= last) {
	B[i] = array[m];
    m = m + 1;
 	i = i + 1;
  }
  int j = 1;
  
  while (j < i) {
	array[first + j - 1] = B[j];
	j = j + 1;
  }
  free(B);  //Speicher freigeben
}


int min (int a, int b) {      //min -> minimum = mittelpunkt von entweder berechnete Ergebnis oder n(länge des arrays)
	if (a < b) {
		return a;
	} else {
		return b;
	}
}


/*
 * Diese Funktion implementiert den iterativen Mergesort
 * Algorithmus auf einem Array. Sie soll analog zum Pseudocode
 * implementiert werden.
 *
 * array:  Pointer auf das Array
 * last :  Index des letzten Elements
 */
void merge_sort(int* array, int last)
{
    // HIER Funktion merge_sort() implementieren
	
	int step, left, middle, right;
	
	step = 1;
	while (step <= last) {
		left = 0;
		while (left <= last - step) {
			middle = left + step - 1;
			middle = min(middle, last);
			right = left + 2 * step - 1;
			right = min(right, last);
			merge(array, left, middle, right);
			left = left + 2 * step;
		}
		step = step * 2;
	}
}

/*
 * Hauptprogramm.
 *
 * Liest Integerwerte aus einer Datei und gibt diese sortiert im
 * selben Format über die Standardausgabe wieder aus.
 *
 * Aufruf: ./introprog_merge_sort_iterativ <maximale anzahl> \
 * 	   <dateipfad>
 */
int main (int argc, char *argv[])
{
    if (argc!=3){
        printf ("usage: %s <maximale anzahl>  <dateipfad>\n", argv[0]);
        exit(2);
    }
    
    char *filename = argv[2];
    
    // Hier array initialisieren
	int* array = (int*) malloc((100000) * sizeof(int));
    
    int len = read_array_from_file(array, atoi(argv[1]), filename);

    printf("Eingabe:\n");
    print_array(array, len);

    // HIER Aufruf von "merge_sort()"
	int last = len - 1;
	merge_sort(array, last);

    printf("Sortiert:\n");
    print_array(array, len);
	
	free(array);

    return 0;
}
