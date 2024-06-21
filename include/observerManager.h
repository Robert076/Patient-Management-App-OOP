#include "observer.h"
#include <vector>
using namespace std;

class ObserverManager
{
private:
    vector<Observer*> observers;
public:
    ObserverManager() {}
    ~ObserverManager()
    {
        for(auto obs : observers)
            delete obs;
    }
    void registerObserver(Observer* newObserver)
    {
        observers.push_back(newObserver);
    }
    void notify()
    {
        for(auto obs : observers)
            obs->update();
    }
};