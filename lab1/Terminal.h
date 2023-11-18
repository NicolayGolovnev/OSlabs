//
// Created by kolya on 17.09.2023.
//

#ifndef OSLABS_TERMINAL_H
#define OSLABS_TERMINAL_H

#include <cstdio>
#include <iostream>
#include <string>

#include "PackageTaskUtil.h"

// Выбор кол-ва сессий
int chooseSessions() {
    int count;
    printf("\nChoose count of sessions in package of task:");
    scanf("%d", &count);
    if (count < 1) count = 1;
    printf("Current count of sessions - %d\n", count);

    return count;
}

// Выбор кол-ва заданий в пакете (зависит от уровня сложности)
PackageLevelType choosePackageTasksLevel() {
    PackageLevelType level = Low;
    printf("\nChoose level tasks of package:");
    printf("\n\t(Low, Medium, High)");
    printf("\nLevel=");

    std::string levelName;
    std::cin >> levelName;
    if (levelName == (char*)"Low")
        level = Low;
    else if (levelName == (char*)"Medium")
        level = Medium;
    else if (levelName == (char*)"High")
        level = High;
    else
        level = Low;

    printf("Current level tasks - ");
    if (level == Low)
        printf("Low\n");
    else if (level == Medium)
        printf("Medium\n");
    else
        printf("High\n");

    return level;
}

// Вывод статистики ?
void printDefaultStatistic() {

}

#endif //OSLABS_TERMINAL_H
