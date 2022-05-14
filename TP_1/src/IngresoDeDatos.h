#ifndef INGRESODEDATOS_H_
#define INGRESODEDATOS_H_

/**
 * \brief Solicita un INT al usuario, lo valida en un rango y lo retorna por referencia
 * \param pNumeroIngresado Puntero donde se almacena el valor del INT solicitado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje mostrado al ingresar un INT fuera de rango
 * \param min, max Valores que establecen el rango
 * \param reintentos Cantidad de veces que el usuario puede ingresar el dato fuera de rango
 * \return -1 si el usuario no ingreso un INT validado. 0 si se realizo la carga satisfactoriamente
 */
int getInt(int * pNumeroIngresado, char * mensaje, char * mensajeError, int min, int max, int reintentos);

/**
 * \brief Solicita un FLOAT al usuario, lo valida en un rango y lo retorna por referencia
 * \param pNumeroIngresado Puntero donde se almacena el valor del FLOAT solicitado
 * \param mensaje Es el mensaje a ser mostrado
 * \param mensajeError Es el mensaje mostrado al ingresar un INT fuera de rango
 * \param min, max Valores que establecen el rango
 * \param reintentos Cantidad de veces que el usuario puede ingresar el dato fuera de rango
 * \return -1 si el usuario no ingreso un FLOAT validado. 0 si se realizo la carga satisfactoriamente
 */
int getFloat(float * pNumeroIngresado, char * mensaje, char * mensajeError, int min, int max, int reintentos);


#endif
