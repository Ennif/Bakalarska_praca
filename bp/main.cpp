#include "APP/app_handler.h"

int main() {
    /*chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " [ms]" << endl;*/

   auto *appHandler = new app_handler();
   appHandler->mainProgram();
   return 0;
}









