//
// Created by ovi on 6/2/22.
//

#ifndef QTLAB10_OBSERVER_H
#define QTLAB10_OBSERVER_H
#include <vector>
#include <algorithm>

class Observer{
public:
    virtual void update() = 0;
};

class Observable{
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer *obs){
        observers.push_back(obs);
    }

    void removeObserver(Observer *obs){
        observers.erase(std::remove(begin(observers), end(observers), obs), observers.end());
    }

protected:
    void notify(){
        for(auto obs : observers){
            obs->update();
        }
    }
};

#endif //QTLAB10_OBSERVER_H
