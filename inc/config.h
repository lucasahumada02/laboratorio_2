#define TIPO_DE_MEMORIA 1

#if TIPO_DE_MEMORIA == 0
#define USAR_MEMORIA_DINAMICA
#else
#define USAR_MEMORIA_ESTATICA
#endif

#ifdef USAR_MEMORIA_ESTATICA
        #define ALUMNOS_MAX_INSTANCIAS 2 //!<Cantidad maxima de alumnos
#endif