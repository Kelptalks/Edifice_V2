//
// Created by Spencer on 7/19/2024.
//

#ifndef EDIFICE_TIKEVENT_H
#define EDIFICE_TIKEVENT_H

enum TikType{
    TikLBM
};

struct TikEvent{
    enum TikType tikType;
    int* pointerToEntity;

};

#endif //EDIFICE_TIKEVENT_H
