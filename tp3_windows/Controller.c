#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Passenger.h"
#include "Controller.h"
#include "parser.h"
#include "UTN.h"

//---------------------------------- LOAD --------------------------------------------------

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListPassenger){
	int retorno = -1;
	FILE* file;

	if(pArrayListPassenger != NULL){
		file = fopen(path, "r");
		if(file != NULL && parser_PassengerFromText(file, pArrayListPassenger) == 0){
			retorno = 0;
		}
		fclose(file);
	}
    return retorno;
}

/** \brief Carga los datos de los pasajeros desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListPassenger){
    int retorno = -1;
    int len;
	FILE* file;

	if(pArrayListPassenger != NULL){
		file = fopen(path, "rb");
		if(file != NULL && parser_PassengerFromBinary(file, pArrayListPassenger)==0 ){
			retorno = 0;
		}
	}

	fclose(file);
	len=ll_len(pArrayListPassenger);
	ll_remove(pArrayListPassenger, len-1);

	return retorno;
}




//---------------------------------- ALTA - MODIFICACION - BAJA-----------------------------------------------


/** \brief Alta de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_addPassenger(LinkedList* pArrayListPassenger){
	int retorno = -1;
	Passenger* auxPasajero;
	int nextID;
	char id[32];
	char nombre[32];
	char apellido[32];
	char codigoDeVuelo[32];
	char tipoDePasajero[32];
	char precio[32];
	char estadoDeVuelo[32];


	if(pArrayListPassenger != NULL){
		if(getString ("Nombre: \n", "ERROR. Intente nuevamente.", nombre, 32, 3) == 0 &&
				getString ("Apellido: \n", "ERROR. Intente nuevamente.", apellido, 32, 3) == 0 &&
				getString ("Codigo de vuelo: \n", "ERROR. Intente nuevamente.", codigoDeVuelo, 32, 3) == 0 &&
				getString ("Tipo de pasajero: (1. EconomicClass || 2.ExecutiveClass || 3.FirstClass) \n", "ERROR. Intente nuevamente.", tipoDePasajero, 32, 3) == 0 &&
				getString ("Precio: \n", "ERROR. Intente nuevamente.", precio, 32, 3) == 0 &&
				getString ("Estado del vuelo: \n", "ERROR. Intente nuevamente.", estadoDeVuelo, 32, 3) == 0){

			nextID = controller_generadorID(pArrayListPassenger);
			sprintf(id,"%i", nextID);
			auxPasajero = Passenger_newParametros(id, nombre, apellido, codigoDeVuelo, tipoDePasajero, precio, estadoDeVuelo);
			ll_add(pArrayListPassenger, auxPasajero);
			retorno = 0;
		}

	}

    return retorno;
}

/** \brief Modificar datos de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_editPassenger(LinkedList* pArrayListPassenger){
	int retorno = -1;
	int idPasajero;
	int indexPasajero = -1;
	int opcionIngresada;
	char nuevoDato[32];
	Passenger* auxPasajero = NULL;

	 if(controller_ListPassenger(pArrayListPassenger)==0 &&
			 getInt(&idPasajero, "Pasajero ID: \n", "ERROR. Intente nuevamente\n", 1, 9999, 3) == 0){

		 retorno = 0;
		 indexPasajero = controller_BuscarPasajeroPorID(pArrayListPassenger, idPasajero);
		 if(indexPasajero != -1){
				auxPasajero=(Passenger*)ll_get(pArrayListPassenger, indexPasajero);
				mostrarPasajero(auxPasajero);

				do{
					mostrarMenuModificaciones();
					if(getInt(&opcionIngresada, "\n", "No existe esa opcion\n", 1, 6, 3) == 0){

						switch(opcionIngresada){
							case 1: //---------------------------------------------------------> NOMBRE
								getString ("Nuevo nombre:\n", "ERROR\n", nuevoDato, 32, 3);
								Passenger_setNombre(auxPasajero, nuevoDato);
								mostrarPasajero(auxPasajero);
								break;
							case 2: //---------------------------------------------------------> APELLIDO
								getString ("Nuevo apellido:\n", "ERROR\n", nuevoDato, 32, 3);
								Passenger_setApellido(auxPasajero, nuevoDato);
								mostrarPasajero(auxPasajero);
								break;
							case 3: //---------------------------------------------------------> CODIGO DE VUELO
								getString ("Nuevo codigo de vuelo:\n", "ERROR\n", nuevoDato, 32, 3);
								Passenger_setCodigoVuelo(auxPasajero, nuevoDato);
								mostrarPasajero(auxPasajero);
								break;
							case 4: //---------------------------------------------------------> TIPO DE PASAJERO
								getString ("Nuevo tipo de pasajero:\n", "ERROR\n", nuevoDato, 32, 3);
								Passenger_setTipoPasajero(auxPasajero, atoi(nuevoDato));
								mostrarPasajero(auxPasajero);
								break;
							case 5: //---------------------------------------------------------> PRECIO
								getString ("Nuevo precio:\n", "ERROR\n", nuevoDato, 32, 3);
								Passenger_setPrecio(auxPasajero, atof(nuevoDato));
								mostrarPasajero(auxPasajero);
								break;
							case 6: //---------------------------------------------------------> VOLVER AL MENU PRINCIPAL
								break;
						}

					}
				}while(opcionIngresada != 6);

		 }
	 }

	return retorno;
}

/** \brief Baja de pasajero
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_removePassenger(LinkedList* pArrayListPassenger){
	int retorno = -1;
	int indexPasajero;
	int idPasajero;
	Passenger* auxPasajero;
	char respuestaConfirmacion;

	//Valido los parametros ingresados
	if(pArrayListPassenger != NULL){

		//Listo los pasajeros
		//Solicito el ID del pasajero a eliminar
		if(controller_ListPassenger(pArrayListPassenger) == 0 &&
				getInt(&idPasajero, "Pasajero ID:\n", "ERROR. Intente nuevamente\n", 0, 9999, 3) == 0){


			//Si existe el pasajero, se almacena en la variable 'auxPasajero' y se muestra.
			indexPasajero = controller_BuscarPasajeroPorID(pArrayListPassenger, idPasajero);
			if(indexPasajero != -1){
				auxPasajero=(Passenger*)ll_get(pArrayListPassenger, indexPasajero);
				mostrarPasajero(auxPasajero);

				//Se solicita confirmacion para eliminar. En casi de que el usuario confirme, el usuario se elimina.
				if (getCharSiNo ("Desea eliminar este pasajero\n", &respuestaConfirmacion, 3) == 0 && respuestaConfirmacion == 'S'){
		    		ll_remove(pArrayListPassenger, indexPasajero);
		    		Passenger_delete(auxPasajero);
		    		retorno=0;
				}

			}

		}


	}


    return retorno;
}



//------------------------------LISTAR / BUSCAR / ORDENAR----------------------------------------
/** \brief Listar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_ListPassenger(LinkedList* pArrayListPassenger){
	int retorno = -1;
	int len;
	Passenger* auxPasajero;

	if(pArrayListPassenger != NULL){
		len = ll_len(pArrayListPassenger);
		printf("\n---------------------------------------------------------------------------------------------------\n");
		printf("ID        NOMBRE         APELLIDO       PRECIO       CODIGO DE VUELO     TIPO             ESTADO\n");
		printf("---------------------------------------------------------------------------------------------------\n");
		for(int i=0; i<len; i++){
			auxPasajero = (Passenger*) ll_get(pArrayListPassenger, i);
			mostrarPasajero(auxPasajero);
		}
		retorno = 0;
	}
    return retorno;
}


int controller_BuscarPasajeroPorID(LinkedList* pArrayListPassenger, int id){
	int retorno = -1;
	int len;
	Passenger* auxPasajero = NULL;

	len=ll_len(pArrayListPassenger);

	if(pArrayListPassenger != NULL){
		for (int i=0; i<len; i++){
			auxPasajero = (Passenger*)ll_get(pArrayListPassenger, i);
			if(auxPasajero->id == id){
				retorno = ll_indexOf(pArrayListPassenger, auxPasajero);
				break;
			}
		}
	}

	return retorno;
}

/** \brief Ordenar pasajeros
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_sortPassenger(LinkedList* pArrayListPassenger){
	int retorno = -1;
	int opcionIngresada;
	int opcionIngresadaOrdenamiento;

	 if(pArrayListPassenger != NULL){

		 retorno = 0;
		 mostrarMenuOrdenamientos();
		 if(getInt(&opcionIngresada, "\n", "No existe esa opcion\n", 1, 7, 3) == 0){
			 switch(opcionIngresada){
			 	case 1: //---------------------------------------------------------> ID
			 		if(getInt(&opcionIngresadaOrdenamiento, "Ordenar de manera:\n 0) Descendente\n 1) Ascendente\n", "ERROR. Intente nuevamente", 0, 1, 3) == 0){
			 			ll_sort(pArrayListPassenger, compararPasajerosPorID, opcionIngresadaOrdenamiento);
			 		}
			 		break;
			 	case 2: //---------------------------------------------------------> NOMBRE
			 		if(getInt(&opcionIngresadaOrdenamiento, "Ordenar de manera:\n 0) Descendente\n 1) Ascendente\n", "ERROR. Intente nuevamente", 0, 1, 3) == 0){
			 			ll_sort(pArrayListPassenger, compararPasajerosPorNombre, opcionIngresadaOrdenamiento);
			 		}
			 		break;
			 	case 3: //---------------------------------------------------------> APELLIDO
			 		if(getInt(&opcionIngresadaOrdenamiento, "Ordenar de manera:\n 0) Descendente\n 1) Ascendente\n", "ERROR. Intente nuevamente", 0, 1, 3) == 0){
			 			ll_sort(pArrayListPassenger, compararPasajerosPorApellido, opcionIngresadaOrdenamiento);
			 		}
			 		break;
			 	case 4: //---------------------------------------------------------> CODIGO DE VUELO
			 		if(getInt(&opcionIngresadaOrdenamiento, "Ordenar de manera:\n 0) Descendente\n 1) Ascendente\n", "ERROR. Intente nuevamente", 0, 1, 3) == 0){
			 			ll_sort(pArrayListPassenger, compararPasajerosPorCodigoVuelo, opcionIngresadaOrdenamiento);
			 		}
			 		break;
			 	case 5: //---------------------------------------------------------> TIPO DE PASAJERO
			 		if(getInt(&opcionIngresadaOrdenamiento, "Ordenar de manera:\n 0) Descendente\n 1) Ascendente\n", "ERROR. Intente nuevamente", 0, 1, 3) == 0){
			 			ll_sort(pArrayListPassenger, compararPasajerosPorTipoPasajero, opcionIngresadaOrdenamiento);
			 		}
			 		break;
			 	case 6: //---------------------------------------------------------> PRECIO
			 		if(getInt(&opcionIngresadaOrdenamiento, "Ordenar de manera:\n 0) Descendente\n 1) Ascendente\n", "ERROR. Intente nuevamente", 0, 1, 3) == 0){
			 			ll_sort(pArrayListPassenger, compararPasajerosPorPrecio, opcionIngresadaOrdenamiento);
			 		}
			 		break;
			 	case 7: //---------------------------------------------------------> VOLVER AL MENU ANTERIOR
			 		break;
			 }
		 }
	 }

	//Si el usuario realizo algun ordenamiento, muestra la lista reordenada.
	if(opcionIngresada >= 1 && opcionIngresada <= 6){
		controller_ListPassenger(pArrayListPassenger);
	}

	return retorno;
}

/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */

//------------------------------- MANEJO ID ------------------------------------------------

int controller_generadorID(LinkedList* pArrayListPassenger){
	int id = -1;

	if(pArrayListPassenger){
		id = controller_buscarUltimoID(pArrayListPassenger);
		id++;
	}

	return id;
}

int controller_buscarUltimoID(LinkedList* pArrayListPassenger){
	int id = 0;
	int len;
	Passenger* auxPasajero;

	len = ll_len(pArrayListPassenger);
	if(pArrayListPassenger != NULL){
		for(int i=0; i<len; i++){
			auxPasajero = (Passenger*)ll_get(pArrayListPassenger, i);
			if(auxPasajero->id > id){
				id = auxPasajero->id;
			}
		}
	}
	return id;
}


//---------------------------------- SAVE --------------------------------------------------

int controller_saveAsText(char* path , LinkedList* pArrayListPassenger){
	int retorno = -1;
    int len;
    int id;
    char nombre[32];
    char apellido[32];
    char codigoDeVuelo[32];
    int tipoDePasajero_codigoInterno;
    char tipoDePasajeroStr[32];
    char estadoDeVuelo[32];
    float precio;

    FILE* file;
    Passenger* auxPasajero;



    /*
	//===================================================================
	tipoDePasajero_codigoInterno = Passenger_getTipoPasajero(pPasajero);

	if(tipoDePasajero_codigoInterno == 1){
		strcpy(tipoDePasajeroStr, "EconomyClass");
	}
	else{
		if(tipoDePasajero_codigoInterno == 2){
			strcpy(tipoDePasajeroStr, "ExecutiveClass");
		}
		else{
			strcpy(tipoDePasajeroStr, "FirstClass");
		}
	}
	//===================================================================

    */
    len = ll_len(pArrayListPassenger);
    file = fopen(path, "w");

    if(path != NULL){
    	fprintf(file,"id,name,lastname,price,flycode,typePassenger,statusFlight\n"); //Imprimo el header
    	for(int i=0; i<len; i++){
    		auxPasajero = (Passenger*)ll_get(pArrayListPassenger, i);

    		tipoDePasajero_codigoInterno = Passenger_getTipoPasajero(auxPasajero);
    		decodificarTipoDePasajero(tipoDePasajeroStr, tipoDePasajero_codigoInterno);


    		id = Passenger_getId(auxPasajero);
    		strcpy(nombre, Passenger_getNombre(auxPasajero));
    		strcpy(apellido, Passenger_getApellido(auxPasajero));
    		strcpy(codigoDeVuelo, Passenger_getCodigoVuelo(auxPasajero));
    		precio = Passenger_getPrecio(auxPasajero);
    		strcpy(codigoDeVuelo, Passenger_getCodigoVuelo(auxPasajero));
    		strcpy(estadoDeVuelo, Passenger_getEstadoDeVuelo(auxPasajero));
    		fprintf(file,"%d,%s,%s,%.0f,%s,%s,%s\n",id,nombre,apellido,precio,codigoDeVuelo,tipoDePasajeroStr,estadoDeVuelo);
    		retorno = 0;
    	}
    }

    fclose(file);
	return retorno;
}



/** \brief Guarda los datos de los pasajeros en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListPassenger LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListPassenger){
	int retorno = -1;
	int len;
	FILE* file;
	Passenger* auxPasajero = NULL;

	if(pArrayListPassenger != NULL && path != NULL){
		retorno = 0;
		file = fopen(path, "wb");
		len = ll_len(pArrayListPassenger);

		for(int i=0; i<len; i++){
			auxPasajero = (Passenger*) ll_get(pArrayListPassenger, i);
			fwrite(auxPasajero, sizeof(Passenger), 1, file);
		}

	}

	fclose(file);
    return retorno;
}

