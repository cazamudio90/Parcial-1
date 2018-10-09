#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "utn.h"
#include "clientes.h"
#include "afiches.h"
#include "informes.h"
/**
* \brief    Se utiliza esta funcion para obtener un nuevo id
*           declarando una variable static para el id y suma 1 al anterior
* \return devuelve un id vacio
*/
static int getNextId()
{
    static int ultimoId=-1;
    ultimoId++;
    return ultimoId;
}
/**
* \brief    Se utiliza esta funcion para obtener un lugar vacio
*
* \return devuelve un id nuevo
*/

static int buscaLugarVacio(clientes* pArray, int limite)
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
/** \brief inicializa el array en 0 para verificar que esten vacios
* \ pArray cadenar a recorrer
*\ limite es el limite de la cadena
*/
int initClientes(clientes* pArray, int limite)
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

int cliente_ingresoForzado(clientes* pArray, int limite, char *nombre, char *apellidos, char *cuit)
{
    int retorno = -1;
    int indice;
    indice = buscaLugarVacio(pArray,limite);
    if( pArray != NULL && limite > 0 && nombre != NULL &&
        apellidos != NULL && cuit != NULL)
    {
        strncpy(pArray[indice].nombre, nombre, 51);
        strncpy(pArray[indice].apellidos, apellidos, 51);
        strncpy(pArray[indice].cuit, cuit, 20);
        pArray[indice].idClientes = getNextId();
        pArray[indice].isEmpty = 0;
        retorno = 0;
    }
    return retorno;

}
/** \brief funcion para agregar clientes
* \param pArray cadenar a recorrer
*\param limite es el limite de la cadena
*\param id te devuelve el id del cliente agregado
*\return si agrega un cliente retorno 0 sino -1
*/
int addClientes (clientes* pArray,int limite, int* id)
{
	int retorno = -1;
	int i;
	char bufferNombre[51];
	char bufferApellido[51];
	char bufferCuit[15];
    __fpurge(stdin);
	if(pArray != NULL && limite > 0)
	{
		for (i = 0; i<limite; i++ )
		{
			if (pArray[i].isEmpty == 0 &&
				utn_getNombre( bufferNombre, 51, "Ingresar nombre de cliente\n","No es un nombre valido\n", 3) == 0 &&
				utn_getNombre( bufferApellido, 51, "Ingresar apellido de cliente\n","No es un apellido valido\n", 3) == 0 &&
				utn_getNumeros(bufferCuit, 15,"Ingresar cuit de cliente\n", "No es un cuit valido", 3) == 0)
			{
				pArray[i].idClientes = getNextId();
				*id = pArray[i].idClientes;
				strncpy(pArray[i].nombre, bufferNombre, 51);
				strncpy(pArray[i].apellidos, bufferApellido, 51);
				strncpy(pArray[i].cuit, bufferCuit, 15);
				pArray[i].isEmpty =  1;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/**
* \ brief    Toma la cadena y evalua si es un nombre
* \ pArray   array a recorre
* \ len    limite del array
* \ id    toma el id del cliente a modificar
* \return En caso de exito retorna 0, si no -1
*/
int cli_modificarCliente(clientes* pArray, int len, int id)
{
    int retorno = -1;
    char bufferNombre[51];
    char bufferApellido[51];
    char bufferCuit[15];
    if(pArray != NULL && len > 0 && len>0 && id >= 0 && id < len )
    {
        if (pArray[id].isEmpty == 1 &&
            utn_getNombre(bufferNombre, 51, "Modifique Nombre\n", "No es un nombre valido\n", 2)==0 &&
            utn_getNombre( bufferApellido, 51, "Modifique apellido del cliente\n","No es un apellido valido\n", 3) == 0 &&
            utn_getNumeros(bufferCuit, 51,"Ingresar cuit de cliente\n", "No es un cuit valido", 3) == 0)
        {
            strncpy(pArray[id].nombre, bufferNombre, 51);
            strncpy(pArray[id].apellidos, bufferApellido, 51);
            strncpy(pArray[id].cuit, bufferCuit, 15);
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
* \brief    evalua el id ingresado y en caso de exito y de haber informacion en ese id
*           borra la informacion
* \param pArray Recibe el array ingresado
* \param id es el numero a buscar
* \param limite Es el tamano maximo del string
*/
int cli_borrarCliente(clientes* pArray, int len, int id)
{
	int retorno = -1;
	char resp;
    if(pArray != NULL && len > 0 && len>0 && id >= 0 )
	{
		if (pArray[id].isEmpty == 1)
		{
			 printf("Esa seguro de borrar al cliente Y/N");
			 scanf("%c", &resp);
			 if (resp == 'Y')
			 {
                pArray[id].isEmpty = 0;
                retorno = 0;
			 }
			 else
			 {
                retorno = 1;
			 }
		}else
		{
			printf("No hay empleado con ese id\n");
		}
	}
  return retorno;
}
/** \brief funcion que recibe 2 arrays e imprime la informacion del cliente
*\param pArray array de clientes que se recorre
*\param len limite de pArray
*\param pArrayAfi array de afiches que se recorre
*\param limiteAfi limite de pArrayAfi
**/
int cli_PorIDprintclie(clientes* pArray, int len, afiches * pArrayAfi, int limiteAfi, int *devID)
{
    int retorno = -1;
    int i,j,auxIdCliente;
    int bufferIdVenta;
      if (pArray != NULL && len > 0)
      {
			if(utn_getEntero(&bufferIdVenta, 10, "Ingrese id de venta \n","No es un id valido \n", 3) == 0 &&
                pArrayAfi[bufferIdVenta].isEmpty == 1 )
             {
                 for (i = 0; i< limiteAfi; i++)
                 {
                    if (pArrayAfi[i].idAfiches == bufferIdVenta)
                    {
                       auxIdCliente = pArrayAfi[i].idCliente;
                       break;

                    }
                 }
                        for (j = 0; j< len; j++)
                        {
                            if (pArray[j].idClientes == auxIdCliente)
                            {
                                printf("Id %d\n", pArray[j].idClientes);
                                printf("Nombre %s\n", pArray[j].nombre);
                                printf("Apellido  %s\n", pArray[j].apellidos);
                                printf("Cuit %s\n", pArray[j].cuit);
                                printf("---------------------------------\n");
                                *devID = bufferIdVenta;
                                retorno = 0;
                                break;
                            }
                        }
             }
      }
    return retorno;
}
/**
* \brief    Se utiliza esta funcion para mostrar todos los datos de los
*           clientes del array
* \param arrayClientes Es el array que se recorre
* \param lenClientes Es el limite de clientes que puede guardar el array
* \return El retorno es 0 si se mostraron los datos, si no el retorno es -1.
*/
int cliente_mostrar(clientes* pArray, int limite)
{
    int retorno = -1;
    int i;
    if(pArray != NULL && limite > 0)
    {
        for(i=0;i<limite;i++)
        {
            if(pArray[i].isEmpty == 1)
            {
                printf("ID: %d\nNombre: %s\nApellido: %s\nCuit: %s\n",
                pArray[i].idClientes,pArray[i].nombre, pArray[i].apellidos,
                pArray[i].cuit );
            }
        }
        retorno = 0;
    }
    return retorno;
}
/**
* \brief    imprime los clientes segun el id de venta
* \param pArray Es el array que se recorre
* \param limite Es el limite de clientes que puede guardar el array
* \param pArrayAfi Es el array que se recorre
* \param limiteAfi Es el limite de clientes que puede guardar el array
* \return El retorno es 0 si se mostraron los datos, si no el retorno es -1.
*/
int printClientesAfiches(clientes* pArray, int limite, afiches* pArrayAfi, int limiteAfi)
{
   int i;
   int j;
   int retorno;
   int contadorAfiches = 0;
    if(pArray != NULL && limite > 0 && pArrayAfi != NULL && limiteAfi > 0)
    {
        for(i= 0; i< limite; i++)
        {
            if(pArray[i].isEmpty == 1)
            {
                printf("id %d\n", pArray[i].idClientes);
                printf("Nombre:  %s\n", pArray[i].nombre);
                printf("Apellido: %s\n", pArray[i].apellidos);
                printf("Cuit: %s\n", pArray[i].cuit);
                retorno = 0;
                break;
            }
          }
        for (j=0; j< limiteAfi; j++)
            {
                if(pArrayAfi[j].isEmpty == 1 && pArrayAfi[j].idCliente == pArray[i].idClientes && strcmp(pArrayAfi[j].estado,"a cobrar")== 0)
                {
                    contadorAfiches++;
                    retorno = 0;
                }
            }

        printf("cantidad: %d\n", contadorAfiches);
    }
    return retorno;
}
/**
* \brief    funcion de menu
* \param pArray Es el array que se recorre de clientes
* \param limite Es el limite de clientes que puede guardar el array
* \param pArrayAfi Es el array que se recorre de afiches
* \param limiteAfi Es el limite de afiches que puede guardar el array
* \return El retorno es 0 si se mostraron los datos, si no el retorno es -1.
*/
int mostarMenu(clientes * pArray, int limite,afiches* pArrayAfic, int limiteAfi)
{
    int retorno = -1;
    int resp;
    char resp2;
    int bufferID, idMostrarAfiches;
    int modificarCliente, borrarCliente,idVenta,idVentaprint;
    do
    {
        printf("1- Alta cliente\n");
        printf("2- Modificar cliente\n");
        printf("3- baja cliente\n");
        printf("4- Ingrese ventas\n");
        printf("5- Editar ventas\n");
        printf("6- Cobrar ventas\n");
        printf("7- imprimir clientes\n");
        printf("8- cliente con mas ventas a cobrar\n");
        printf("16- Salir\n");

        __fpurge(stdin);
        scanf("%d", &resp);
        switch(resp)
        {
            case 1:
            if(addClientes (pArray, limite, &bufferID) == 0)
            {
                printf("clientes ingresado, id %d\n", bufferID);
            }
            break;
            case 2:
            __fpurge(stdin);
            if (utn_getEntero(&modificarCliente, 10, "Ingrese id\n","No es un id valido \n", 3) == 0 &&
                         cli_modificarCliente( pArray, limite, modificarCliente) == 0)
            {
                printf("Cliente Modificado\n");
            }
            break;
            case 3:
            __fpurge(stdin);
            if (utn_getEntero(&borrarCliente, 10, "Ingrese id\n","No es un id valido \n", 3) == 0 &&
                cli_borrarCliente(pArray, limite, borrarCliente) == 0)
                {
                    printf("cliente Borrado\n");
                    break;
                }else if (utn_getEntero(&borrarCliente, 10, "Ingrese id\n","No es un id valido \n", 3) == 0 &&
                            cli_borrarCliente(pArray, limite, borrarCliente) == 1)
                            {
                                printf("No se borro Cliente\n");
                                break;
                            }
            case 4:
            __fpurge(stdin);
            if(utn_getEntero(&idVenta, 10, "Ingrese id de cliente\n","No es un id valido \n", 3) == 0 &&
                pArray[idVenta].isEmpty == 1 && addAfiches(pArrayAfic, limiteAfi, idVenta, &idMostrarAfiches) == 0)
                {
                    printf("venta ingresada, id %d\n", idMostrarAfiches);
                }
                break;
            case 5:
            printAfiches(pArrayAfic, limiteAfi);
            if(utn_getEntero(&idVenta, 10, "Ingrese id de venta\n","No es un id valido \n", 3) == 0 &&
                afi_modificarAfiches(pArrayAfic, limiteAfi, idVenta)== 0)
                {
                    printf("Venta modificada");
                }
                break;
            case 6:
            __fpurge(stdin);
            printAfiches(pArrayAfic, limiteAfi);
            if(cli_PorIDprintclie( pArray, limite, pArrayAfic, limiteAfi, &idVentaprint)==0)
            {
                printf("Desea cambiar el estado de la venta Y/N\n");
                scanf("%c", &resp2);
                if (resp2 == 'Y')
                {
                    strncpy(pArrayAfic[idVentaprint].estado,"cobrada" ,51);
                    printf("Estado :%s\n", pArrayAfic[idVentaprint].estado);
                }
            }else
            {
                printf("no existe id\n");
            }
            break;
            case 7:
             printClientesAfiches(pArray, limite, pArrayAfic, limiteAfi);
            break;
            case 8:
            informar_clienteConMasVentas(pArrayAfic,limiteAfi,pArray,limite);
            break;
            case 16:
            printf("salio");
            retorno = 0;
            break;
      }

    }while(resp != 16);
 return retorno;
}
