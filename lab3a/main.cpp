#include "lib/bigNumber.h"

using namespace Prog3a;

const char *msgs[] = {" 0. Exit",
                      " 1. Create big number from string",
                      " 2. Create big number from long",
                      " 3. Get add code",
                      " 4. Add",
                      " 5. Subtract",
                      " 6. Increase by 10 times",
                      " 7. Decrease by 10 times"
};

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

int (*functions[])(bigDecNum &) = {nullptr, dialog_inputStr,
                                    dialog_inputLong,
                                    dialog_getAddCode,
                                    dialog_sum,
                                    dialog_sub,
                                    dialog_inc10,
                                    dialog_dec10
};


int main() {

    bigDecNum a;
    int rc = 0;

    while ((rc = dialog(msgs, NMsgs))) {
        if (!functions[rc](a))
            break;
    }

    std::cout << "Goodbye!" << std::endl;

    return 0;
}
