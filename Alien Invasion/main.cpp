#include "iostream"
#include "./src/simulationManager.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    try {
        simulationManager simManager(Interactive);
        simulationManager::intro();
        int timeStep{0};
       for(int i=0 ; i<1000 ; i++) {
            int randNum = rand() % 100;
            system("cls");
            cout << "Current TimeStep is:" << timeStep;
            cout << "\n🔢 Current Random num is " << randNum << "\n";
            cout << "⏩ Press Enter to proceed to the next time step..." << endl;
            simManager.updateSimulation(timeStep);
            cin.get();
            timeStep++;
        }
       simManager.loadtoOutputFile();
    } catch (const runtime_error &e) {
        cout << "⚠️ " << e.what() << endl;
        cin.get();
        exit(0);
    }
    cin.get();
}
