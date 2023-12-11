//
// Created by Николай Головнев on 10.12.2023.
//

#ifndef EXECUTIONTIME_H
#define EXECUTIONTIME_H

class TaskExecution {
private:
    const int PROCESS_OPERATION_EXECUTE_TIME = 5;
    const int NORMAL_OPERATION_EXECUTE_TIME = 10;
    const int IO_OPERATION_EXECUTE_TIME = 20;
    int totalExecutionTime;    // Требуемое время для решения задачи
    int elapsedExecutionTime;  // Фактически потраченное время выполнение на задачу

    // TODO Лучше сделать через конструктор, но будем считать, что для всех задач
    //      у нас единая единица для выполнения задачи
    int timeSize = 128;              // единица выполнения требуемой задачи

    int processingStart = 0;        // Фактическое время начала выполнения задачи
    int processingEnd = 0;          // Фактическое время окончания выполнения задачи

public:
    // Высчитываем время выполнение для требуемой задачи
    int computeTotalExecutionTime(int operationCount, PackageTaskType type) {
        if (type == IO)
            this->totalExecutionTime = IO_OPERATION_EXECUTE_TIME * operationCount;
        else if (type == Process)
            this->totalExecutionTime = PROCESS_OPERATION_EXECUTE_TIME * operationCount;
        else if (type == Balanced)
            this->totalExecutionTime = NORMAL_OPERATION_EXECUTE_TIME * operationCount;

        return this->totalExecutionTime;
    }

    // Заполняем время начала выполнение задачи, если фактически не начали ее
    void setProcessingStartIfNotStarted(int procStart) {
        if (processingStart == 0)
            this->processingStart = procStart;
    }

    // Условие для выполнения задачи в данный момент времени
    bool isExecuteTaskNow(int executionTime) {
        return totalExecutionTime > elapsedExecutionTime &&
            timeSize > executionTime;
    }

    void increaseExecutionTime(int executionTime = 1) {
        this->elapsedExecutionTime += executionTime;
    }

    // Условие выполнения задачи
    bool isEndProcessTask(int procEnd) {
        bool isEnd = 0;

        if (elapsedExecutionTime >= totalExecutionTime) {
            isEnd = 1;
            processingEnd = procEnd;
        }

        return isEnd;
    }

    // Подсчет нового времени выполнения для задачи
    void computeExecutionTime(int executionTime) {
        // Если потратили меньше времени - пересчитаем время выполнения задачи
        if (executionTime > this->timeSize)
            this->timeSize -= (executionTime - this->timeSize);
        // Иначе нам нужно больше времени для выполнения задачи
        else
            this->timeSize = this->timeSize + 64;
    }

    // Получение потраченного времени на выполнение
    int getElapsedExecutionTime() {
        return processingEnd - processingStart;
    }

    bool isOperationNotEnded() {
        return totalExecutionTime > timeSize;
    }
};

#endif //EXECUTIONTIME_H
