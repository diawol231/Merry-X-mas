#include "garland.h"
#include "QDebug"

// 0 - black
// 1 - green
// 2 - blue
// 3 - orange
// 4 - red


Garland::Garland()
{
    garlThread = INVALID_HANDLE_VALUE;
    hMutex = CreateMutexA( NULL, FALSE, "" );
    hUpdateEvt = CreateEvent( NULL, TRUE, TRUE, NULL );
    hStopEvt = CreateEvent( NULL, TRUE, FALSE, NULL );
    hClickEvt = CreateEvent( NULL, TRUE, TRUE, NULL );

}


Garland::~Garland(){
    stopWork();
    CloseHandle(hUpdateEvt);
}

std::vector<int> Garland::blackLine(){

    GarlandLocker guard(hMutex);
    for(int k = 0; k < sizeCol; k++){
        garlandArr[k] = 0;
    }
    return garlandArr;
}

void Garland::stopWork(){
    if (garlThread == INVALID_HANDLE_VALUE) return;
    SetEvent(hStopEvt);
    if(WaitForSingleObject(garlThread, 100) != WAIT_OBJECT_0) {
        TerminateThread(garlThread, 1);
    }
    CloseHandle(garlThread);
    garlThread = INVALID_HANDLE_VALUE;
}


DWORD WINAPI Garland::garlThrLine(LPVOID ptr){
    Garland* _this = (Garland*)ptr;
    if (!_this) return 1;
    for(;;){
        _this->setLight();
        if(WaitForSingleObject(_this->hStopEvt, 1000)!= WAIT_TIMEOUT){
            break;
        }
    }
    return 0;
}
void Garland::startLight(){
    if(garlThread != INVALID_HANDLE_VALUE) return;

    ResetEvent(hStopEvt);
    garlThread = CreateThread(NULL, 0, garlThrLine, this, 0, NULL);
}

void Garland::AlgrtmGarl_1(){
    if(WaitForSingleObject(hClickEvt, 0) != WAIT_OBJECT_0){
        for(int i = 0; i < sizeCol; i++)
            garlandArr[i] = 0;
        SetEvent(hClickEvt);
    }
    for(int j = 0; j < sizeCol; j++){
            garlandArr[j]+= step;
            if(garlandArr[j] > sizeCol)
                garlandArr[j] = 1;
    }

}
void Garland::AlgrtmGarl_2(){
    if(WaitForSingleObject(hClickEvt, 0) != WAIT_OBJECT_0){
        for(int i = 0; i < sizeCol; i++)
            garlandArr[i] = 0;
        SetEvent(hClickEvt);
    }

    if(colorSwitcher % 2 == 1){
        garlandArr[0] = 1;
        garlandArr[1] = 0;
        garlandArr[2] = 2;
        garlandArr[3] = 0;
        colorSwitcher++;
    }
    else{
        garlandArr[0] = 0;
        garlandArr[1] = 3;
        garlandArr[2] = 0;
        garlandArr[3] = 4;
        colorSwitcher++;
    }
}


void Garland::AlgrtmGarl_3(){
    if(WaitForSingleObject(hClickEvt, 0) != WAIT_OBJECT_0){
        for(int i = 0; i < sizeCol; i++)
            garlandArr[i] = i+step;
        SetEvent(hClickEvt);
    }

    for(int k = 0; k < sizeCol; k++){
        garlandArr[k]+=step;
        if(garlandArr[k] > sizeCol)
            garlandArr[k] = 1;
    }
}

bool Garland::isWorked(){
    return WaitForSingleObject(hUpdateEvt, 0) == WAIT_OBJECT_0;
}


std::vector<int> Garland::getLight(){
    GarlandLocker guard(hMutex);
    ResetEvent(hUpdateEvt);
    return garlandArr;
}

void Garland::setLight(){
    GarlandLocker guard(hMutex);

    if(countClckr == 1){
        AlgrtmGarl_1();
    }
    if(countClckr == 2){
        AlgrtmGarl_2();

   }
    if(countClckr == 3){
        AlgrtmGarl_3();
    }
    SetEvent(hUpdateEvt);
}

void Garland::inCreaseValue(){
    GarlandLocker guard(hMutex);
    countClckr++;
    ResetEvent(hClickEvt);
    if(countClckr > 3){
        countClckr = 1;
    }

}
