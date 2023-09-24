//
// Created by kolya on 22.09.2023.
//

#include "Package.h"
#include "Terminal.h"

void runPackageExecute() {
    srand(time(NULL));
    int sessions = chooseSessions();

    std::vector<Package*> *packages = new std::vector<Package*>();
    for(int i = 0; i < sessions; i++) {
        PackageLevelType packageLevel = choosePackageTasksLevel();

        packages->push_back(new Package(i, packageLevel));
    }

    for (auto* package : *packages)
        package->run();
}