//
// Created by kolya on 17.09.2023.
//

#ifndef OSLABS_PACKAGETASK_H
#define OSLABS_PACKAGETASK_H

#include "PackageTaskUtil.h"
#include <ctime>
#include <random>

/** Пакетированная задача выполнения */
class PackageTask {
private:
    const int IO_OPERATION_EXECUTE_TIME = 20;
    const int NORMAL_OPERATION_EXECUTE_TIME = 5;

    int operationCount = 0;
    PackageTaskType type;
    double executeTime = 0;

    void generateCountOfOperations() {
        srand((unsigned) time(NULL));

        int operationCount = 0;
        if (this->type == IO)
            operationCount = rand() % 30 + 20;
        else if (this->type == Balanced)
            operationCount = rand() % 20;
        this->operationCount = operationCount;
    }

    void executeTimeOperations() {
        if (type == IO)
            this->executeTime = IO_OPERATION_EXECUTE_TIME * operationCount;
        else if (type == Balanced)
            this->executeTime = NORMAL_OPERATION_EXECUTE_TIME * operationCount;
    }
public:
    PackageTask(PackageTaskType _type) {
        this->type = _type;

        this->generateCountOfOperations();
        this->executeTimeOperations();
    }

    void printInfo() {

    }

    double getExecuteTime() {
        return this->executeTime;
    }
};


#endif //OSLABS_PACKAGETASK_H
