#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getString(char* pBuffer,int limite){
    char bufferString[4096];
    int retorno =-1;
    if (pBuffer != NULL && limite >0){
//        __fpurge(stdin);
        fgets(bufferString,sizeof(bufferString),stdin);
        if (bufferString[strlen(bufferString)-1]=='\n'){
            bufferString[strlen(bufferString)-1]='\0';
        }
        if(strlen(bufferString)<= limite){
            strncpy(pBuffer,bufferString,limite);
            retorno=0;
        }
    }
    return retorno;
}
int isValidSoloNumeros(char *pBuffer, int limite)
{
    int retorno = 0;
    int i;
    if( pBuffer != NULL && limite > 0 && strlen(pBuffer) == 13 &&
            pBuffer[2] == '-' && pBuffer[11] == '-')
    {
        retorno = 1;
        for(i=0; i < limite && pBuffer[i] != '\0'; i++)
        {
            if((pBuffer[i] < '0' || pBuffer[i] > '9') && i!=2 && i!=11)
            {
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}
int utn_getNumeros(   char *pEntero, int limite, char *mensaje, char *mensajeError, int reintentos)
{
    int retorno=-1;
    char buffer[4096];
    if( pEntero != NULL && limite > 0 && mensaje != NULL &&
            mensajeError != NULL && reintentos>=0)
    {
        do
        {
            reintentos--;
            printf("\n%s", mensaje);
            if( getString(buffer, limite) == 0 &&
                isValidSoloNumeros(buffer, limite))
            {
                strncpy(pEntero, buffer, limite);
                retorno = 0;
                break;
            }
            else
            {
                printf("\n%s", mensajeError);
            }
        }
        while(reintentos>=0);
    }
    return retorno;
}
int utn_getLetrasYNumeros(char* pBuffer,int limite,char* msj){
    int retorno=-1;
    char aux[limite];
    printf("%s",msj);
    if (pBuffer!=NULL&&limite>0&&getString(aux,limite)==0)
        {
            retorno=0;
            strncpy(pBuffer,aux,limite);
        }
    return retorno;
}
/**
* \brief    Toma la cadena y evalua si es un nombre
* \param pNombre Recibe el texto ingresado en caso de exito
* \param limite Es el tamano maximo del string
* \param msg Es el mensaje que se muestra al usuario antes de introducir datos
* \param msgErr Es el mensaje que se muestra en caso de error
* \param reintentos Veces que el usuario podra volver a introducir el dato
* \return En caso de exito retorna 0, si no -1
*/
int utn_getNombre(  char* pNombre,int limite, char* msg, char* msgErr, int reintentos)
{
    int retorno=-1;
    char bufferNombre[4096];
    if(pNombre != NULL && limite > 0 && msg != NULL && msgErr != NULL && reintentos >= 0 )
    {
      do
      {
         reintentos--;
         printf("%s", msg);
         if (utn_getString(bufferNombre, limite) == 0 && utn_isValidNombre(bufferNombre, limite))
         {
            strncpy(pNombre, bufferNombre, limite);
            retorno = 0;
            break;
         }else
         {
            printf("%s", msgErr);
         }


      }while(reintentos>=0);
    }
    return retorno;
}
/**
* \brief El usuario ingresa una cadena con fgets
* \param pBuffer Recibe el texto ingresado en caso de exito
* \param limite Es el tamano maximo del string
* \return En caso de exito retorna 0, si no -1
*/
int utn_getString(char* pBuffer, int limite)
{
    int retorno = -1;
    char bufferStr[4096];
    int len;
    if(pBuffer != NULL && limite > 0)
    {
        //__fpurge(stdin);
        fflush(stdin);
        fgets(bufferStr,limite,stdin);
        len = strlen(bufferStr);
        if(len != limite-1 ||  bufferStr[limite-2] == '\n')
        {
            bufferStr[len-1] = '\0';
        }
        retorno = 0;
        strncpy(pBuffer,bufferStr,limite);
    }
    return retorno;
}
int utn_isValidNombre(char* pBuffer,int limite)
{
    int retorno = 0;
    int i;
    if(pBuffer != NULL && limite > 0)
    {
        retorno = 1;
        for(i=0;i < limite && pBuffer[i] != '\0';i++)
        {
            if(tolower(pBuffer[i]) < 'a' || tolower(pBuffer[i]) > 'z')
            {
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}
/**
* \brief Evalua si se trata de un entero
* \param pBuffer Es la cadena que evaluamos
* \param limite Es el numero maximo de cifras
* \return En caso de exito retorna 1, si no 0
*
*/
int isValidEntero(char *pBuffer, int limite)
{
    int retorno = 0;
    int i;
    if  ((pBuffer != NULL && limite > 0 ) &&
        (pBuffer[0] == '-' || pBuffer[0] == '+' ||
        (pBuffer[0]>='0' && pBuffer[0]<='9')))
    {
        retorno = 1;
        for(i=1;i < limite && pBuffer[i] != '\0';i++)
        {
            if (!(pBuffer[i]>='0' && pBuffer[i]<='9'))
            {
                retorno = 0;
                break;
            }
        }
    }
    return retorno;
}
/**
* \brief    Toma la cadena y evalua si es un entero en caso de exito lo transforma a entero
* \param pEntero Recibe el numero ingresado en caso de exito
* \param limite Es el tamano maximo de cifras
* \param mensaje Es el mensaje que se muestra al usuario antes de introducir datos
* \param mensajeError Es el mensaje que se muestra en caso de error
* \param reintentos Veces que el usuario podra volver a introducir el dato
* \return En caso de exito retorna 0, si no -1
*/
int utn_getEntero(  int *pEntero, int limite, char *mensaje,char *mensajeError, int reintentos)
{
    int retorno=-1;
    char bufferEntero[4096];
    if( pEntero != NULL && limite > 0 && mensaje != NULL &&
        mensajeError != NULL && reintentos>=0)
    {
        do
        {
            reintentos--;
            printf("\n%s", mensaje);
            if( utn_getString(bufferEntero, limite) == 0 &&
                isValidEntero(bufferEntero, limite))
            {
                *pEntero = atoi(bufferEntero);
                retorno = 0;
                break;
            }
            else
            {
                printf("\n%s", mensajeError);
            }
        }while(reintentos>=0);
    }
    return retorno;
}

