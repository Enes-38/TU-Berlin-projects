#include <stdio.h>
#include <stdlib.h>
#include "arrayio.h"

int MAX_LAENGE = 1000;
int MAX_VALUE = 100;


void count_sort_calculate_counts(int input_array[], int len, int count_array[]) {
    /* Hier Funktion implementieren */
	for (int i = 0; i < MAX_LAENGE; i++) {
		count_array[i] = 0;            //count_array wird initialisiert
	}
	
	for (int j = 0; j < len; j++) {
		count_array[input_array[j]] = count_array[input_array[j]] + 1;   //wird gezählt wie häufig, jedes Elem. vorkommt
	}
}

void count_sort_write_output_array(int output_array[], int len, int count_array[]) {
    /* Hier Funktion implementieren */
	int k = 0;
	for (int j = 0; j < MAX_LAENGE; j++) {
		for (int i = 0; i < count_array[j]; i++) {     //Dementsprechen werden die Elem. nach der Reihe ihrer Häufigkeiten hineingefügt
			output_array[k] = j;
			k = k + 1;
		}
	}
}



int main(int argc, char *argv[]) {

   if (argc < 2){
        printf("Aufruf: %s <Dateiname>\n", argv[0]);
        printf("Beispiel: %s zahlen.txt\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];

    int input_array[MAX_LAENGE];
    int len = read_array_from_file(input_array, MAX_LAENGE, filename);

    printf("Unsortiertes Array:");
    print_array(input_array, len);

    /*
     * Hier alle nötigen Deklarationen und Funktionsaufrufe für
     * Countsort einfügen!
     */
     int count_array[MAX_LAENGE + 1];   //bekommt MAX_LAENGE + 1 Speicher/Kapazität reserviert//muss immer größer sein als out- und input array
	 int output_array[MAX_VALUE];        //bekommt MAX_LAENGE Speicher/Kapazität reserviert
	 
	 count_sort_calculate_counts(input_array, len, count_array);       //die Häufigkeiten der Berechnungen werden hier ausgeführt
	 count_sort_write_output_array(output_array, len, count_array);    //Hier wird das sortierte Array ausgeschrieben

    printf("Sortiertes Array:");

    /* Folgende Zeile einkommentieren, um das Array auszugeben! */
    // print_array(output_array, len);
	 print_array(output_array, len);
	 
	 

    return 0;
}
