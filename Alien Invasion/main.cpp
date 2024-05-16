#include "iostream"
#include "./src/simulationManager.h"
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    try {
        simulationManager simManager(Silent);
        simManager.chooseScenario();
        simulationManager::intro();
        if (simManager.getOperationMode() == Silent) {
            cout << "🔕🔇 Silent Mode\n"
                 << "⏩ Battle In Progress.";
            int timeStep{0};
            while (true)
                if (simManager.updateSimulation(timeStep++) != Nan)
                    break;
        } else {
            int timeStep{0};
            while (true) {
                if (simManager.getOperationMode() == Interactive) {
                    system("cls");
                    cout << "Current TimeStep is:" << timeStep << endl;
                    cout << "⏩ Press Enter to proceed to the next time step..." << endl;
                    cout << "Selected Scenario: " + simManager.getCurrentScenario().substr(0, 3) << endl;
                    if (simManager.updateSimulation(timeStep) != Nan)
                        break;
//                    cin.get();
                }
                timeStep++;
            }
        }
        simManager.loadToOutputFile();
    } catch (const runtime_error &e) {
        cout << "⚠️ " << e.what() << endl;
        cin.get();
        exit(0);
    }
    cin.get();
}
