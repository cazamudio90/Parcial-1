#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "afiches.h"
#include "utn.h"
typedef struct
{
    int idClientes;
    char nombre[51];
    char apellidos[51];
    char cuit[15];
    int isEmpty;
}clientes;

int initClientes(clientes* pArray, int limite);
int addClientes (clientes* pArray,int limite, int* id);
int mostarMenu(clientes * pArray, int limite, afiches* pArrayAfic, int limiteAfi);
int cli_modificarCliente(clientes* pArray, int len, int id);
int cliente_mostrar(clientes* pArray, int limite);
int printClientesAfiches(clientes* pArray, int limite, afiches* pArrayAfi, int limiteAfi);
int cli_PorIDprintclie(clientes* pArray, int len, afiches * pArrayAfi, int limiteAfi, int *devID);
int cliente_ingresoForzado(clientes* pArray, int limite, char *nombre, char *apellidos, char *cuit);
#endif // CLIENTES_H_INCLUDED
