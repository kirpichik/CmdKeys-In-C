//
//  cmdkeys.c
//  CmdKeys
//
//  Created by Кирилл on 12.04.17.
//  Copyright © 2017 Кирилл. All rights reserved.
//

#include <stdlib.h>
#include <string.h>

#include "cmdkeys.h"

/** Выделяет переданную строку на куче.
 * str - Строка для выделения на куче. */
const char* reallocString(const char* str) {
    if (!str)
        return NULL;
    
    size_t len = strlen(str);
    if (!len)
        return NULL;
    
    char* newStr = (char*) malloc(sizeof(char) * len);
    if (!newStr)
        return NULL;
    
    strcpy(newStr, str);
    
    return newStr;
}

/** Подготавливает для удобного использования аргументы.
 * Ключи и их значения размещаются в структуре cmdkeys.
 * argc - Кол-во элементов в массиве argv.
 * argv - Массив строк, аргументов командной строки.
 * Возвращает: Структуру для хранения ключей. */
cmdkeys* parseKeys(const int argc, const char** argv) {
    // Подсчитываем кол-во ключей и кол-во остальных аргументов
    size_t keysNumber = 0;
    size_t otherNumber = argc;
    for (register size_t i = 0; i < argc; i++)
        if (argv[i][0] == '-') {
            keysNumber++;
            otherNumber--;
            // Отсекаем арументы к ключам
            if (i + 1 != argc && argv[i + 1][0] != '-')
                otherNumber--;
        }
    
    struct keyvalue* keys = (struct keyvalue*) malloc(keysNumber * sizeof(struct keyvalue));
    const char** globalArgs = (const char**) malloc(otherNumber * sizeof(const char*));
    
    keysNumber = 0;
    otherNumber = 0;
    for (register size_t i = 0; i < argc; i++) {
        if (argv[i][0] == '-') { // Запись ключей и их аргументов
            // Поиск встречавшихся уже ранее ключей
            struct keyvalue* key = NULL;
            for (register size_t j = 0; j < keysNumber; j++) {
                if (!strcmp(keys[j].name, argv[i] + 1)) {
                    key = &keys[j];
                    break;
                }
            }
            if (!key) { // Новый ключ
                const char* name = reallocString(argv[i] + 1);
                if (!name)
                    continue;
                key = &keys[keysNumber++];
                key->name = name;
                key->value = NULL;
            }
            
            // Запись следующего аргумента(не ключа) как аргумент данному ключу
            if (i + 1 != argc && argv[i + 1][0] != '-') {
                key->value = reallocString(argv[i + 1]);
                i++;
            }
        } else // Запись прочих аргументов
            globalArgs[otherNumber++] = reallocString(argv[i]);
    }
    
    cmdkeys* result = (cmdkeys*) malloc(sizeof(cmdkeys));
    result->keys = keys;
    result->keysArrSize = keysNumber;
    result->globalArgs = globalArgs;
    result->globalArrSize = otherNumber;
    
    return result;
}

/** Проверяет наличие ключа в аргументах.
 * storage - Структура для хранения ключей.
 * keyName - Имя ключа.
 * Возвращает: true, если ключ присутствует в аргументах. */
bool hasKey(cmdkeys* storage, const char* keyName) {
    return getKeyValue(storage, keyName);
}

/** Проверяет значение ключа
 * storage - Структура для хранения ключей.
 * keyName - Имя ключа.
 * value - Проверяемое значение.
 * Возвращает: true, если ключ существует и его значение эквивалентно value. */
bool equalKeyValue(cmdkeys* storage, const char* keyName, const char* value) {
    return !strcmp(getKeyValue(storage, keyName), value);
}

/** Получает значение ключа в аргументах.
 * storage - Структура для хранения ключей.
 * keyName - Имя ключа.
 * Возвращает: Строку, соответствующую ключу или NULL, если ключ не существует или его значение не задано. */
const char* getKeyValue(cmdkeys* storage, const char* keyName) {
    if (!storage || !keyName)
        return NULL;
    
    for (register size_t i = 0; i < storage->keysArrSize; i++)
        if (!strcmp(storage->keys[i].name, keyName))
            return storage->keys[i].value;
    
    return NULL;
}

/** Освобождает структуру для хранения ключей.
 * storage - Структура для освобождения. */
void freeCmdKeysStorage(cmdkeys* storage) {
    for (register size_t i = 0; i < storage->keysArrSize; i++) {
        free((char*) storage->keys[i].name);
        free((char*) storage->keys[i].value);
    }
    free(storage->keys);
    for (register size_t i = 0; i < storage->globalArrSize; i++)
        free((char*) storage->globalArgs[i]);
    free(storage->globalArgs);
    free(storage);
}
