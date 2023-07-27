//
// Created by Arya Rakha on 7/27/2023.
//

#ifndef ECSTEROID_ILOADABLESERVICE_H
#define ECSTEROID_ILOADABLESERVICE_H


class ILoadableService {
public:
    virtual void Load() = 0;
    virtual void Unload() = 0;
};


#endif //ECSTEROID_ILOADABLESERVICE_H
