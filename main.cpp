#include <QCoreApplication>
#include "include/NeuronetMaster.h"
#include "include/CommunicationMaster.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CommunicationMaster cMaster("neuServer");

    NeuronetMaster nMaster;

    return a.exec();
}
