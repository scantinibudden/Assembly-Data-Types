#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "lib.h"

int main (void){  
    
    //TEST INTCMP///////////////////////////////////////////////////////////////////////

    bool res = true;
    for (int32_t i = 0; i < 10; i++){
        for (int32_t j = 5; j < 15; j++){
            int32_t c = 0;
            if(i < j) c = 1;
            else if (i == j) c = 0;
            else c = -1;

            res &= c == intCmp(&i, &j);
        }
        
    }

    printf("Test intCmp: %s\n", res ? "Paso el test" : "No paso el test");

    //TEST INTCLONE///////////////////////////////////////////////////////////////////////

    int32_t *temp[10];
    res = true;
    for (int32_t i = 0; i < (int)(sizeof(temp)/sizeof(temp[0])); i++){
        temp[i] = intClone(&i);
        res &= i == *temp[i];
    }
    
    printf("Test intClone: %s\n", res ? "Paso el test" : "No paso el test");

    //TEST INTDELETE///////////////////////////////////////////////////////////////////////

    for (int32_t i = 0; i < (int)(sizeof(temp)/sizeof(temp[0])); i++) {
        intDelete(temp[i]);
    }

    //TEST INTPRINT///////////////////////////////////////////////////////////////////////

    FILE *fp_int = fopen("int_print.txt", "w");
    int32_t a = 68;
    intPrint(&a, fp_int);
    fclose(fp_int);

    //TEST STRCMP///////////////////////////////////////////////////////////////////////

    char* s_1 = "sebas"; //mayor
    char* s_2 = "lucy"; //menor
    res = true;

    res = 0 == strCmp(s_1, s_1) && 1 == strCmp(s_2, s_1) && -1 == strCmp(s_1, s_2) && 0 == strCmp(s_2,s_2);

    printf("Test strCmp: %s\n", res ? "Paso el test" : "No paso el test");

    //TEST STRPRINT///////////////////////////////////////////////////////////////////////

    FILE *fp_str = fopen("str_print.txt", "w");
    char* s = "hola";
    strPrint(s, fp_str);
    fprintf(fp_str, "\n");
    char* sv = "";
    strPrint(sv, fp_str);
    fclose(fp_str);

    //TEST STRCLONE///////////////////////////////////////////////////////////////////////

    char* s_clon = strClone(s);
    printf("Test strClone: %s\n", s_clon);

    //TEST STRDELETE///////////////////////////////////////////////////////////////////////

    strDelete(s_clon);
    
    //TESTS ARRAY/////////////////////////////////////////////////////////////////////////

    //string

    uint8_t capacity_str = 3;
    type_t type = TypeString;
    array_t* array_str = arrayNew(type, capacity_str);
    char* str_1 = "lucy";
    char* str_2 = "y";
    char* str_3 = "sebas";
    arrayAddLast(array_str, str_1);
    arrayAddLast(array_str, str_2);
    arrayAddLast(array_str, str_3);
    arraySwap(array_str, 0, 2);
    uint8_t size_str = arrayGetSize(array_str);
    printf("Test arrayGetSize_str: %d\n", size_str);


    char* removed = (char*) arrayRemove(array_str, 2);
    printf("ARRAY REMOVED: %s\n", removed);
    strDelete(removed);
    FILE *fp_array = fopen("array_print.txt", "w");
    arrayPrint(array_str, fp_array);
    fprintf(fp_array, "\n");
    arrayDelete(array_str);

    printf("IMPRESO ARRAY STRINGS\n");

    //int
    uint8_t capacity_int = 5;
    type_t type_int = TypeInt;
    array_t *array_int = arrayNew(type_int, capacity_int);
    int32_t dato_1 = 4;
    int32_t dato_2 = 7;
    int32_t dato_3 = 6;
    arrayAddLast(array_int, &dato_1);
    arrayAddLast(array_int, &dato_2);
    arrayAddLast(array_int, &dato_3);
    arrayAddLast(array_int, &dato_3);
    arrayAddLast(array_int, &dato_1);
    int32_t* test = (int32_t*)arrayRemove(array_int, 3);
    intDelete(test);
    uint8_t size_int = arrayGetSize(array_int);
    printf("Test arrayGetSize_int: %d\n", size_int);

    arrayPrint(array_int, fp_array);
    fclose(fp_array);

    arrayDelete(array_int);

    // TEST LISTS ///////////////////////////////////////////////////////////////////////////

    type_t type_list = TypeInt;
    list_t* list = listNew(type_list);

    listAddFirst(list, &dato_1); //4 //lucy
    listAddFirst(list, &dato_2); //7 //y
    listAddFirst(list, &dato_3); //6 //sebas
    listAddFirst(list, &dato_3); //6 //sebas
    listAddFirst(list, &dato_1); //4 //lucy
    listAddFirst(list, &dato_1);  //4 //lucy
    listAddLast(list, &dato_3);
    listAddLast(list, &dato_1);

    uint8_t list_size = listGetSize(list);
    printf("Test listGetSize: %d\n", list_size);

    //listRemove(list, 0);
    //listRemove(list, 3);
    //listSwap(list, 4, 5);

    list_size = listGetSize(list);
    printf("Test listGetSize (post remove): %d\n", list_size);

    int32_t *test_list = (int32_t *)listRemove(list, 0);
    intDelete(test_list);

    list_t* lista_clon = listClone(list);

    FILE *fp_list = fopen("list_print.txt", "w");
    listPrint(list, fp_list);
    listPrint(lista_clon, fp_list);
    fprintf(fp_list, "\n");
    fclose(fp_list);

    listDelete(lista_clon);
    listDelete(list);


    //TEST CARDNEW, CARDGETSUIT, CARDGETNUMBER ////////////////////////////////////////////

    char* suit_1 = "basto";
    int32_t number_1 = 9;
    card_t* carta_1 = cardNew(suit_1, &number_1);
    char* suit_2 = "oro";
    int32_t number_2 = 5;
    card_t* carta_2 = cardNew(suit_2, &number_2);
    printf("Test cardCmp: %d\n", cardCmp(carta_1, carta_2));
    char *suit_3 = "copa";
    int32_t number_3 = 3;
    card_t *carta_3 = cardNew(suit_3, &number_3);

    cardAddStacked(carta_1, carta_2);
    cardAddStacked(carta_1, carta_3);
    
    card_t *card_clon_2 = cardClone(carta_2);
    cardAddStacked(card_clon_2, carta_1);

    card_t *card_clon_1 = cardClone(carta_1);
    cardAddStacked(card_clon_1, card_clon_2);
    cardAddStacked(card_clon_1, carta_3);

    FILE *fp_card = fopen("card_print.txt", "w");
    cardPrint(carta_2, fp_card);
    fprintf(fp_card, "\n");
    cardPrint(carta_1, fp_card);
    fprintf(fp_card, "\n");
    cardPrint(card_clon_1, fp_card);
    fclose(fp_card);

    cardDelete(card_clon_2);
    cardDelete(card_clon_1);
    cardDelete(carta_1);
    cardDelete(carta_2);
    cardDelete(carta_3);

    //TESTS OBLIGATORIOS


    //Crear un mazo con 5 cartas sobre un arreglo
    type_t tipo_array = TypeCard;
    type_t tipo_lista = TypeCard;
    int8_t capacidad_array = 5;
    array_t* array = arrayNew(tipo_array, capacidad_array);
    list_t* lista = listNew(tipo_lista);


    int32_t numero1 = 7;
    int32_t numero2 = 12;
    int32_t numero3 = 1;
    int32_t numero4 = 3;
    int32_t numero5 = 10;
    
    char* palo1 = "basto";
    char* palo2 = "oro";
    char* palo3 = "copa";
    char* palo4 = "espada";
    
    card_t* carta1 = cardNew(palo1, &numero1);
    card_t* carta2 = cardNew(palo2, &numero2);
    card_t* carta3 = cardNew(palo4, &numero3);
    card_t* carta4 = cardNew(palo3, &numero5);
    card_t* carta5 = cardNew(palo1, &numero4);

    arrayAddLast(array, carta1);
    arrayAddLast(array, carta2);
    arrayAddLast(array, carta3);
    arrayAddLast(array, carta4);
    arrayAddLast(array, carta5);

    listAddLast(lista, carta3);
    listAddLast(lista, carta4);
    listAddFirst(lista, carta2);
    listAddLast(lista, carta5);
    listAddFirst(lista, carta1);

    //Imprimir el mazo.
    FILE *fp = fopen("pruebas_cortas.txt", "w");
    arrayPrint(array, fp);
    fprintf(fp, "\n");
    listPrint(lista, fp);
    fprintf(fp, "\n");

    //Apilar una carta cualquiera del mazo sobre otra carta cualquiera.
    cardAddStacked(arrayGet(array, 2), arrayGet(array, 4));
    cardAddStacked(listGet(lista, 2), listGet(lista, 4));

    //Imprimir nuevamente el mazo.
    arrayPrint(array, fp);
    fprintf(fp, "\n");
    listPrint(lista, fp);

    //Borrar el mazo.
    fclose(fp);
    arrayDelete(array);
    listDelete(lista);
    cardDelete(carta1);
    cardDelete(carta2);
    cardDelete(carta3);
    cardDelete(carta4);
    cardDelete(carta5);

    printf("Pruebas cortas: listo\n");

    printf("FIN\n");

    return 0;
}




