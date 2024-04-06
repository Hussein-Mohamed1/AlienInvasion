#include "iostream"
#include "./src/simulationManager.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    try {
        simulationManager simManager(Silent);
        for (int i = 0; i < 50; ++i) {
            int randNum = rand() % 100;
            system("cls");
            simManager.updateSimulation(i);
            cout << "Current TimeStep is:" << i;
            cout << "\n🔢 Current Random num is " << randNum << "\n";
            cout << "👽 Alien Army Count is: " << simManager.getAlienUnitCount() << endl;
            cout << "🌍 Earth Army Count is: " << simManager.getEarthUnitCount() << endl;
            simManager.phase12TestFunction(randNum);
            cout << "⏩ Press Enter to proceed to the next time step..." << endl;
            cin.get();
        }
    } catch (const runtime_error &e) {
        cout << "⚠️ " << e.what() << endl;
        exit(0);
    }
}