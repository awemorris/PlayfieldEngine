#include <string.h>

const char *get_system_language(void);

const char *playfield_gettext(const char *msg)
{
    const char *lang_code = get_system_language();
    if (strcmp(msg, "Error: %s: %d: %s\n") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "エラー: %s: %d: %s\n";
        if (strcmp(lang_code, "ca") == 0) return "Error: %s: %d: %s\n";
        if (strcmp(lang_code, "es") == 0) return "Error: %s: %d: %s\n";
        if (strcmp(lang_code, "de") == 0) return "Fehler: %s: %d: %s\n";
        if (strcmp(lang_code, "it") == 0) return "Errore: %s: %d: %s\n";
        return "Error: %s: %d: %s\n";
    }
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
    if (strcmp(msg, "%s:%d: error: %s\n") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "%s:%d: エラー: %s\n";
        if (strcmp(lang_code, "ca") == 0) return "%s:%d: error: %s\n";
        if (strcmp(lang_code, "es") == 0) return "%s:%d: error: %s\n";
        if (strcmp(lang_code, "de") == 0) return "%s:%d: Fehler: %s\n";
        if (strcmp(lang_code, "it") == 0) return "%s:%d: errore: %s\n";
        return "%s:%d: error: %s\n";
    }
    if (strcmp(msg, "shell(): Parameter not a string.\n") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "shell(): 引数が文字列ではありません。\n";
        if (strcmp(lang_code, "ca") == 0) return "shell(): El paràmetre no és un string.\n";
        if (strcmp(lang_code, "es") == 0) return "shell(): El parámetro no es un string.\n";
        if (strcmp(lang_code, "de") == 0) return "shell(): Parameter ist kein String.\n";
        if (strcmp(lang_code, "it") == 0) return "shell(): Il parametro non è un string.\n";
        return "shell(): Parameter not a string.\n";
    }
    if (strcmp(msg, "Failed to load a texture.\n") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "テクスチャのロードに失敗しました。\n";
        return "Failed to load a texture.\n";
    }
    if (strcmp(msg, "file parameter is not set.\n") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "file引数がありません。\n";
        return "file parameter is not set.\n";
    }
    if (strcmp(msg, "No startup file.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "スタートアップファイルがありません。";
        return "No startup file.";
    }
    if (strcmp(msg, "Failed to initialize the graphics.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "グラフィックスの初期化に失敗しました。";
        return "Failed to initialize the graphics.";
    }
    if (strcmp(msg, "Failed to initialize sound.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "サウンドの初期化に失敗しました。";
        return "Failed to initialize sound.";
    }
    return msg;
}
