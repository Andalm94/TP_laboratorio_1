/*
 * Passenger.h
 *
 *  Created on: 19 may. 2022
 *
 */

#ifndef PASSENGER_H_
#define PASSENGER_H_

typedef struct
{
	int id;
	char nombre[50];
	char apellido[50];
	float precio;
	int tipoPasajero;
	char codigoVuelo[16];
	char estadoDeVuelo[16];

}Passenger;

Passenger* Passenger_new();

Passenger* Passenger_newParametros(char* id, char* nombre, char* apellido, char* codigoDeVuelo, char* tipoPasajero, char* precio, char* estadoDeVuelo);
void Passenger_delete(Passenger* this);


//--------------------------------------- MOSTRAR ---------------------------------------------

int mostrarPasajeros(Passenger **arrayPasajeros, int len);
int mostrarPasajero(Passenger *pPasajero);
int decodificarTipoDePasajero(char tipoDePasajeroStr[], int tipoDePasajeroint);


//--------------------------------------- ORDENAR Y COMPARAR ---------------------------------------------

int compararPasajerosPorID(void* primerPasajero, void* segundoPasajero);

int compararPasajerosPorNombre(void* primerPasajero, void* segundoPasajero);

int compararPasajerosPorApellido(void* primerPasajero, void* segundoPasajero);

int compararPasajerosPorCodigoVuelo(void* primerPasajero, void* segundoPasajero);

int compararPasajerosPorTipoPasajero(void* primerPasajero, void* segundoPasajero);

int compararPasajerosPorPrecio(void* primerPasajero, void* segundoPasajero);



//--------------------------------------- GET Y SET ---------------------------------------------

int Passenger_setId(Passenger* this,int id);
int Passenger_getId(Passenger* this);

int Passenger_setNombre(Passenger* this,char* nombre);
char* Passenger_getNombre(Passenger* this);

int Passenger_setApellido(Passenger* this,char* apellido);
char* Passenger_getApellido(Passenger* this);

int Passenger_setCodigoVuelo(Passenger* this,char* codigoVuelo);
char* Passenger_getCodigoVuelo(Passenger* this);

int Passenger_setTipoPasajero(Passenger* this,int tipoPasajero);
int Passenger_getTipoPasajero(Passenger* this);

int Passenger_setPrecio(Passenger* this,float precio);
float Passenger_getPrecio(Passenger* this);

int Passenger_setEstadoDeVuelo(Passenger* this,char* estadoDeVuelo);
char* Passenger_getEstadoDeVuelo(Passenger* this);

#endif /* PASSENGER_H_ */
