#ifndef INFORMES_H_INCLUDED
#define INFORMES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "clientes.h"
#include "afiches.h"
int informar_clienteConMasVentas(void* arrayAfi, int limiteAfi,void* pArray, int limite);
int informar_clienteVentasCobradas(afiches* arrayAfi, int limiteAfi,clientes* pArray, int limite);


#endif // INFORMES_H_INCLUDED
