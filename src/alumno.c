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
 * @param campo Nombre del campo
 * @param valor Contenido de texto
 * @param buffer Buffer de salida
 * @param size  Tamaño disponible para escribir la cadena
 * @return int Longitud del texto generado o -1 si el espacio no es suficiente
 */
static int SerializarTexto(char campo[], const char valor[], char buffer[], uint32_t size);

/**
 * @brief Serializa un campo numérico clave-valor en formato JSON.
 *
 * @param campo Nombre del campo
 * @param valor Valor numérico
 * @param buffer Buffer de salida
 * @param size  Tamaño disponible para escribir la cadena
 * @return int Longitud del texto generado o -1 si el espacio no es suficiente
 */
static int SerializarNumero(char campo[], int valor, char buffer[], uint32_t size);

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

static int SerializarTexto(char campo[], const char valor[], char buffer[], uint32_t size) {
    return snprintf(buffer, size, "\"%s\":\"%s\",", campo, valor);
}

static int SerializarNumero(char campo[], int valor, char buffer[], uint32_t size) {
    return snprintf(buffer, size, "\"%s\":%d", campo, valor);
}

/* === Public function implementation ============================================================================== */

int Serializar(const alumno_t* alumno, char buffer[], uint32_t size) {
    int escritos;
    int resultado;

    buffer[0] = '{';
    buffer++;
    escritos = 1;

    resultado = SerializarTexto("nombre", alumno->nombre, buffer, size - escritos);
    if (resultado < 0) {
        return -1;
    }

    escritos = escritos + resultado;
    buffer = buffer + resultado;
    resultado = escritos;
    escritos += SerializarTexto("apellido", alumno->apellido, buffer, size - escritos);
    if (escritos < 0) {
        return -1;
    }

    buffer = buffer + (escritos - resultado);
    resultado = escritos;

    escritos = escritos + SerializarNumero("documento", alumno->documento, buffer, size - escritos);
    if (escritos < 0) {
        return -1;
    }

    buffer = buffer + (escritos - resultado);

    if ((uint32_t)escritos >= (size - 1)) {
        return -1;
    } else {
        *buffer = '}';
        buffer++;
        *buffer = '\0';

        escritos = escritos + 2;
    }

    return escritos;
}

/* === End of documentation ======================================================================================== */
