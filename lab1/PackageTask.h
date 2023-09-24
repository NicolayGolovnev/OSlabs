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
    const int PROCESS_OPERATION_EXECUTE_TIME = 5;
    const int NORMAL_OPERATION_EXECUTE_TIME = 10;
    const int IO_OPERATION_EXECUTE_TIME = 20;

    int operationCount = 0;
    PackageTaskType type;
    double executeTime = 0;

    void generateCountOfOperations() {
        int operationCount = 0;
        if (this->type == IO)
            // 35 <= operationCount <= 50
            operationCount = rand() % 15 + 35;
        else if (this->type == Process)
            // 0 <= operationCount <= 15
            operationCount = rand() % 15;
        else if (this->type == Balanced)
            // 15 <= operationCount <= 35
            operationCount = rand() % 20 + 15;

        this->operationCount = operationCount;
    }

    void executeTimeOperations() {
        if (type == IO)
            this->executeTime = IO_OPERATION_EXECUTE_TIME * operationCount;
        else if (type == Process)
            this->executeTime = PROCESS_OPERATION_EXECUTE_TIME * operationCount;
        else if (type == Balanced)
            this->executeTime = NORMAL_OPERATION_EXECUTE_TIME * operationCount;
    }
public:
    PackageTask(PackageTaskType _type) {
        this->type = _type;

        this->generateCountOfOperations();
        this->executeTimeOperations();
    }

    double getExecuteTime() {
        return this->executeTime;
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
        printf("\texecute time = %d", (int)this->executeTime);
        printf("\n");
    }
};


#endif //OSLABS_PACKAGETASK_H
