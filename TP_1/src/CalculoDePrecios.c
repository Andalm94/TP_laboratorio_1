#include <stdio.h>
#include <stdlib.h>
#include "CalculoDePrecios.h"

float CalcularAumento(float precio, float aumento){
	float resultado;

	resultado = precio + (precio * aumento);

	return resultado;
}

float CalcularDescuento(float precio, float descuento){
	float resultado;

	resultado = precio - (precio * descuento);

	return resultado;
}

float CalcularPrecioEnBTC(float precio, float valorBTC){
	float resultado;

	resultado = precio / valorBTC;

	return resultado;
}

float CalcularPrecioPorKilometro(float precio, float kilometros){
	float resultado;

	resultado = precio / kilometros;

	return resultado;
}

float CalcularDiferencialDePrecio(float precio1, float precio2){
	float diferencial;


	diferencial = precio1 - precio2;
	if (diferencial < 0){
		diferencial = diferencial * (-1);
	}


	return diferencial;
}
