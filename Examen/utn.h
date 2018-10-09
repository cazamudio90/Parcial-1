#ifndef UTN_H_INCLUDED
#define UTN_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int utn_getNombre(  char* pNombre,int limite, char* msg, char* msgErr, int reintentos);
int utn_isValidNombre(char* pBuffer,int limite);
int isValidEntero(char *pBuffer, int limite);
int utn_getEntero(  int *pEntero, int limite, char *mensaje,char *mensajeError, int reintentos);
int utn_getString(char* pBuffer, int limite);
int isValidSoloNumeros(char *pArray, int limite);
int utn_getNumeros(   int *pEntero, int limite, char *mensaje, char *mensajeError, int reintentos);
int pedirIndiceVacio(char* pArray, int len, int * indice);
#endif // UTN_H_INCLUDED
