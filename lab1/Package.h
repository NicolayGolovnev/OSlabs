//
// Created by kolya on 17.09.2023.
//

#ifndef OSLABS_PACKAGE_H
#define OSLABS_PACKAGE_H

#include <vector>
#include "Terminal.h"
#include "PackageTask.h"

class Package {
private:
    std::vector<PackageTask> tasks;
public:
    Package();

    void addTask(PackageTask task);

    void run();
};

#endif //OSLABS_PACKAGE_H
