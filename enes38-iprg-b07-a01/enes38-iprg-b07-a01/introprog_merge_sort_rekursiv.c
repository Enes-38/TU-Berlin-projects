#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "introprog_input_merge_sort.h"

/*
 * Diese Funktion fügt zwei bereits sortierte Arrays zu einem
 * sortierten Array zusammen
 *
 * array : Pointer auf das Array
 * first : Index des ersten Elements (Beginn) des (Teil-)Array
 * middle: Index des mittleren Elements des (Teil-)Array
 * last  : Index des letzten Elements(Ende) des (Teil-)Array
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

/*
 * Diese Funktion implementiert den rekursiven Mergesort
 * Algorithmus auf einem Array. Sie soll analog zum Pseudocode
 * implementiert werden.
 *
 * array: Pointer auf das Array
 * first: Index des ersten Elements des (Teil-)Array
 * last:  Index des letzten Elements des (Teil-)Array
 */
void merge_sort(int* array, int first, int last)
{
  // HIER Funktion merge_sort() implementieren
  
  if (first < last) {                    //wenn first kleiner als last ist, dann
	int middle = ((first + last)/2);    //die Mitte durch abrunden finden
    merge_sort(array, first, middle);        //hier wird die linke Seite sortiert
	merge_sort(array, middle + 1, last);    //hier wird die rechte Seite sortiert 
	merge(array, first, middle, last); //Seiten werden zusammengeführt
  }
}

/*
 * Hauptprogramm.
 *
 * Liest Integerwerte aus einer Datei und gibt diese sortiert im
 * selben Format über die Standardausgabe wieder aus.
 *
 * Aufruf: ./introprog_merge_sort_rekursiv <maximale anzahl> \
 *         <dateipfad>
 */
int main (int argc, char *argv[])
{
    if (argc!=3){
        printf ("usage: %s <maximale anzahl>  <dateipfad>\n", argv[0]);
        exit(2);
    }
    
    char *filename = argv[2];
    
	//int array[100000]; 1. variante
	int* array = (int*) malloc((100000) * sizeof(int)); //2. variante mit dynamisch allotierten Speicher
    // Hier array initialisieren
    
    int len = read_array_from_file(array, atoi(argv[1]), filename);

    printf("Eingabe:\n");
    print_array(array, len);

    // HIER Aufruf von "merge_sort()"
	int first = 0;
    int last = len - 1;
	merge_sort(array, first, last);

    printf("Sortiert:\n");
    print_array(array, len);
	
	free(array);  //speicher freigeben

    return 0;
}
