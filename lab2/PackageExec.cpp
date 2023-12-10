//
// Created by kolya on 22.09.2023.
//

#include "Package.h"
#include "Terminal.h"

void runPackageExecute() {
    srand(time(NULL));
    int sessions = chooseSessions();

    std::vector<Package*> *packages = new std::vector<Package*>();
    for(int i = 0; i < sessions; i++)
        packages->push_back(new Package(i));

    for (auto* package : *packages)
        package->run();
}

int main() {
    runPackageExecute();

    return 0;
}