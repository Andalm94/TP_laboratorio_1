
#include <stdio.h>
#include <stdlib.h>
#include "IngresoDeDatos.h"
#include "CalculoDePrecios.h"

#define BTC 4606954.55

int main(void) {
	setbuf(stdout, NULL);

	int opcionMenu;
	int opcionSubMenu;
	int validacionRetorno;

	float kilometros = 0;
	float precioVueloAerolineas = 0;
	float precioVueloLatam = 0;


	int flagKMingresados = -1;
	int flagPrecioAerolineasIngresado = -1;
	int flagPrecioLatamIngresado = -1;
	int flagCostosCalculados = -1;

	float precioConDebitoAerolineas;
	float precioConCreditoAerolineas;
	float precioEnBitcoinAerolineas;
	float precioPorKilometroAerolineas;

	float precioConDebitoLatam;
	float precioConCreditoLatam;
	float precioEnBitcoinLatam;
	float precioPorKilometroLatam;


	float diferencialDePrecio;


	do{

		printf("---------------------------MENU PRINCIPAL---------------------------\n");
		printf("1) Ingresar kilometros: (KM = %.2f) \n", kilometros);
		printf("2) Ingresar precio de vuelos: (Aerolineas = %.2f, Latam = %.2f) \n", precioVueloAerolineas, precioVueloLatam);
		printf("3) Calcular todos los costos: \n");
		printf("4) Informar resultados: \n");
		printf("5) Carga forzada de datos: \n");
		printf("6) Salir\n");

		validacionRetorno = getInt(&opcionMenu, "Por favor seleccione una opcion:\n",
		"La opcion ingresada es invalida. Por favor intente nuevamente:\n", 1, 6, 3);

		if (validacionRetorno == 0){
			switch(opcionMenu){

			case 1:
				validacionRetorno = getFloat(&kilometros, "Por favor, ingrese la cantidad de kilometros:\n",
				"Por favor, intente nuevamente", 0, 25000, 3);
				flagKMingresados = 0;
				break;

			case 2:
				do{
					printf("Ingresar el precio de vuelos: \n");
					printf("1) Aerolineas \n");
					printf("2) Latam \n");
					printf("3) Volver al menu anterior: \n");

					validacionRetorno = getInt(&opcionSubMenu, "Por favor seleccione una opcion:\n",
					"La opcion ingresada es invalida. Por favor intente nuevamente:\n", 1, 6, 3);

					switch(opcionSubMenu){
						case 1:
							validacionRetorno = getFloat(&precioVueloAerolineas, "Por favor, ingreseel precio del vuelo:\n",
							"Por favor, intente nuevamente", 0, 5000000, 3);
							flagPrecioAerolineasIngresado = 0;
							break;
						case 2:
							validacionRetorno = getFloat(&precioVueloLatam, "Por favor, ingreseel precio del vuelo:\n",
							"Por favor, intente nuevamente", 0, 5000000, 3);
							flagPrecioLatamIngresado = 0;
							break;
					}

				}while(opcionSubMenu != 3);
				break;

			case 3:
				if(flagKMingresados == 0 && flagPrecioAerolineasIngresado == 0 && flagPrecioLatamIngresado == 0){

					precioConDebitoAerolineas = CalcularDescuento(precioVueloAerolineas, 0.1);
					precioConCreditoAerolineas = CalcularAumento(precioVueloAerolineas, 0.25);
					precioEnBitcoinAerolineas = CalcularPrecioEnBTC(precioVueloAerolineas, BTC);
					precioPorKilometroAerolineas = CalcularPrecioPorKilometro(precioVueloAerolineas, kilometros);

					precioConDebitoLatam = CalcularDescuento(precioVueloLatam, 0.1);
					precioConCreditoLatam = CalcularAumento(precioVueloLatam, 0.25);
					precioEnBitcoinLatam = CalcularPrecioEnBTC(precioVueloLatam, BTC);
					precioPorKilometroLatam = CalcularPrecioPorKilometro(precioVueloLatam, kilometros);

					diferencialDePrecio = CalcularDiferencialDePrecio(precioVueloLatam, precioVueloAerolineas);

					printf("Se han calculado los costos exitosamente. \n");
					flagCostosCalculados = 0;
				}
				else{
					printf("No se han podido calcular los costos. Por favor, revise haber ingresado Los kilometros y el precio de cada vuelo. \n");
				}
				break;

			case 4:
				if (flagCostosCalculados == 0){
					printf("---------------------------RESULTADOS---------------------------\n");
					printf("Precio Latam: $ %.2f \n", precioVueloLatam);
					printf("a) Precio con tarjeta de debito: $ %.2f \n", precioConDebitoLatam);
					printf("b) Precio con tarjeta de credito: $ %.2f  \n", precioConCreditoLatam);
					printf("c) Precio pagando con bitcoin: %.8f BTC \n", precioEnBitcoinLatam);
					printf("d) Precio unitario: $ %.2f \n", precioPorKilometroLatam);
					printf("\n");
					printf("Precio Aerolineas: $ %.2f \n", precioVueloAerolineas);
					printf("a) Precio con tarjeta de debito: $ %.2f \n", precioConDebitoAerolineas);
					printf("b) Precio con tarjeta de credito: $ %.2f  \n", precioConCreditoAerolineas);
					printf("c) Precio pagando con bitcoin: %.8f BTC \n", precioEnBitcoinAerolineas);
					printf("d) Precio unitario: $ %.2f \n", precioPorKilometroAerolineas);
					printf("\n");
					printf("La diferencia de precio es: $ %.2f \n", diferencialDePrecio);
				}
				else{
					printf("Aun no se han calculado los costos.\n");
				}
				break;

			case 5:

				precioConDebitoAerolineas = CalcularDescuento(162965, 0.1);
				precioConCreditoAerolineas = CalcularAumento(162965, 0.25);
				precioEnBitcoinAerolineas = CalcularPrecioEnBTC(162965, BTC);
				precioPorKilometroAerolineas = CalcularPrecioPorKilometro(162965, 7090);

				precioConDebitoLatam = CalcularDescuento(159339, 0.1);
				precioConCreditoLatam = CalcularAumento(159339, 0.25);
				precioEnBitcoinLatam = CalcularPrecioEnBTC(159339, BTC);
				precioPorKilometroLatam = CalcularPrecioPorKilometro(159339, 7090);

				diferencialDePrecio = CalcularDiferencialDePrecio(159339, 162965);

				printf("---------------------------RESULTADOS---------------------------\n");
				printf("Precio Latam: $ %.2f \n", precioVueloLatam);
				printf("a) Precio con tarjeta de debito: $ %.2f \n", precioConDebitoLatam);
				printf("b) Precio con tarjeta de credito: $ %.2f  \n", precioConCreditoLatam);
				printf("c) Precio pagando con bitcoin: %.8f BTC \n", precioEnBitcoinLatam);
				printf("d) Precio unitario: $ %.2f \n", precioPorKilometroLatam);
				printf("\n");
				printf("Precio Aerolineas: $ %.2f \n", precioVueloAerolineas);
				printf("a) Precio con tarjeta de debito: $ %.2f \n", precioConDebitoAerolineas);
				printf("b) Precio con tarjeta de credito: $ %.2f  \n", precioConCreditoAerolineas);
				printf("c) Precio pagando con bitcoin: %.8f BTC \n", precioEnBitcoinAerolineas);
				printf("d) Precio unitario: $ %.2f \n", precioPorKilometroAerolineas);
				printf("\n");
				printf("La diferencia de precio es: $ %.2f \n", diferencialDePrecio);

				break;

			case 6:
				break;
			}
		}


	}while(opcionMenu != 6);


	return EXIT_SUCCESS;
}
