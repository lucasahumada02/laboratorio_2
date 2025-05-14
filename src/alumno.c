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
#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/* === Macros definitions ========================================================================================== */
#ifdef USAR_MEMORIA_ESTATICA
    #ifndef ALUMNOS_MAX_INSTANCIAS
        #define ALUMNOS_MAX_INSTANCIAS 2 //!<Cantidad maxima de alumnos
    #endif
#endif
/* === Private data type declarations ============================================================================== */
struct alumno_s {
    char nombre[20];     //!< Nombre del alumno
    char apellido[20];   //!< Apellido del alumno
    uint32_t documento;  //!< Documento del alumno
#ifndef USAR_MEMORIA_ESTATICA
    bool ocupado;       //!<Indica si la instancia esta ocupada
#endif
};
/* === Private function declarations =============================================================================== */

/**
 * @brief Crea una nueva instancia de la estructura alumno_s.
 *
 * @return Puntero a la nueva instancia de alumno_s, o NULL si no hay espacio disponible.
 */
#ifdef USAR_MEMORIA_ESTATICA
static alumnoT CrearInstancia(void);
#endif
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
#ifdef USAR_MEMORIA_ESTATICA
    static struct alumno_s instancias[ALUMNOS_MAX_INSTANCIAS]={0};
#endif
/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */
#ifdef USAR_MEMORIA_ESTATICA
static alumno_t CrearInstancia(){
    alumno_t self = NULL;
    for (int i = 0; i < ALUMNOS_MAX_INSTANCIAS; i++)
    {
        if (!instancias[i].ocupado)
        {
            instancias[i].ocupado = true;
            self = &instancias[i];
            break;
        }
        
    }
    
   return self;
    
}
#endif
static int SerializarTexto(char campo[], const char valor[], char buffer[], uint32_t size) {
    return snprintf(buffer, size, "\"%s\":\"%s\",", campo, valor);
}

static int SerializarNumero(char campo[], int valor, char buffer[], uint32_t size) {
    return snprintf(buffer, size, "\"%s\":%d", campo, valor);
}

/* === Public function implementation ============================================================================== */
alumno_t CrearAlumno(char* nombre, char* apellido, uint32_t dni) {
    #ifndef USAR_MEMORIA_DINAMICA
        alumno_t self = malloc(sizeof(struct alumno_s));
    #else
        alumno_t self = CrearInstancia();
    #endif
    if (self != NULL) {
        self->documento = dni;
        strncpy(self->nombre, nombre, sizeof(self->nombre) - 1);
        strncpy(self->apellido, apellido, sizeof(self->apellido) - 1);
    } 
    return self;
}

int SerializarAlumno(alumno_t self, char *buffer, int size) {
    int escritos;
    int resultado;

    buffer[0] = '{';
    buffer++;
    escritos = 1;

    resultado = SerializarTexto("nombre", self->nombre, buffer, size - escritos);
    if (resultado < 0) {
        return -1;
    }

    escritos = escritos + resultado;
    buffer = buffer + resultado;
    resultado = escritos;
    escritos += SerializarTexto("apellido", self->apellido, buffer, size - escritos);
    if (escritos < 0) {
        return -1;
    }

    buffer = buffer + (escritos - resultado);
    resultado = escritos;

    escritos = escritos + SerializarNumero("documento", self->documento, buffer, size - escritos);
    if (escritos < 0) {
        return -1;
    }

    buffer = buffer + (escritos - resultado);

    if (escritos >= (size - 1)) {
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
