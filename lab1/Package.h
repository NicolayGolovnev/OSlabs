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
    std::vector<PackageTask*>* tasks;
    double fullExecuteTime = 0;

    void executeTime() {
        fullExecuteTime = 0;
        for (PackageTask* task : *tasks) {
            fullExecuteTime += task->getExecuteTime();
        }
    }

public:
    Package(int _serial) {
        this->serial = _serial;
        this->tasks = new std::vector<PackageTask*>();
    };

    void addTask(PackageTask *task) {
        this->tasks->push_back(task);
    };

    void run() {
        this->executeTime();
    };
};

#endif //OSLABS_PACKAGE_H
