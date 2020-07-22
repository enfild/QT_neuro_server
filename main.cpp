#include <QCoreApplication>
#include <QObject>
#include "include/NeuronetMaster.h"
#include "include/CommunicationMaster.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CommunicationMaster cMaster("neuServer");


    return a.exec();
}
