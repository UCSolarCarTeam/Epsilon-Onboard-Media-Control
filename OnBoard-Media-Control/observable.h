#ifndef OBSERVABLE_H
#define OBSERVABLE_H
#pragma once
#include <vector>

// Note: All classes that inherit Observable must have an Observer interface

template <class T>
class Observable {
public:
    void add_listener(T* listener) {
        listeners.push_back(listener);
    }

protected:
    std::vector<T*> listeners;
};


#endif // OBSERVABLE_H

