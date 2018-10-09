#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utn.h"
#include "clientes.h"
#include "afiches.h"
/*int informes_ordenarByNombre(empleadoDes* pBuffer,int limite,int upOrDonw)
{
  int i, j;
  int auxId;
  char auxNombre[50];
  char auxLastName[50];
  int auxSector;
  float auxSalario;
  if (pBuffer != NULL && limite > 0 && (upOrDonw == 0 || upOrDonw == 1))
    {
        for(i = 0; i < limite; i++)
        {
          j = i + 1;
                fflush(stdin);
                if(pBuffer[i].isEmpty == 1&& pBuffer[j].isEmpty == 1 && upOrDonw == 1 && strcmp(pBuffer[i].lastName,pBuffer[j].lastName) >0
                   || (strcmp(pBuffer[i].lastName,pBuffer[j].lastName) ==0 && pBuffer[i].sector > pBuffer[j].sector))
                {
                    auxId = pBuffer[j].id;
                    pBuffer[j].id = pBuffer[i].id;
                    pBuffer[i].id = auxId;

                    strncpy(auxLastName, pBuffer[j].lastName, 50);
                    strncpy(pBuffer[j].lastName,pBuffer[i].lastName, 50);
                    strncpy(pBuffer[i].lastName,auxLastName, 50);

                    strncpy(auxNombre, pBuffer[j].name, 50);
                    strncpy(pBuffer[j].name,pBuffer[i].name, 50);
                    strncpy(pBuffer[i].name,auxNombre, 50);

                    auxSalario = pBuffer[j].salary;
                    pBuffer[j].salary = pBuffer[i].salary;
                    pBuffer[i].salary = auxSalario;

                    auxSector = pBuffer[j].sector;
                    pBuffer[j].sector = pBuffer[i].sector;
                    pBuffer[i].sector = auxSector;
                }else if(pBuffer[i].isEmpty == 1&& pBuffer[j].isEmpty == 1 && upOrDonw == 0 && strcmp(pBuffer[i].lastName,pBuffer[j].lastName) <0
                         || strcmp(pBuffer[i].lastName,pBuffer[j].lastName) ==0 && pBuffer[i].sector < pBuffer[j].sector)
                {
                    auxId = pBuffer[j].id;
                    pBuffer[j].id = pBuffer[i].id;
                    pBuffer[i].id = auxId;

                    strncpy(auxLastName, pBuffer[j].lastName, 50);
                    strncpy(pBuffer[i+1].lastName,pBuffer[i].lastName, 50);
                    strncpy(pBuffer[i].lastName,auxLastName, 50);

                    strncpy(auxNombre, pBuffer[j].name, 50);
                    strncpy(pBuffer[i+1].name,pBuffer[i].name, 50);
                    strncpy(pBuffer[i].name,auxNombre, 50);

                    auxSalario = pBuffer[j].salary;
                    pBuffer[j].salary = pBuffer[i].salary;
                    pBuffer[i].salary = auxSalario;

                    auxSector = pBuffer[j].sector;
                    pBuffer[j].sector = pBuffer[i].sector;
                    pBuffer[i].sector = auxSector;
                }
        }
    }
    return 1;
}
*/
int informar_clienteConMasVentas(void* arrayAfi, int limiteAfi,void* pArray, int limite)
{
    afiches * pArrayAfi = arrayAfi;
    clientes * arrayClientes = pArray;
    int arrayCantidadVentasPorCliente[limite];
    int retorno=-1;
    int i;
    int j;
    int mayorCantidadVentas = 0;
    int contadorDeVentasCliente;
    if(pArrayAfi != NULL && limiteAfi > 0 && arrayClientes != NULL && limite > 0)
    {
        for(i=0; i < limite; i++)
        {
            if(arrayClientes[i].isEmpty == 1)
            {
                contadorDeVentasCliente = 0;
                for(j=0;j<limiteAfi; j++)
                {
                    if(afi_getByIdCliente(&pArrayAfi[j], 1, arrayClientes[i].idClientes) != NULL && strcmp(pArrayAfi[i].estado, "a cobrar") == 0)
                    {
                        contadorDeVentasCliente++;
                    }
                }
                arrayCantidadVentasPorCliente[i] = contadorDeVentasCliente;
            }
            if(arrayClientes[i].isEmpty== 1 && arrayCantidadVentasPorCliente[i] > mayorCantidadVentas)
            {
                mayorCantidadVentas = arrayCantidadVentasPorCliente[i];
            }
        }
        for(i=0; i < limite; i++)
        {
            if(arrayClientes[i].isEmpty == 1 && mayorCantidadVentas == arrayCantidadVentasPorCliente[i])
            {
                cliente_mostrar(&arrayClientes[i], 1);
            }
        }
        retorno = 0;
    }
    return retorno;
}
int informar_clienteVentasCobradas(afiches* arrayAfi, int limiteAfi,clientes* pArray, int limite)
{
    int retorno = -1;
    int contadorDeVentasCliente = 0;
    int mayorCantidadVentasCliente = 0;
    int arrayCantidadVentasPorCliente[limite];
    int i,j;
    if (arrayAfi != NULL && limiteAfi > 0 && pArray != NULL && limite >0)
    {
       for(i=0; i < limite; i++)
        {
            if(pArray[i].isEmpty == 1)
            {
                contadorDeVentasCliente = 0;
                for(j=0;j<limiteAfi; j++)
                {
                    if(arrayAfi[j].idCliente == pArray[i].idClientes && strcmp(arrayAfi[j].estado,"cobrada") == 0)
                    {
                        contadorDeVentasCliente++;
                    }
                }
                arrayCantidadVentasPorCliente[i] = contadorDeVentasCliente;
            }
            if(pArray[i].isEmpty== 1 && arrayCantidadVentasPorCliente[i] > mayorCantidadVentasCliente)
            {
                mayorCantidadVentasCliente = arrayCantidadVentasPorCliente[i];
            }
            for(i=0; i < limite; i++)
            {
                 if(pArray[i].isEmpty == 1 && mayorCantidadVentasCliente == arrayCantidadVentasPorCliente[i])
                 {
                    cliente_mostrar(&pArray[i], 1);
                    retorno = 0;
                 }

            }
        }
    }
    return retorno;
}


