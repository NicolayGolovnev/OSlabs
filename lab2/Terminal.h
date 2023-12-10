//
// Created by kolya on 17.09.2023.
//

#ifndef OSLABS_TERMINAL_H
#define OSLABS_TERMINAL_H

#include <cstdio>
#include <iostream>
#include <string>


// Выбор кол-ва сессий
int chooseSessions() {
    int count;
    printf("\nChoose count of sessions in package of task:");
    scanf("%d", &count);
    if (count < 1) count = 1;
    printf("Current count of sessions - %d\n", count);

    return count;
}

// Вывод статистики ?
void printDefaultStatistic() {

}

#endif //OSLABS_TERMINAL_H
