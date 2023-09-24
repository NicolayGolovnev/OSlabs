//
// Created by kolya on 17.09.2023.
//

#ifndef OSLABS_PACKAGE_H
#define OSLABS_PACKAGE_H

#include <vector>
#include <cstring>
#include "Terminal.h"
#include "PackageTask.h"

class Package {
private:
    int serial = -1;
    PackageLevelType level;

    std::vector<PackageTask*>* tasks;
    double fullExecuteTime = 0;

    void addTask(PackageTask *task) {
        this->tasks->push_back(task);
    }

    void executeTime() {
        fullExecuteTime = 0;
        for (PackageTask* task : *tasks) {
            fullExecuteTime += task->getExecuteTime();
        }
    }

    void printInfo() {
        printf("Package #%d:\n", this->serial);
        for (auto* task : *tasks) {
            printf("\t");
            task->printInfo();
        }

        printf("All execution time = %d\n\n", (int)this->fullExecuteTime);
    }
public:
    Package(int _serial, PackageLevelType _level) {
        this->serial = _serial;
        this->level = _level;
        this->tasks = new std::vector<PackageTask*>();
    };

    void run() {
        // В зависимости от сложности пакета получаем кол-во заданий
        int taskCount = 0;
        if (this->level == Low)
            // 0..5
            taskCount = rand() % 5;
        else if (this->level == Medium)
            // 5..15
            taskCount = rand() % 10 + 5;
        else if (this->level == High)
            // 15..30
            taskCount = rand() % 15 + 15;

        for(int i = 0; i < taskCount; i++) {
            int taskType = std::rand() % 3;
            this->addTask(new PackageTask(static_cast<PackageTaskType>(taskType)));
        }

        // Выполняем подсчет общего времени выполнения задач в пакете
        this->executeTime();

        this->printInfo();
    };
};

#endif //OSLABS_PACKAGE_H
