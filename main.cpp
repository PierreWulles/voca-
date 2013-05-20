#include <QApplication>

#include "VocaDow.h"
#include "VocaHelp.h"

int main(int argc, char *argv[])
{
    QApplication programme(argc, argv);
    VocaDow main;
    main.show();
    return programme.exec();
}
