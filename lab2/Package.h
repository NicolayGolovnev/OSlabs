//
// Created by kolya on 17.09.2023.
//

#ifndef OSLABS_PACKAGE_H
#define OSLABS_PACKAGE_H

#include <vector>
#include "PackageTask.h"
#include "template/DictTemplate.h"

class Package {
private:
    int serial = -1;

    std::vector<PackageTask*>* tasks;
    double totalExecutionTime = 0;
    int totalElapsedExecutionTime = 0;
    Dictionary<PackageTaskType, int> typeTaskCount;

    void addTask(PackageTask *task) {
        this->tasks->push_back(task);
    }

    void executeTime() {
        totalExecutionTime = 0;
        totalElapsedExecutionTime = 0;
        for (PackageTask* task : *tasks) {
            totalExecutionTime += task->getExecuteTime();
            totalElapsedExecutionTime += task->getExecutionObject()->getElapsedExecutionTime();
        }
    }

    // TODO иногда зацикливается при выполнении, не могу найти этот момент
    void runDispatchingService() {
        int currentTask = 0;
        int executionTime = 1;

        int isDoneTasks = 0;

        while (this->tasks->size() > isDoneTasks) {
            int currentExecTime = 0;
            PackageTask* task = this->tasks->at(currentTask);
            // Заполняем время начала выполнение задачи, если фактически не начали ее
            task->getExecutionObject()->setProcessingStartIfNotStarted(executionTime);

            while (task->getExecutionObject()->isExecuteTaskNow(currentExecTime)) {
                // Если мы не сможем закончить выполенение задачи за отведенной время - выходим
                if (task->getExecutionObject()->isOperationNotEnded())
                    break;

                // Тратим время на выполнение
                task->getExecutionObject()->increaseExecutionTime();

                // Увеличиваем время выполнения
                executionTime++;
                currentExecTime++;

                // Если завершили выполнение задачи - выходим
                if (task->getExecutionObject()->isEndProcessTask(executionTime)) {
                    isDoneTasks++;
                    break;
                }
            }
            // Пересчитываем время выполнения у данной задачи
            task->getExecutionObject()->computeExecutionTime(currentExecTime);

            currentTask = (currentTask + 1) % this->tasks->size();
        }
    }

    void analyzeData() {
        for (PackageTask* task : *tasks) {
            PackageTaskType type = task->getType();
            this->typeTaskCount[type] = this->typeTaskCount[type] + 1;
        }

        printf("All tasks - %lu\n", tasks->size());
        printf("Process tasks - %f\n", (typeTaskCount[Process] * 1.0 / tasks->size() * 100));
        printf("Balanced tasks - %f\n", (typeTaskCount[Balanced] * 1.0 / tasks->size() * 100));
        printf("IO tasks - %f\n", (typeTaskCount[IO] * 1.0 / tasks->size() * 100));
    }

    void printInfo() {
        printf("Package #%d:\n", this->serial);
        for (auto* task : *tasks) {
            printf("\t");
            task->printInfo();
        }

        printf("All execution time = %d\n", (int)this->totalExecutionTime);
        printf("All elapsed execute time = %d\n\n", this->totalElapsedExecutionTime);
    }
public:
    Package(int _serial) {
        this->serial = _serial;
        this->tasks = new std::vector<PackageTask*>();

        this->typeTaskCount.clear();
        this->typeTaskCount.add(Process, 0);
        this->typeTaskCount.add(Balanced, 0);
        this->typeTaskCount.add(IO, 0);
    };

    void run() {
        // В зависимости от случайности получаем
        // какое то количество заданий от 5 до 40
        int taskCount = rand() % 35 + 5;

        for(int i = 0; i < taskCount; i++) {
            int taskType = std::rand() % 3;
            this->addTask(new PackageTask(static_cast<PackageTaskType>(taskType)));
        }

        // Запускаем обработку задач в диспетчере
        this->runDispatchingService();

        // Выполняем подсчет общего времени выполнения задач в пакете
        this->executeTime();

        this->analyzeData();

        this->printInfo();
    };
};

#endif //OSLABS_PACKAGE_H
