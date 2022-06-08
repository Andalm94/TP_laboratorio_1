#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Passenger.h"
#include "parser.h"

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromText(FILE* pFile , LinkedList* pArrayListPassenger){

	//Descripcion:
	//**1-Declaro las variables necesarias para cargar a los pasajeros escaneados del documento
	//**2-Valido la validez de los parametros.
	//**3-Recorro el archivo. Escaneo linea por linea, cargando los datos separados por coma en las variables declaradas al principio.
	//**4-Creo el nuevo pasajero con los datos escaneados. Cargo el nuevo pasajero en la linkedList. Retorno 0 en caso de exito.
	int retorno = -1;
	Passenger* auxPasajero;
	char id[32];
	char nombre[32];
	char apellido[32];
	char codigoDeVuelo[32];
	char tipoDePasajero[32];
	char tipoDePasajero_codigoInterno[4];
	char estadoDeVuelo[32];
	char precio[32];

	if(pFile != NULL && pArrayListPassenger!= NULL){
		fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",id, nombre, apellido, precio, codigoDeVuelo, tipoDePasajero, estadoDeVuelo);//falsa lectura
		while(!feof(pFile)){
			fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",id, nombre, apellido, precio, codigoDeVuelo, tipoDePasajero, estadoDeVuelo); //Escaneo el documento
			parser_codificarTipoDePasajero(tipoDePasajero_codigoInterno, tipoDePasajero); //Codifico el tipo de pasajero
			auxPasajero = Passenger_newParametros(id, nombre, apellido, codigoDeVuelo, tipoDePasajero_codigoInterno, precio, estadoDeVuelo); //cargo los datos escaneados en un nuevo pasajero
			ll_add(pArrayListPassenger, auxPasajero); //cargo el nuevo pasajero en la linkedList
			retorno = 0;
		}
	}



    return retorno;
}

/** \brief Parsea los datos los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int parser_PassengerFromBinary(FILE* pFile , LinkedList* pArrayListPassenger){

	int retorno = -1;
    Passenger* auxPasajero = NULL;

    if(pFile != NULL && pArrayListPassenger != NULL){
		while(!feof(pFile)){
			auxPasajero = Passenger_new();
			fread(auxPasajero, sizeof(Passenger), 1, pFile);
			ll_add(pArrayListPassenger, auxPasajero);
			retorno = 0;
		}
    }

	return retorno;
}

int parser_codificarTipoDePasajero(char tipoDePasajeroint[], char tipoDePasajeroStr[]){
	int retorno = -1;
	char tipoDePasajeroConvertido[4];
	strcpy(tipoDePasajeroConvertido, "0");

	if(tipoDePasajeroint != NULL && tipoDePasajeroStr != NULL){
		retorno = 0;


		if(strcmp(tipoDePasajeroStr, "EconomyClass") == 0){
			strcpy(tipoDePasajeroConvertido, "1");
		}
		else{
			if(strcmp(tipoDePasajeroStr, "ExecutiveClass") == 0){
				strcpy(tipoDePasajeroConvertido, "2");
			}
			else{
				if(strcmp(tipoDePasajeroStr, "FirstClass") == 0){
					strcpy(tipoDePasajeroConvertido, "3");
				}
			}
		}
		strcpy(tipoDePasajeroint, tipoDePasajeroConvertido);
	}

	return retorno;

}

