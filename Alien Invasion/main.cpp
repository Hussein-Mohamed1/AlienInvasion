#include "iostream"
#include "./src/simulationManager.h"


int main() {
    try {
        simulationManager SimManger(Silent);
        for (int i = 0; i < 50; ++i) {
            system("CLS");
            cout << SimManger.getAlienUnitCount() << endl;
            cout << SimManger.getEarthUnitCount() << endl;

            cin.get();
        }


    } catch (const runtime_error &e) {
        cout << e.what();
        exit(0);
    }

}