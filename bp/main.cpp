#include "APP/app_handler.h"

int main() {
    auto *appHandler = new app_handler();
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    appHandler->mainProgram();
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Time difference of program 1M entry "
         << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " [ms]" << endl;
   return 0;
}









