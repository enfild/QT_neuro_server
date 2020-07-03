#include <QCoreApplication>
#include "include/NeuronetMaster.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    NeuronetMaster nMaster;

    return a.exec();
}
