#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "introprog_structs_lists_input.h"

#define MAX_STR 255

/* Bewirkt, dass statt 'struct _element' auch 'element' verwendet
 * werden kann.
 */
typedef struct _element element; 

/* Bewirkt, dass statt 'struct _list' auch 'list' verwendet werden
 * kann.  Hier in einem geschrieben, so dass man auch 'list'
 * innerhalb der struct-Definition selbst verwenden kann.
 */
typedef struct _list { /* Separater Wurzelknoten */
    element *first;    /* Anfang/Kopf der Liste */
    int count;         /* Anzahl der Elemente */
} list;

/* HIER struct _element implementieren. */
typedef struct _element {       //Deklerationen
	    char title[MAX_STR];
	    char author[MAX_STR];
	    int year;
	    long long int isbn;
	    struct _element *next;
}element;

/* Fuege ein Element in die Liste ein, sodass die Liste aufsteigend
 * nach ISBN sortiert ist.  Dafür muss das erste Element ermittelt
 * werden, das in der bisher sortierten Liste eine ISBN besitzt,
 * die größer ist als die des neuen Elements.  Wenn die Liste leer
 * ist, soll das Element direkt an den Anfang platziert werden.
 *
 * first    - Pointer auf das erste Element (bzw. Anfang) der Liste
 * new_elem - Pointer auf das neues Element das in die Liste
 * eingefuegt werden soll
 *
 * Gib einen Pointer auf den neuen oder alten Anfang der Liste
 * zurueck.
 */
element* insert_sorted(element *first, element *new_elem) {
    /* HIER implementieren. */
	
	element* neuElement = new_elem;  //zu sortierendes neues Element deklariert
	if (first == NULL) {        //wenn first == 0, dann
		first = neuElement;     //wird neuElement = first
	} else {    
	    element *now = first;   //wenn first != 0, dann wird jetziger Elem in der Liste = first
	    element *before = NULL;    //und vorheriger Elem = 0
		while (now && now->isbn <= neuElement->isbn) {  //wenn jetziger Elem isbn kleiner gleich isbn von neuElement isbn
			before = now;           //dann wird vorheriger Elem zu jetziger Elem
			now = now->next;        //und jetziger Elem zu nächsten Elem
		}
		if (now == NULL) {          //WENN jetziger Elem = 0, dann
			before->next = neuElement;  //dann wird vorheriger der nächste neuElement
		} else if (before) {
			neuElement->next = before->next; //anderherum wird vorheriges/letztes Elem zu neuElement
			before->next = neuElement;
		} else {                 //wenn das auch nicht der Fall ist, dann
			neuElement->next = first;  //neuElement zu erstes Elem
			first = neuElement;
		}
	
	}
	return first;
}


/* Kreiere ein neues Element mit dynamischem Speicher.
 *
 * title  - Titel des Buches
 * author - Autor des Buches
 * year   - Erscheinungsjahr des Buches
 * isbn   - ISBN des Buches
 *
 * Gib einen Pointer auf das neue Element zurueck.
 */
element *construct_element(char *title, char* author, int year, long long int isbn) {
    /* HIER implementieren. */
	element *neu_element = (element*) malloc(sizeof(element));
	
	strncpy(neu_element->title, title, MAX_STR);
	neu_element->title[254]= '\0';
	
	strncpy(neu_element->author, author, MAX_STR);
	neu_element->author[254]= '\0';
	
	neu_element->year = year;
	neu_element->isbn = isbn;
	neu_element->next = NULL;
	return neu_element;
}

/* Gib den der Liste und all ihrer Elemente zugewiesenen
 * Speicher frei.
 */
void free_list(list *alist) {
    /* HIER implementieren. */
	element *new = alist->first;
	while (new != NULL) {
		element *save = new;
		new = new->next;
		free(save);     //*save freigegeben
		
	}
	free(alist);        //alist freigegeben
}

/* Lese die Datei ein und fuege neue Elemente in die Liste ein 
 * _Soll nicht angepasst werden_
 */
void read_list(char* filename, list *alist) {
    element* new_elem;
    char* title;
    char* author;
    int year;
    long long int isbn;
    read_line_context ctx;
    open_file(&ctx, filename);
    while(read_line(&ctx, &title, &author, &year, &isbn) == 0) {
        new_elem = construct_element(title, author, year, isbn);
        alist->first = insert_sorted(alist->first, new_elem);
        alist->count++;
    }
}

/* Erstelle die Liste:
 *  - Weise ihr dynamischen Speicher zu 
 *  - Initialisiere die enthaltenen Variablen
 * _Soll nicht angepasst werden_
 */
list* construct_list() {
    list *alist = malloc(sizeof(list));
    alist->first = NULL;
    alist->count = 0;
    return alist;
}

/* Gib die Liste aus:
 * _Soll nicht angepasst werden_
 */
void print_list(list *alist) {
    printf("Meine Bibliothek\n================\n\n");
    int counter = 1;
    element *elem = alist->first;
    while (elem != NULL) {
        printf("Buch %d\n", counter);
        printf("\tTitel: %s\n", elem->title);
        printf("\tAutor: %s\n", elem->author);
        printf("\tJahr:  %d\n", elem->year);
        printf("\tISBN:  %lld\n", elem->isbn);
        elem = elem->next;
        counter++;
    }
}

/* Main Funktion
 * _Soll nicht angepasst werden_
 */
int main(int argc, char** argv) {
    list *alist = construct_list();
    read_list(argc>1?argv[1]:"buecherliste.txt", alist);
    print_list(alist);
    free_list(alist);
    return 0;
}
