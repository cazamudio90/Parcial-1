#ifndef AFICHES_H_INCLUDED
#define AFICHES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "clientes.h"
#include "afiches.h"
typedef struct
{
    int idAfiches;
    int cantidadAfiches;
    char nombreDeAfiche[51];
    char zona[51];
    int idCliente;
    char estado[51];
    int isEmpty;
}afiches;
int addAfiches (afiches* pArray,int limite, int id, int *idMostrarAfiches);
int initAfiches(afiches* pArray, int limite);
void printAfiches(afiches* pArray, int len);
int afi_modificarAfiches(afiches* pArray, int len, int id);
int afic_PorIDprintAfiches(afiches* pArray, int len, int *devID);
afiches* afi_getByIdCliente(afiches* pArrayAfi, int limiteAfi, int idCliente);
int afiche_ingresoForzado(afiches* pArray, int limite, int cantidadAfiches, char *zona,
                            char *estado,int idCliente);

#endif // AFICHES_H_INCLUDED
