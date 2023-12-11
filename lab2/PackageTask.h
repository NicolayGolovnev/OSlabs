//
// Created by kolya on 17.09.2023.
//

#ifndef OSLABS_PACKAGETASK_H
#define OSLABS_PACKAGETASK_H

#include "PackageTaskType.h"
#include <ctime>
#include <random>

#include "TaskExecution.h"

/** Пакетированная задача выполнения */
class PackageTask {
private:
    int operationCount = 0;
    PackageTaskType type;
    TaskExecution* execution;
    double executeTime = 0;

    void generateCountOfOperations() {
        int operationCount = 0;
        if (this->type == IO)
            // 35 <= operationCount <= 70
            operationCount = rand() % 35 + 35;
        else if (this->type == Process)
            // 0 <= operationCount <= 15
            operationCount = rand() % 15;
        else if (this->type == Balanced)
            // 15 <= operationCount <= 35
            operationCount = rand() % 20 + 15;

        this->operationCount = operationCount;
    }

public:
    PackageTask(PackageTaskType _type) {
        this->type = _type;
        this->execution = new TaskExecution();

        this->generateCountOfOperations();
        this->executeTime = this->execution->computeTotalExecutionTime(this->operationCount, this->type);
    }

    void printInfo() {
        printf("Task ");
        if (this->type == Process)
            printf("PROCESS");
        else if (this->type == IO)
            printf("IO\t");
        else if (this->type == Balanced)
            printf("BALANCED");

        printf("\toperations = %d", this->operationCount);
        printf("\ttotal execute time = %d", (int)this->executeTime);
        printf("\telapsed execute time = %d", this->execution->getElapsedExecutionTime() - (int)this->executeTime);
        printf("\n");
    }

    double getExecuteTime() {
        return this->executeTime;
    }

    TaskExecution* getExecutionObject() {
        return this->execution;
    }

    PackageTaskType getType() {
        return type;
    }
};


#endif //OSLABS_PACKAGETASK_H
