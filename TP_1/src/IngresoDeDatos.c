#include <stdio.h>
#include <stdlib.h>

int getInt(int * pNumeroIngresado, char * mensaje, char * mensajeError, int min, int max, int reintentos){

	int auxNumeroIngresado;
	int retorno;
	retorno = -1;

	if(pNumeroIngresado != NULL && max >= min && reintentos>= 0){
		do{
			printf("%s", mensaje);
			scanf("%d", &auxNumeroIngresado);
			reintentos--;

			if(auxNumeroIngresado >= min && auxNumeroIngresado <= max){
						*pNumeroIngresado = auxNumeroIngresado;
						retorno = 0;
						break;
			}else{
				printf("%s", mensajeError);
			}

		}while(reintentos > 0);
	}

	return retorno;
}

int getFloat(float * pNumeroIngresado, char * mensaje, char * mensajeError, int min, int max, int reintentos){

	float auxNumeroIngresado;
	int retorno;
	retorno = -1;

	if(pNumeroIngresado != NULL && max >= min && reintentos>= 0){
		do{
			printf("%s", mensaje);
			scanf("%f", &auxNumeroIngresado);
			reintentos--;

			if(auxNumeroIngresado >= min && auxNumeroIngresado <= max){
						*pNumeroIngresado = auxNumeroIngresado;
						retorno = 0;
						break;
			}else{
				printf("%s", mensajeError);
			}

		}while(reintentos > 0);
	}

	return retorno;
}
