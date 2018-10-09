#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "clientes.h"
#include "afiches.h"
#define CANTIDAD_CLIENTES 100
#define CANTIDAD_AFICHES 1000
int main()
{
    clientes clientesArray[CANTIDAD_CLIENTES];
    afiches aficheArray[CANTIDAD_AFICHES];
    initClientes(clientesArray, CANTIDAD_CLIENTES);
    initAfiches(aficheArray, CANTIDAD_AFICHES);
    mostarMenu(clientesArray, CANTIDAD_CLIENTES,aficheArray, CANTIDAD_AFICHES);
    return 0;
}
