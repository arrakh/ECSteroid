//
// Created by Arya Rakha on 8/2/2023.
//

#ifndef ECSTEROID_IWINDOW_H
#define ECSTEROID_IWINDOW_H


#include "../services/core/ServiceLocator.h"

class IWindow {
public:
    virtual ~IWindow() {}

    virtual bool TryInitialize(ServiceLocator& serviceLocator) = 0;
    virtual bool IsOpen() const = 0;
    virtual void End() = 0;
    virtual void PollEvents() = 0;
    virtual void Clear() = 0;
    virtual void Render() = 0;
};


#endif //ECSTEROID_IWINDOW_H
