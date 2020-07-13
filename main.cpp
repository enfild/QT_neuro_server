#include <QCoreApplication>
#include <QObject>

#include "include/NeuronetMaster.h"
#include "include/CommunicationMaster.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CommunicationMaster cMaster("neuServer");

    NeuronetMaster nMaster;

//    QObject::connect(cMaster, &CommunicationMaster::recieveDone(QImage *), [=](ima),  {NeuronetMaster::TF_processing(false);} );

//    QObject::connect(cMaster, SIGNAL(&CommunicationMaster::recieveDone(image)), cMaster, SLOT(&NeuronetMaster::TF_processing(false)));


    return a.exec();
}
