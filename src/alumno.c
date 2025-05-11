/********************************************************************************************************************
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

/** @file alumno.c
 ** @brief Implementación del módulo Alumno
 **/

/* === Headers files inclusions ==================================================================================== */

#include "alumno.h"
#include <stdio.h>
#include <string.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/* === Private function declarations =============================================================================== */

/**
 * @brief Serializa un campo de texto clave-valor en formato JSON.
 * 
 * @param clave Nombre del campo
 * @param valor Contenido de texto
 * @param salida Buffer de salida
 * @return int Longitud del texto generado
 */
static int SerializarTexto(const char *clave, const char *valor, char *salida);

/**
 * @brief Serializa un campo numérico clave-valor en formato JSON.
 * 
 * @param clave Nombre del campo
 * @param valor Valor numérico
 * @param salida Buffer de salida
 * @return int Longitud del texto generado
 */
static int SerializarNumero(const char *clave, int valor, char *salida);

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

static int SerializarTexto(const char *clave, const char *valor, char *salida) {
    return sprintf(salida, "\"%s\":\"%s\"", clave, valor);
}

static int SerializarNumero(const char *clave, int valor, char *salida) {
    return sprintf(salida, "\"%s\":%d", clave, valor);
}

/* === Public function implementation ============================================================================== */

int Serializar(const Alumno *a, char *salida, int tam) {
    char buffer[256];
    int total = 0;

    total += sprintf(buffer + total, "{");
    total += SerializarTexto("nombre", a->nombre, buffer + total);
    total += sprintf(buffer + total, ",");
    total += SerializarTexto("apellido", a->apellido, buffer + total);
    total += sprintf(buffer + total, ",");
    total += SerializarNumero("documento", a->documento, buffer + total);
    total += sprintf(buffer + total, "}");

    if (total >= tam) return -1;

    strcpy(salida, buffer);
    return total;
}

/* === End of documentation ======================================================================================== */
