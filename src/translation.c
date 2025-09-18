#include <string.h>

const char *get_system_language(void);

const char *playfield_gettext(const char *msg)
{
    const char *lang_code = get_system_language();
    if (strcmp(msg, "Error: %s: %d: %s") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "エラー: %s: %d: %s";
        if (strcmp(lang_code, "ca") == 0) return "Error: %s: %d: %s";
        if (strcmp(lang_code, "es") == 0) return "Error: %s: %d: %s";
        if (strcmp(lang_code, "de") == 0) return "Fehler: %s: %d: %s";
        if (strcmp(lang_code, "it") == 0) return "Errore: %s: %d: %s";
        return "Error: %s: %d: %s";
    }
    if (strcmp(msg, "Cannot open file \"%s\".") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "ファイル \"%s\" を開けません。";
        if (strcmp(lang_code, "ca") == 0) return "No es pot obrir el fitxer \"%s\".";
        if (strcmp(lang_code, "es") == 0) return "No se puede abrir el archivo \"%s\".";
        if (strcmp(lang_code, "de") == 0) return "Datei \"%s\" kann nicht geöffnet werden.";
        if (strcmp(lang_code, "it") == 0) return "Impossibile aprire il file \"%s\".";
        return "Cannot open file \"%s\".";
    }
    if (strcmp(msg, "Cannot get the size of file \"%s\".") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "ファイル \"%s\" のサイズを取得できません。";
        return "Cannot get the size of file \"%s\".";
    }
    if (strcmp(msg, "Cannot read file \"%s\".") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "ファイル \"%s\" を読み込めません。";
        if (strcmp(lang_code, "ca") == 0) return "No es pot llegir el fitxer \"%s\".";
        if (strcmp(lang_code, "es") == 0) return "No se puede leer el archivo \"%s\".";
        if (strcmp(lang_code, "de") == 0) return "Datei \"%s\" kann nicht gelesen werden.";
        if (strcmp(lang_code, "it") == 0) return "Impossibile leggere il file \"%s\".";
        return "Cannot read file \"%s\".";
    }
    if (strcmp(msg, "shell(): Parameter not a string.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "shell(): 引数が文字列ではありません。";
        if (strcmp(lang_code, "ca") == 0) return "shell(): El paràmetre no és un string.g.";
        if (strcmp(lang_code, "es") == 0) return "shell(): El parámetro no es un string.";
        if (strcmp(lang_code, "de") == 0) return "shell(): Parameter ist kein String.";
        if (strcmp(lang_code, "it") == 0) return "shell(): Il parametro non è un string.";
        return "shell(): Parameter not a string.";
    }
    if (strcmp(msg, "In tag %s:%d: runtime error.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "タグ %s:%d: 実行エラー";
        return "In tag %s:%d: runtime error.";
    }
    if (strcmp(msg, "%s:%d: Tag \"%s\" not found.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "%s:%d: タグ \"%s\" がみつかりません。";
        return "%s:%d: Tag \"%s\" not found.";
    }
    if (strcmp(msg, "%s:%d: \"tag_%s\" is not a function.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "%s:%d: \"tag_%s\" が関数ではありません。";
        return "%s:%d: \"tag_%s\" is not a function.";
    }
    if (strcmp(msg, "In tag %s:%d: Tag \"%s\" execution error.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "タグ %s:%d: タグ \"%s\" の実行エラーです。";
        return "In tag %s:%d: Tag \"%s\" execution error.";
    }
    if (strcmp(msg, "Cannot determine the file type for \"%s\".") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "\"%s\" のファイルタイプを決定できません。";
        return "Cannot determine the file type for \"%s\".";
    }
    if (strcmp(msg, "Cannot load an image \"%s\".") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "画像 \"%s\" をロードできません。";
        return "Cannot load an image \"%s\".";
    }
    if (strcmp(msg, "Too many textures.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "テキスチャが多すぎます。";
        return "Too many textures.";
    }
    if (strcmp(msg, "Invalid font slot index.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "フォントスロットの番号が不正です。";
        return "Invalid font slot index.";
    }
    if (strcmp(msg, "Invalid sound stream index.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "サウンドストリームの番号が不正です。";
        return "Invalid sound stream index.";
    }
    if (strcmp(msg, "Cannot make the save directory.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "セーブディレクトリを作成できません。";
        return "Cannot make the save directory.";
    }
    if (strcmp(msg, "Save data key too long.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "セーブデータキーが長すぎます。";
        return "Save data key too long.";
    }
    if (strcmp(msg, "Cannot open a save file.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "セーブファイルを開けません。";
        return "Cannot open a save file.";
    }
    if (strcmp(msg, "Cannot write to a save file.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "セーブファイルに書き込めません。";
        return "Cannot write to a save file.";
    }
    if (strcmp(msg, "Cannot get the size of a save file.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "セーブファイルのサイズを取得できません。";
        return "Cannot get the size of a save file.";
    }
    if (strcmp(msg, "Save file too large.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "セーブファイルが大きすぎます。";
        return "Save file too large.";
    }
    if (strcmp(msg, "Cannot read a save file.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "セーブファイルを読み込めません。";
        return "Cannot read a save file.";
    }
    if (strcmp(msg, "String too long.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "文字列が長すぎます。";
        return "String too long.";
    }
    if (strcmp(msg, "Invalid save data.") == 0) {
        if (strcmp(lang_code, "ja") == 0) return "セーブデータが不正です。";
        return "Invalid save data.";
    }
    return msg;
}
