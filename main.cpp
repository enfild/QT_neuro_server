#include <QCoreApplication>
#include <QObject>

#include "include/NeuronetMaster.h"
#include "include/CommunicationMaster.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CommunicationMaster cMaster("neuServer");

//    NeuronetMaster nMaster;

//    QObject::connect(cMaster, cMaster.recieveDone(), [ &nMaster] (QImage imageQ) {nMaster.TF_processing(false, imageQ); });


//    QObject::connect(cMaster, &cMaster.recieveDone(), nMaster, [=] () {nMaster.TF_processing(false, cMaster.imageQ); });

//QObject::connect(cMaster, &cMaster.recieveDone(image) , this, [this, i] () { function(i); });


//    QObject::connect(&cMaster, SIGNAL(recieveDone), &nMaster, SLOT(TF_processing(bool, )));


//    QObject::connect(cMaster, &CommunicationMaster::recieveDone(QImage *), [=](ima),  {NeuronetMaster::TF_processing(false);} );

//    QObject::connect(cMaster, SIGNAL(&CommunicationMaster::recieveDone(image)), cMaster, SLOT(&NeuronetMaster::TF_processing(false)));

//QObject::connect(cMaster, &cMaster.recieveDone(), nMaster, &nMaster.TF_processing() );

    return a.exec();
}
