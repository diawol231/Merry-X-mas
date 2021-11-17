#ifndef GARLAND_H
#define GARLAND_H

//#include <QMainWindow>
//#include <QObject>
#include <qt_windows.h>
#include <vector>
#include <map>


class GarlandLocker{
    HANDLE hMutex;
public:
    GarlandLocker(HANDLE mutex)
        :hMutex(mutex){
        WaitForSingleObject(hMutex, INFINITE);
    }
    ~GarlandLocker(){
        ReleaseMutex(hMutex);
    }

};

class Garland
{
    HANDLE garlThread;
    HANDLE hMutex;
    HANDLE hStopEvt;
    HANDLE hUpdateEvt;
    HANDLE hClickEvt;

    int step = 1;
    int sizeCol = 4;
    int colorSwitcher = 1;
    int countClckr = 1;
    std::vector<int> garlandArr = {0,0,0,0};


public:
    Garland();
    ~Garland();
    void stopWork();
    void startLight();
    std::vector<int> blackLine();

    void AlgrtmGarl_1();
    void AlgrtmGarl_2();
    void AlgrtmGarl_3();

    bool isWorked();
    void inCreaseValue();

    void setLight();
    std::vector<int> getLight();


private:

    static DWORD WINAPI garlThrLine(LPVOID ptr);
};



#endif // GARLAND_H
