/*********************************************************************************************************************
Copyright (c) 2025, Lucas Ahumada Checa Casquero <lucasahum@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*********************************************************************************************************************/

#ifndef ALUMNO_H_
#define ALUMNO_H_

/** @file alumno.h
 ** @brief Definiciones y declaración de funciones del módulo Alumno
 **/

/* === Headers files inclusions ==================================================================================== */

/* === Header for C++ compatibility ================================================================================ */
#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

/**
 * @brief Estructura que representa a un alumno.
 */
typedef struct {
    char nombre[50];     /**< Nombre del alumno */
    char apellido[50];   /**< Apellido del alumno */
    int documento;       /**< Documento del alumno */
} Alumno;

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/**
 * @brief Serializa los datos de un alumno a formato JSON.
 * 
 * @param a Puntero constante al alumno
 * @param salida Buffer donde se escribe el JSON generado
 * @param tam Tamaño máximo del buffer de salida
 * @return int Longitud de la cadena generada o -1 si no hay suficiente espacio
 */
int Serializar(const Alumno *a, char *salida, int tam);

/* === End of conditional blocks =================================================================================== */
#ifdef __cplusplus
}
#endif

#endif /* ALUMNO_H_ */
