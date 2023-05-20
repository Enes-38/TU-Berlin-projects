#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>  // definiert den speziellen Wert NaN für floats
#include "introprog_input_stacks-rpn.h"

typedef struct _stack stack;
typedef struct _stack_element stack_element;

struct _stack {
    stack_element* top;
};

struct _stack_element {
    stack_element* next;
    float value;
};

/* 
 * Füge Element am Anfang des Stacks ein
 *
 * astack - Ein Pointer auf den Stack.
 * value  - Zahl, die als neues Element auf den Stack gelegt
 *          werden soll.
 */
void stack_push(stack* astack, float value)
{
    /* HIER implementieren */
	 stack_element *neues_element = (stack_element*) malloc(sizeof(stack_element));
	 neues_element -> value = value;
	 neues_element -> next = astack -> top;
	 astack -> top = neues_element;
}

/* 
 * Nehme das letzte eingefügte Element vom Anfang des Stacks
 * Gebe NaN zurück, wenn keine Element vorhanden ist.
 *
 * astack - Ein Pointer auf den Stack
 *
 * Gebe die im Element enthaltenen Zahl zurück
 */
float stack_pop(stack* astack)
{
    /* HIER implementieren */
	float first_elem;
	stack_element *pop_elem = astack -> top;
	if (pop_elem == NULL) {
		first_elem = NAN;   //Wenn kein Element vorhanden ist, wird hier NAN zurückgegeben
		return first_elem;
	}
	float sec_elem = pop_elem -> value;    //wenn if schleife Bedingung erfüllt wird bzw. wenn != NULL ist -
	astack -> top = astack -> top -> next;  //wird das zuletzt eingefügte Elem. vom Stack genommen -
	free(pop_elem);  //Speicher freigeben
	return sec_elem;          //und der Wert ausgegeben 
}

/*
 * Führt abhängig von dem Token eine entsprechende Operation auf
 * dem Stack aus.  Wenn es sich bei dem Token um
 *  -> eine Zahl handelt, dann konvertiere die Zahl mithilfe von
 *     atof() zu einem float und lege sie auf den Stack.
 *  -> einen Operator handelt, dann nehme zwei Zahlen vom Stack,
 *     führe die Operation aus und lege das Resultat auf den Stack.
 *  -> eine nichterkennbare Zeichenkette handelt, dann tue nichts.
 *
 * astack - Ein Pointer auf den Stack
 * token  - Eine Zeichenkette
 */
void process(stack* astack, char* token)
{
    /* HIER implementieren */
	float f1;
	float f2;
	
	if (is_number(token)) {    //wenn´s eine zahl ist
		f1 = atof(token);   //Zahl wird mit atof() in float umgewandelt
		stack_push(astack, f1);  //umgewandelte Zahl wird ins Stack gelegt
	}   else if (is_add(token)) {  //wenns ein Operator ist (+)
		   f1 = stack_pop(astack); //1. Zahl vom Stack
           f2 = stack_pop(astack); //2. Zahl vom Stack
		   stack_push(astack, f1 + f2);  //Resultat wird in Stack gelegt
	    }  else if (is_sub(token)) {  //wenns ein Operator ist (-)
		      f1 = stack_pop(astack);      // "
              f2 = stack_pop(astack);      // "
		      stack_push(astack, f2 - f1); // "
	        } else if (is_mult(token)) {  //wenns ein Operator ist (*)
		        f1 = stack_pop(astack);      // "
                f2 = stack_pop(astack);      // "
		        stack_push(astack, f1 * f2); // "
            }		
	
    printf("\n<Logik fehlt!>\n");
    return;
    /* Du kannst zur Erkennung der Token folgende Hilfsfunktionen
     * benutzen:
     *
     * Funktion          Rückgabewert von 1 bedeutet
     * ---------------------------------------------
     * is_add(token)     Token ist ein Pluszeichen
     * is_sub(token)     Token ist ein Minuszeichen
     * is_mult(token)    Token ist ein Multiplikationszeichen
     * is_number(token)  Token ist eine Zahl
     */
}

/* 
 * Debugausgabe des Stack
 * Diese Funktion kannst du zum debugging des Stack verwenden.
 *
 * astack - Ein Pointer auf den Stack
 */
void print_stack(stack *astack) {
    int counter = 0;
    printf("\n |xxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxx|\n");
    printf(" | Nr. | Adresse           | Next              | Wert    |\n");
    printf(" |-----|-------------------|-------------------|---------|\n");
    for (stack_element* elem=astack->top; elem != NULL; elem = elem->next) {
        printf(" | %3d | %17p | %17p | %7.3f |\n", counter, elem, elem->next, elem->value);
        counter++;
    }
    printf(" |xxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxxxxxxxxxxxx|xxxxxxxxx|\n");
}

/* 
 * Erstelle einen Stack mit dynamischem Speicher.
 * Initialisiere die enthaltenen Variablen.
 *
 * Gebe einen Pointer auf den Stack zurück.
 */
stack* stack_erstellen() {
    /* HIER implementieren */
	stack *stack_dynm_speicher = (stack*) malloc(sizeof(stack));
	stack_dynm_speicher -> top = NULL;
	return stack_dynm_speicher;
}

int main(int argc, char** args)
{
    stack* astack = stack_erstellen();
    char zeile[MAX_STR];
    char* token;

    intro();
    while (taschenrechner_input(zeile) == 0) {
        // Erstes Token einlesen
        token = strtok(zeile, " ");

        while (token != NULL) {
            printf("Token: %s\n", token);
            // Stackoperationen durchführen
            process(astack, token);
            // Nächstes Token einlesen
            token = strtok(NULL, " ");
            print_stack(astack);
        }

        printf("\nExtrahiere Resultat\n");
        float result = stack_pop(astack);
        print_stack(astack);

        if (astack->top != NULL) {
            while (astack->top != NULL) {
                stack_pop(astack);   //Räume Stack auf
            }
            printf("\nDoes not Compute: Stack nicht leer!\n");
        } else if (result != result) {
            printf("\nDoes not Compute: Berechnung fehlgeschlagen!\n");
        } else {
            printf("\nDein Ergebnis:\t%7.3f\n\n", result);
        }
    }
    free(astack);
}
