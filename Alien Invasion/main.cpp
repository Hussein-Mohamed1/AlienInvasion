#include "iostream"
#include "./src/simulationManager.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    try {
        simulationManager simManager(Interactive);
        simulationManager::intro();
        int timeStep{0};
        while (true) {
            int randNum = rand() % 100;
            system("cls");
            simManager.updateSimulation(timeStep);
            cout << "Current TimeStep is:" << timeStep;
            cout << "\n🔢 Current Random num is " << randNum << "\n";
            cout << "⏩ Press Enter to proceed to the next time step..." << endl;
            cin.get();
            timeStep++;
        }
    } catch (const runtime_error &e) {
        cout << "⚠️ " << e.what() << endl;
        cin.get();
        exit(0);
    }
    cin.get();
}
