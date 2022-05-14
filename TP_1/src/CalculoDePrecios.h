#ifndef CALCULODEPRECIOS_H_
#define CALCULODEPRECIOS_H_


/**
 * \brief Aplica al primer parametro el aumento porcentual del segundo parametro y lo retorna
 * \param precio Variable sobre la que se calcula el aumento
 * \param aumento Variable que establece el aumento
 * \return El primer parametro aumentado
 */
float CalcularAumento(float precio, float aumento);

/**
 * \brief Aplica al primer parametro el descuento porcentual del segundo parametro y lo retorna
 * \param precio Variable sobre la que se calcula el descuento
 * \param aumento Variable que establece el descuento
 * \return El primer parametro descontado
 */
float CalcularDescuento(float precio, float descuento);


/**
 * \brief Calcula el precio en BTC y lo retorna
 * \param precio Variable que define el total
 * \param valorBTC Variable que divide el total
 * \return El valor traducido a BTC del primer parametro
 */
float CalcularPrecioEnBTC(float precio, float valorBTC);


/**
 * \brief Calcula el precio por cada kilometro y lo retorna
 * \param precio Variable que define el total
 * \param kilometros variable que divide al primer parametro
 * \return El valor del primer parametro dividido por el segundo
 */
float CalcularPrecioPorKilometro(float precio, float kilometros);


/**
 * \brief Calcula el diferencial de los dos parametros y lo retorna
 * \param precio1, precio2 Variables a calcular su diferencia
 * \return El diferencial de ambos parametros, siempre como valor positivo (mayor a 0)
 */
float CalcularDiferencialDePrecio(float precio1, float precio2);


#endif
