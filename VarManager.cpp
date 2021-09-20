//
// Created by amit on 23/12/2019.
//

#include <string>
#include "VarManager.h"
#include <bits/stdc++.h>

#include "mutex"

using namespace std;
mutex locker;
mutex locker2;

//adding new variable to maps
void VarManager::addTomaps(string name, string path, double val, int kriha) {
    locker.lock();
    VarInfo *temp = new VarInfo(val, kriha, name);
    path.erase(remove(path.begin(), path.end(), '"'), path.end());
    this->symbolMap2[name] = temp;
    this->pathMap[path] = temp;
    this->symbolMap2[name]->sim = path;
    locker.unlock();
}

//constractor
VarManager::VarManager() {
    XML();
}

//update information of variable in maps
void VarManager::setSymbol(string name, double value) {
    //mutex to lock this func to avoid multi thread using
    locker2.lock();
    string temp = name + "=" + to_string(value);
    this->l->setVariables(temp);//set variable value to use it for caculate expressions
    this->symbolMap2[name]->value = value;
    if (this->symbolMap2[name]->kriha == 1) {
        string message;
        message = "set " + this->symbolMap2[name]->sim + " " + to_string(value) + "\r\n";
        this->commandQ.push(message);
    }
    locker2.unlock();
}

//getting the information of the XML file
void VarManager::XML() {
    this->xmlList.push_back("/instrumentation/airspeed-indicator/indicated-speed-kt");
    this->xmlList.push_back("/sim/time/warp");
    this->xmlList.push_back("/controls/switches/magnetos");
    this->xmlList.push_back("/instrumentation/heading-indicator/offset-deg");
    this->xmlList.push_back("/instrumentation/altimeter/indicated-altitude-ft");
    this->xmlList.push_back("/instrumentation/altimeter/pressure-alt-ft");
    this->xmlList.push_back("/instrumentation/attitude-indicator/indicated-pitch-deg");
    this->xmlList.push_back("/instrumentation/attitude-indicator/indicated-roll-deg");
    this->xmlList.push_back("/instrumentation/attitude-indicator/internal-pitch-deg");
    this->xmlList.push_back("/instrumentation/attitude-indicator/internal-roll-deg");
    this->xmlList.push_back("/instrumentation/encoder/indicated-altitude-ft");
    this->xmlList.push_back("/instrumentation/encoder/pressure-alt-ft");
    this->xmlList.push_back("/instrumentation/gps/indicated-altitude-ft");
    this->xmlList.push_back("/instrumentation/gps/indicated-ground-speed-kt");
    this->xmlList.push_back("/instrumentation/gps/indicated-vertical-speed");
    this->xmlList.push_back("/instrumentation/heading-indicator/indicated-heading-deg");
    this->xmlList.push_back("/instrumentation/magnetic-compass/indicated-heading-deg");
    this->xmlList.push_back("/instrumentation/slip-skid-ball/indicated-slip-skid");
    this->xmlList.push_back("/instrumentation/turn-indicator/indicated-turn-rate");
    this->xmlList.push_back("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
    this->xmlList.push_back("/controls/flight/aileron");
    this->xmlList.push_back("/controls/flight/elevator");
    this->xmlList.push_back("/controls/flight/rudder");
    this->xmlList.push_back("/controls/flight/flaps");
    this->xmlList.push_back("/controls/engines/engine/throttle");
    this->xmlList.push_back("/controls/engines/current-engine/throttle");
    this->xmlList.push_back("/controls/switches/master-avionics");
    this->xmlList.push_back("/controls/switches/starter");
    this->xmlList.push_back("/engines/active-engine/auto-start");
    this->xmlList.push_back("/controls/flight/speedbrake");
    this->xmlList.push_back("/sim/model/c172p/brake-parking");
    this->xmlList.push_back("/controls/engines/engine/primer");
    this->xmlList.push_back("/controls/engines/current-engine/mixture");
    this->xmlList.push_back("/controls/switches/master-bat");
    this->xmlList.push_back("/controls/switches/master-alt");
    this->xmlList.push_back("/engines/engine/rpm");
}