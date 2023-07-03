#ifndef cJSON__h
#define cJSON__h

#ifdef __cplusplus
extern "C"
{
#endif

#if !defined(__WINDOWS__) && (defined(WIN32) || defined(WIN64) || defined(_MSC_VER) || defined(_WIN32))
#define __WINDOWS__
#endif

#ifdef __WINDOWS__

    /* When compiling for windows, we specify a specific calling convention to avoid issues where we are being called from a project with a different default calling convention.  For windows you have 3 define options:

    CJSON_HIDE_SYMBOLS - Define this in the case where you don't want to ever dllexport symbols
    CJSON_EXPORT_SYMBOLS - Define this on library build when you want to dllexport symbols (default)
    CJSON_IMPORT_SYMBOLS - Define this if you want to dllimport symbol

    For *nix builds that support visibility attribute, you can define similar behavior by

    setting default visibility to hidden by adding
    -fvisibility=hidden (for gcc)
    or
    -xldscope=hidden (for sun cc)
    to CFLAGS

    then using the CJSON_API_VISIBILITY flag to "export" the same symbols the way CJSON_EXPORT_SYMBOLS does

    */

#define CJSON_CDECL __cdecl
#define CJSON_STDCALL __stdcall

/* export symbols by default, this is necessary for copy pasting the C and header file */
#if !defined(CJSON_HIDE_SYMBOLS) && !defined(CJSON_IMPORT_SYMBOLS) && !defined(CJSON_EXPORT_SYMBOLS)
#define CJSON_EXPORT_SYMBOLS
#endif

#if defined(CJSON_HIDE_SYMBOLS)
#define CJSON_PUBLIC(type) type CJSON_STDCALL
#elif defined(CJSON_EXPORT_SYMBOLS)
#define CJSON_PUBLIC(type) __declspec(dllexport) type CJSON_STDCALL
#elif defined(CJSON_IMPORT_SYMBOLS)
#define CJSON_PUBLIC(type) __declspec(dllimport) type CJSON_STDCALL
#endif
#else /* !__WINDOWS__ */
#define CJSON_CDECL
#define CJSON_STDCALL

#if (defined(__GNUC__) || defined(__SUNPRO_CC) || defined(__SUNPRO_C)) && defined(CJSON_API_VISIBILITY)
#define CJSON_PUBLIC(type) __attribute__((visibility("default"))) type
#else
#define CJSON_PUBLIC(type) type
#endif
#endif

/* project version */
#define CJSON_VERSION_MAJOR 1
#define CJSON_VERSION_MINOR 7
#define CJSON_VERSION_PATCH 15

#include <stddef.h>

/* cJSON Types: */
#define cJSON_Invalid (0)
#define cJSON_False (1 << 0)              // 1
#define cJSON_True (1 << 1)               // 2
#define cJSON_NULL (1 << 2)               // 4
#define cJSON_Number (1 << 3)             // 8
#define cJSON_String (1 << 4)             // 16
#define cJSON_Array (1 << 5)              // 32
#define cJSON_Object (1 << 6)             // 64
#define cJSON_Raw (1 << 7) /* raw json */ // 256

#define cJSON_IsReference 256
#define cJSON_StringIsConst 512

    /* The cJSON structure: */
    typedef struct cJSON
    {
        struct cJSON *next;
        struct cJSON *prve;
        struct cJSON *child;

        int type;
        char *valuestring;
        int valueint;
        double valuedouble;
        char *string;

    } cJSON;

#ifdef __cplusplus
}
#endif
#endif