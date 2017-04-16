//
//  cmdkeys.h
//  CmdKeys
//
//  Created by Кирилл on 12.04.17.
//  Copyright © 2017 Кирилл. All rights reserved.
//

#include <stdbool.h>
#include <stddef.h>

struct keyvalue {
    const char* name;
    const char* value;
};

/** Структура для хранения разобраных ключей */
typedef struct cmdkeys {
    struct keyvalue* keys;
    size_t keysArrSize;
    const char** globalArgs;
    size_t globalArrSize;
} cmdkeys;

/** Подготавливает для удобного использования аргументы.
 * Ключи и их значения размещаются в структуре cmdkeys.
 * argc - Кол-во элементов в массиве argv.
 * argv - Массив строк, аргументов командной строки. 
 * Возвращает: Структуру для хранения ключей. */
cmdkeys* parseKeys(const int argc, const char** argv);

/** Проверяет наличие ключа в аргументах.
 * storage - Структура для хранения ключей.
 * keyName - Имя ключа.
 * Возвращает: true, если ключ присутствует в аргументах. */
bool hasKey(cmdkeys* storage, const char* keyName);

/** Проверяет значение ключа
 * storage - Структура для хранения ключей.
 * keyName - Имя ключа.
 * value - Проверяемое значение.
 * Возвращает: true, если ключ существует и его значение эквивалентно value. */
bool equalKeyValue(cmdkeys* storage, const char* keyName, const char* value);

/** Получает значение ключа в аргументах.
 * storage - Структура для хранения ключей.
 * keyName - Имя ключа. 
 * Возвращает: Строку, соответствующую ключу или NULL, если ключ не существует или его значение не задано. */
const char* getKeyValue(cmdkeys* storage, const char* keyName);

/** Освобождает структуру для хранения ключей.
 * storage - Структура для освобождения. */
void freeCmdKeysStorage(cmdkeys* storage);
