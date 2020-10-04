//
// Created by user on 04.10.2020.
//
#include "Lemniscate.h"

using namespace Prog2;

const char *msgs[] = {" 0. Exit",
                      " 1. Input inner focus",
                      " 2. Show formula of lemniscate",
                      " 3. Get polar distance depending on angle",
                      " 4. Get radius of curvature depending on the angle",
                      " 5. Get radius of curvature depending on the length of the polar radius.",
                      " 6. Get the area of the polar sector of lemniscate",
                      " 7. Get the area of lemniscate"
};

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

int (*functions[])(Lemniscate &) = {nullptr, dialog_input,
                                    dialog_showFormula,
                                    dialog_getPolarDist,
                                    dialog_getRadiusAngle,
                                    dialog_getRadiusRad,
                                    dialog_getAreaSector,
                                    dialog_getArea};


int main() {
    Lemniscate Lemniscate;

    int rc = 0;

    while ((rc = dialog(msgs, NMsgs))) {
        if (!functions[rc](Lemniscate))
            break;
    }

}