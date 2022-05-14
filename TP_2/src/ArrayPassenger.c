#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "IngresoDeDatos.h"
#include "ArrayPassenger.h"

#define EMPTY 0
#define FULL 1

#define ACTIVO 1
#define CANCELADO 2
#define DEMORADO 3


int initPassengers(Passenger* list, int len){
	int retorno = -1;
	int i;

	if(list != NULL && len > 0){
		for (i=0; i<len; i++){
			list[i].isEmpty = EMPTY;
		}
		retorno = 0;
	}

	return retorno;
}


int addPassenger(Passenger* list, int len, int id, char name[], char lastName[], float price, int typePassenger, char flycode[]){
	int retorno = -1;

	int indexLibre = -1;


	if(buscarIndexLibre(list, len, &indexLibre) == 0){
		list[indexLibre].id = id;
		strcpy(list[indexLibre].name, name);
		strcpy(list[indexLibre].lastName, lastName);
		list[indexLibre].price = price;
		list[indexLibre].typePassenger = typePassenger;
		strcpy(list[indexLibre].flycode, flycode);
		list[indexLibre].statusFlight = ACTIVO;
		list[indexLibre].isEmpty = FULL;
		retorno = 0;
	}



	return retorno;
}


int findPassengerById(Passenger* list, int len, int id){
	int retorno = -1;

	if (list != NULL && len > 0 && id > -1) {

		for (int i = 0; i < len; i++) {
			if (list[i].id == id && list[i].isEmpty == FULL) {
				retorno = i;
				break;
			}
		}

	}

	return retorno;
}


int removePassenger(Passenger* list, int len, int id, char mensaje[]){
	int retorno = -1;
	int index;
	char respuesta;

	if(list != NULL && len>0){

		index = findPassengerById(list, len, id);
		if(index != -1 && printOnlyOnePassenger(list[index]) != -1 && getCharSiNo(mensaje, &respuesta, 1) == 0 && (respuesta == 'S' || respuesta =='s')){
			list[index].isEmpty = EMPTY;
			retorno = 0;
		}
	}

	return retorno;
}

int hayPasajeros(Passenger* list, int len, char * mensajeError){
	int retorno = -1;
	int i;

	for(i = 0;i <len; i++){
		if(list[i].isEmpty == FULL){
			retorno = 0;
			break;
		}
	}

	if(retorno == -1){
		printf(mensajeError);
	}

	return retorno;
}

int buscarIndexLibre(Passenger* list, int len, int * index){
	int retorno = -1;
	int indexLibre;
	int i;

	for (i=0; i<len; i++){
		if(list[i].isEmpty == 0){
			indexLibre = i;
			*index = indexLibre;
			retorno = 0;
			break;
		}
	}

	return retorno;
}

//---------------ORDENAMIENTO---------------

int sortPassengers(Passenger* list, int len, int order){
	int retorno = -1;
	int estaOrdenado;
	int i;
	Passenger aux;

	if(list != NULL && len>0 && (order == 0 || order ==1)){

		if(order == 1){
			do{
				estaOrdenado = 1;
				len--;
				for(i=0; i<len; i++){
					if(stricmp(list[i].lastName, list[i+1].lastName) > 0){
						aux = list[i];
						list[i] = list[i+1];
						list[i+1] = aux;
						estaOrdenado = 0;
					}
				}
			}while(estaOrdenado == 0);
		}
		if(order == 0){
			do{
				estaOrdenado = 1;
				len--;
				for(i=0; i<len; i++){
					if(stricmp(list[i].lastName, list[i+1].lastName) < 0){
						aux = list[i];
						list[i] = list[i+1];
						list[i+1] = aux;
						estaOrdenado = 0;
					}
				}
			}while(estaOrdenado == 0);
		}

		retorno = 0;
	}


	return retorno;
}

int sortPassengersByType(Passenger* list, int len, int order){
	int retorno = -1;
	int estaOrdenado;
	int i;
	Passenger aux;

	if(list != NULL && len>0 && (order == 0 || order ==1)){

		if(order == 1){
			do{
				estaOrdenado = 1;
				len--;
				for(i=0; i<len; i++){
					if( (stricmp(list[i].lastName, list[i+1].lastName) == 0) && (list[i].typePassenger > list[i+1].typePassenger) ){
						aux = list[i];
						list[i] = list[i+1];
						list[i+1] = aux;
						estaOrdenado = 0;
					}
				}
			}while(estaOrdenado == 0);
		}
		if(order == 0){
			do{
				estaOrdenado = 1;
				len--;
				for(i=0; i<len; i++){
					if( (stricmp(list[i].lastName, list[i+1].lastName) == 0) && (list[i].typePassenger < list[i+1].typePassenger) ){
						aux = list[i];
						list[i] = list[i+1];
						list[i+1] = aux;
						estaOrdenado = 0;
					}
				}
			}while(estaOrdenado == 0);
		}

		retorno = 0;
	}


	return retorno;
}

int sortPassengersByCode(Passenger* list, int len, int order){
	int retorno = -1;
		int estaOrdenado;
		int i;
		Passenger aux;

		if(list != NULL && len>0 && (order == 0 || order ==1)){

			if(order == 1){
				do{
					estaOrdenado = 1;
					len--;
					for(i=0; i<len; i++){
						if(stricmp(list[i].flycode, list[i+1].flycode) > 0 ){
							aux = list[i];
							list[i] = list[i+1];
							list[i+1] = aux;
							estaOrdenado = 0;
						}
					}
				}while(estaOrdenado == 0);
			}
			if(order == 0){
				do{
					estaOrdenado = 1;
					len--;
					for(i=0; i<len; i++){
						if(stricmp(list[i].flycode, list[i+1].flycode) < 0){
							aux = list[i];
							list[i] = list[i+1];
							list[i+1] = aux;
							estaOrdenado = 0;
						}
					}
				}while(estaOrdenado == 0);
			}

			retorno = 0;
		}


		return retorno;
}

//-------------------PRINT-------------------

int printPassenger(Passenger* list, int length){
	int i;
	int retorno = -1;
	if(list != NULL && length > 0){
		printf("ID\t||\tNOMBRE\t||\tAPELLIDO\t||\tPRECIO\t||\tCODIGO\t||\tTIPO\t||\tESTADO\n");
		for(i=0; i<length; i++){
			if(list[i].isEmpty == 1){
				printf("%d", list[i].id);
				printf("%20s", list[i].name);
				printf("%20s", list[i].lastName);
				printf("%20.2f", list[i].price);
				printf("%20s", list[i].flycode);
				printf("%10d", list[i].typePassenger);
				printf("%10d", list[i].statusFlight);
				printf("\n");
			}
		}
		printf("\n\n");

		retorno = 0;
	}



	return retorno;
}

int printActivePassenger(Passenger* list, int length){
	int i;
	int retorno = -1;
	if(list != NULL && length > 0){
		printf("ID\t||\tNOMBRE\t||\tAPELLIDO\t||\tPRECIO\t||\tCODIGO\t||\tTIPO\t||\tESTADO\n");
		for(i=0; i<length; i++){
			if(list[i].isEmpty == 1 && list[i].statusFlight == ACTIVO){
				printf("%d", list[i].id);
				printf("%20s", list[i].name);
				printf("%20s", list[i].lastName);
				printf("%20.2f", list[i].price);
				printf("%20s", list[i].flycode);
				printf("%10d", list[i].typePassenger);
				printf("%10d", list[i].statusFlight);
				printf("\n");
			}
		}
		printf("\n\n");

		retorno = 0;
	}



	return retorno;
}

int printOnlyOnePassenger(Passenger pasajero){
	int retorno = -1;


	if(pasajero.isEmpty == FULL){
		printf("ID\t||\tNOMBRE\t||\tAPELLIDO\t||\tPRECIO\t||\tCODIGO\t||\tTIPO\t||\tESTADO\n");
		printf("%d", pasajero.id);
		printf("%20s", pasajero.name);
		printf("%20s", pasajero.lastName);
		printf("%20.2f", pasajero.price);
		printf("%20s", pasajero.flycode);
		printf("%10d", pasajero.typePassenger);
		printf("%10d", pasajero.statusFlight);
		printf("\n");
		retorno = 0;
	}

	return retorno;
}



//---------------MODIFICACIONES---------------


int modificarNombre(Passenger* list, int len, int id, char * mensaje, char * mensajeError){
	int retorno = -1;
	char nuevoDatoIngresado[256];
	int index;

	index = findPassengerById(list, len, id);

	if(index != -1 && getString (mensaje, mensajeError, nuevoDatoIngresado, 256, 3) == 0){
		strcpy(list[index].name, nuevoDatoIngresado);
		retorno = 0;
	}

	return retorno;
}

int modificarApellido(Passenger* list, int len, int id, char * mensaje, char * mensajeError){
	int retorno = -1;
	char nuevoDatoIngresado[256];
	int index;

	index = findPassengerById(list, len, id);

	if(index != -1 && getString (mensaje, mensajeError, nuevoDatoIngresado, 256, 3) == 0){
		strcpy(list[index].lastName, nuevoDatoIngresado);
		retorno = 0;
	}

	return retorno;
}

int modificarPrecio(Passenger* list, int len, int id, char * mensaje, char * mensajeError){
	int retorno = -1;
	float nuevoDatoIngresado;
	int index;

	index = findPassengerById(list, len, id);

	if (index != -1 && getFloat(&nuevoDatoIngresado, mensaje, mensajeError, 10000, 1000000, 3) == 0){
		list[index].price = nuevoDatoIngresado;
		retorno = 0;
	}

	return retorno;
}

int modificarTipo(Passenger* list, int len, int id, char * mensaje, char * mensajeError){
	int retorno = -1;
	int nuevoDatoIngresado;
	int index;

	index = findPassengerById(list, len, id);

	if (index != -1 && getInt(&nuevoDatoIngresado, mensaje, mensajeError, 1, 3, 3) == 0){
		list[index].typePassenger = nuevoDatoIngresado;
		retorno = 0;
	}

	return retorno;
}

int modificarCodigo(Passenger* list, int len, int id, char * mensaje, char * mensajeError){
	int retorno = -1;
	char nuevoDatoIngresado[10];
	int index;

	index = findPassengerById(list, len, id);

	if(index != -1 && getString (mensaje, mensajeError, nuevoDatoIngresado, 256, 3) == 0){
		strcpy(list[index].flycode, nuevoDatoIngresado);
		retorno = 0;
	}

	return retorno;
}


//------------------INFORMES------------------

int mostrarTotalYPromedio(Passenger* list, int len){
	int retorno = -1;
	float precioTotalPasajes = 0;
	float promedioPasajes = 0;
	int contadorPasajeros = 0;
	int contadorPasajerosConPrecioAlto = 0;
	int i;

	if (list != NULL && len > 0){

		for(i=0; i<len; i++){
			if(list[i].isEmpty == FULL){
				precioTotalPasajes += list[i].price;
				contadorPasajeros ++;
			}
		}

		promedioPasajes = precioTotalPasajes / contadorPasajeros;

		for(i=0; i<len; i++){
			if(list[i].isEmpty == FULL && list[i].price > promedioPasajes){
				contadorPasajerosConPrecioAlto ++;
			}
		}

		printf("--INFORME--\n");
		printf("COSTO TOTAL DE PASAJES: $ %.2f\n", precioTotalPasajes);
		printf("PROMEDIO: $ %.2f\n", promedioPasajes);
		printf("PASAJEROS QUE SUPERAN EL PROMEDIO: %d\n", contadorPasajerosConPrecioAlto);
		printf("\n");

		retorno = 0;
	}

	return retorno;
}

int cargaForzadaDePasajeros(Passenger* list, int len, int *id){
	int retorno =-1;

	if(list!=NULL && len>0){
		if(addPassenger(list, len, *id, "Andres", "Almeida", 250000, 1, "EM1190" )==0 &&
				addPassenger(list, len, *id+1, "Karina", "Barreiro", 250000, 1, "EM1190" )==0 &&
				addPassenger(list, len, *id+2, "Pipe", "Almeida", 250000, 1, "EM1190" )==0 &&
				addPassenger(list, len, *id+3, "Gladys", "Salucho", 300000, 1, "CA1340" )==0 &&
				addPassenger(list, len, *id+4, "Ana", "Salucho", 300000, 1, "CA1340" )==0){
			*id += 5;
			retorno = 0;
		}
	}


	return retorno;
}
