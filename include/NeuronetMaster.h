#ifndef TF_using_HEADER
#define TF_using_HEADER
#define QT_NO_KEYWORDS
#undef slots
//#define PY_SSIZE_T_CLEAN
#include "Python.h"
#include <QDebug>
#include <QObject>
#include <QEventLoop>
#include <QtNetwork/QUdpSocket>
#include "QFileSystemWatcher"
#include <QtNetwork/QHostAddress>
#include <QTimer>

#define slots

namespace  {
// колво катетеров
int countCath;
// координаты катетера
const int numCoordinates = 2;
int x;
int y;
}

class NeuronetMaster: public QObject
{
    Q_OBJECT

public:
    // открытая реализация
//        NeuronetMaster *q_ptr;

    NeuronetMaster();

    ~NeuronetMaster();

    /// \ Инициализация Графа, загрузка его в память
    void TF_init();

private:
    PyObject *pModule; //create main module

    PyObject *main_dict;

    PyObject *translation;

    const QString imagePath = "sad";

    QFileSystemWatcher watcher;

    /// \ сокет TCP
    QUdpSocket udpSocket;

    int server_status;

    /// \ Обработка кадра инструментами Питона
    bool TF_processing(bool init);

    /// \ Обработка кадра инструментами Питона
    static void Shower();

    ///\ подстраховка
    static bool TF_done();

    /// \ чтение точек
    QString pointReader(PyObject *ItemString);

    /// \ парсер строки
    void parserString(QString inString);

    /// \ Инициализация сокета
    void connectSocket();

    /// \ прием
    bool reciveSocket();

    void sleep();

    /// \ отправка
    bool sendSocket();


};
#endif
