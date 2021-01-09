#include "Table.h"

using namespace lab4;

const char *msgs[] = {"\t 0. Exit",
                      "\t 1. Register",
                      "\t 2. Unregister",
                      "\t 3. Show info about suite",
                      "\t 4. Show full table",
                      "\t 5. Filling in the Hotel",
};

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

int (*functions[])(Table& Tab) = {nullptr,
                                   dialog_add,
                                   dialog_del,
                                   dialog_find,
                                   dialog_show,
                                   dialog_suits
};

int main() {
    Table Tab = Table();
    int rc = 0;
    while ((rc = dialog(msgs, NMsgs))) {
        if (!functions[rc](reinterpret_cast<Table &>(Tab))) {
            break;
        }
    }
    return 0;
}
