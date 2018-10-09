#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "clientes.h"
#include "afiches.h"

/**
* \brief    Se utiliza esta funcion para obtener un nuevo id
*           declarando una variable static para el id y suma 1 al anterior
* \return devuelve un id nuevo
*/
static int getNextId()
{
    static int ultimoId=-1;
    ultimoId++;
    return ultimoId;
}
/**
* \brief    funcion que busca un lugar vacio y devuelve un indice
* \param pArray Es el array que se recorre de afiches
* \param limite Es el limite de afiches que puede guardar el array
* \return El retorno es 0 si se mostraron los datos, si no el retorno es -1.
*/
static int buscaLugarVacio(afiches* pArray, int limite)
{
    int retorno = -1;
    int i;
    if(pArray != NULL && limite > 0)
    {
        for(i=0;i<limite;i++)
        {
            if(pArray[i].isEmpty)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}
int afiche_ingresoForzado(afiches* pArray, int limite, int cantidadAfiches, char *zona, char *estado,int idCliente)
{
    int retorno = -1;
    int indice;
    indice = buscaLugarVacio(pArray,limite);
    if( pArray != NULL && limite > 0 && zona != NULL &&
        estado != NULL)
    {
        pArray[indice].idAfiches = getNextId();
        strncpy(pArray[indice].zona, zona, 51);
        strncpy(pArray[indice].estado, estado, 51);
        pArray[indice].cantidadAfiches = cantidadAfiches;
        pArray[indice].isEmpty = 1;
        retorno = 0;
    }
    return retorno;
}
/** \brief inicializa el array en 0 para verificar que esten vacios
* \param pArray cadenar a recorrer
* \param limite es el limite de la cadena
* \return 0 si inicializa -1 si no
*/
int initAfiches(afiches* pArray, int limite)
{
	int retorno = -1;
	if(pArray != NULL && limite > 0)
	{
		for (int i = 0; i <= limite; i++)
		{
			pArray[i].isEmpty = 0;
			retorno = 0;
		}
	}
	return retorno;
}
/** \brief funcion para agregar afiche
* \param pArray cadenar a recorrer
*\param limite es el limite de la cadena
*\param id te devuelve el id del cliente agregado
*\return si agrega un afiche retorno 0 sino -1
*/
int addAfiches (afiches* pArray,int limite, int id ,int *idMostrarAfiches)
{
	int retorno = -1;
	int i;
	//23int bufferIdClientes;
	int cantidadAfiches;
	char bufferNombreAfiche[51];
	char bufferZona[51];
//    __fpurge(stdin);
	if(pArray != NULL && limite > 0)
	{
		for (i = 0; i<limite; i++ )
		{
			if (pArray[i].isEmpty == 0 &&
                //utn_getEntero(&bufferIdClientes, 10, "Ingrese id\n","No es un id valido \n", 3) == 0 &&
                utn_getEntero(&cantidadAfiches, 10, "Ingrese cantidad de afiches \n","cantidad invalida \n", 3) == 0 &&
				utn_getNombre( bufferNombreAfiche, 51, "Ingresar nombre de afiche\n","No es un nombre valido\n", 3) == 0 &&
				utn_getNombre( bufferZona, 51, "Ingresar zona\n","No es una zona valido\n", 3) == 0)
			{
				pArray[i].idAfiches = getNextId();
				*idMostrarAfiches = pArray[i].idAfiches;
				pArray[i].cantidadAfiches = cantidadAfiches;
				strncpy(pArray[i].nombreDeAfiche, bufferNombreAfiche, 51);
				strncpy(pArray[i].zona, bufferZona, 15);
				strncpy(pArray[i].estado, "a cobrar", 51);
				pArray[i].idCliente = id;
				pArray[i].isEmpty =  1;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
* \brief    Toma la cadena e imprime lo que tenga guardado
* \param pArray Recibe el array ingresado
* \param limite Es el tamano maximo del string
*/
void printAfiches(afiches* pArray, int len)
{
      if (pArray != NULL && len > 0)
      {
      	for (int i =0; i< len; i++ )
		{
			if(pArray[i].isEmpty == 1)
            {
                printf("Id de afiche %d\n", pArray[i].idAfiches);
                printf("cantidad de afiches %d\n", pArray[i].cantidadAfiches);
                printf("nombre de afiche  %s\n", pArray[i].nombreDeAfiche);
                printf("zona %s\n", pArray[i].zona);
                printf("estado %s\n", pArray[i].estado);
                printf("id de Cliente %d\n", pArray[i].idCliente);
                printf("---------------------------------\n");
            }
        }
      }
}
/**
* \brief    imprime por id
* \param pArray Recibe el array ingresado
* \param len Es el tamano maximo del string
*\param devID devuelve el id del afiche
*\param retorna 0 si esta bien sino -1
*/
int afic_PorIDprintAfiches(afiches* pArray, int len, int *devID)
{
    int retorno = -1;
    int bufferIdVenta;
      if (pArray != NULL && len > 0)
      {
			if(utn_getEntero(&bufferIdVenta, 10, "Ingrese id de venta \n","No es un id valido \n", 3) == 0 &&
                pArray[bufferIdVenta].isEmpty == 1 )
            {
                printf("Id %d\n", pArray[bufferIdVenta].idAfiches);
                printf("cantidad de afiches %d\n", pArray[bufferIdVenta].cantidadAfiches);
                printf("nombre de afiche  %s\n", pArray[bufferIdVenta].nombreDeAfiche);
                printf("zona %s\n", pArray[bufferIdVenta].zona);
                printf("estado %s\n", pArray[bufferIdVenta].estado);
                printf("id Cliente %d\n", pArray[bufferIdVenta].idCliente);
                printf("---------------------------------\n");
                *devID = bufferIdVenta;
                retorno = 0;
            }
      }
    return retorno;
}
/**
* \brief    funcion para modificar afiches
* \param pArray Recibe el array ingresado
* \param len Es el tamano maximo del string
*\param id que se le pasa para modificar
* \return En caso de exito retorna 0, si no -1
*/
int afi_modificarAfiches(afiches* pArray, int len, int id)
{
    int retorno = -1;
    int bufferCantidadAfiches;
    char bufferZona[51];
    if(pArray != NULL && len > 0 && len>0 && id >= 0 && id < len )
    {
        if (pArray[id].isEmpty == 1 &&
            utn_getEntero(&bufferCantidadAfiches, 8, "Modifique la cantidad de afiches \n","Cantidad invalido \n", 3) == 0 &&
            utn_getNombre( bufferZona, 51, "Modifique zona\n","No es una zona valido\n", 3) == 0)
        {
            pArray[id].cantidadAfiches = bufferCantidadAfiches;
            strncpy(pArray[id].zona, bufferZona, 51);
            printf("cliente modicado\n");
            retorno = 0;
        }else
        {
            printf("No existe id\n");
        }
    }
return retorno;
}
/**
* \brief    Se utiliza esta funcion para encontrar un venta a través de un id de cliente,
*           recorriendo el array y comparando los id
* \param arrayVentas Es el array que se recorre
* \param lenVentas Es el limite de ventas que puede guardar el array
* \param idCliente Es el id con que se compara cada idCliente del array
* \return   retorna la direccion de la struct del venta donde se encontro el id,
*           si no el retorno es NULL.
*/
afiches* afi_getByIdCliente(afiches* pArrayAfi, int limiteAfi, int idCliente)
{
    afiches * retorno = NULL;
    int i;
    if(pArrayAfi != NULL && limiteAfi > 0)
    {
        for(i=0;i<limiteAfi;i++)
        {
            if(pArrayAfi[i].isEmpty==1 && pArrayAfi[i].idCliente == idCliente)
            {
                retorno = &pArrayAfi[i];
                break;
            }
        }
    }
    return retorno;
}

