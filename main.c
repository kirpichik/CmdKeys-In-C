//
//  main.c
//  CmdKeys
//
//  Created by Кирилл on 12.04.17.
//  Copyright © 2017 Кирилл. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "cmdkeys.h"

int main(const int argc, const char* argv[]) {
    
    // Получаем структуру для удобной обработки
    cmdkeys* keys = parseKeys(argc, argv);
    
    // Выводим все ключи и их аргументы
    printf("=== Keys: ===\n");
    for (size_t i = 0; i < keys->keysArrSize; i++) {
        printf("\"%s\" : ", keys->keys[i].name);
        
        if (keys->keys[i].value)
            printf("\"%s\"\n", keys->keys[i].value);
        else
            printf("enabled\n");
    }
    
    // Выводим оставшиеся аргументы
    printf("=== Args: ===\n");
    for (size_t i = 0; i < keys->globalArrSize; i++) {
        printf("%s\n", keys->globalArgs[i]);
    }
    
    // Освобождаем структуру
    freeCmdKeysStorage(keys);
    
    return 0;
}
