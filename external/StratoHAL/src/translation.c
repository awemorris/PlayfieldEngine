#include <string.h>

const char *get_system_language(void);

const char *stratohal_gettext(const char *msg)
{
    const char *lang_code = get_system_language();
    if (strcmp(msg, "Cannot open file \"%s\".\n") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "ファイル \"%s\" を開けません。\n";
        if (strcmp(lang_code, "ca") == 0) return "No es pot obrir el fitxer \"%s\".\n";
        if (strcmp(lang_code, "es") == 0) return "No se puede abrir el archivo \"%s\".\n";
        if (strcmp(lang_code, "de") == 0) return "Datei \"%s\" kann nicht geöffnet werden.\n";
        if (strcmp(lang_code, "it") == 0) return "Impossibile aprire il file \"%s\".\n";
        return "Cannot open file \"%s\".\n";
    }
    if (strcmp(msg, "Cannot read file \"%s\".\n") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "ファイル \"%s\" を読み込めません。\n";
        if (strcmp(lang_code, "ca") == 0) return "No es pot llegir el fitxer \"%s\".\n";
        if (strcmp(lang_code, "es") == 0) return "No se puede leer el archivo \"%s\".\n";
        if (strcmp(lang_code, "de") == 0) return "Datei \"%s\" kann nicht gelesen werden.\n";
        if (strcmp(lang_code, "it") == 0) return "Impossibile leggere il file \"%s\".\n";
        return "Cannot read file \"%s\".\n";
    }
    return msg;
}
