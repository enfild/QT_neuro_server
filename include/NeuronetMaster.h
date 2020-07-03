#ifndef TF_using_HEADER
#define TF_using_HEADER
#define QT_NO_KEYWORDS
#undef slots
#include "Python.h"
#include <QDebug>
#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QTcpServer>
#include "QFileSystemWatcher"
#include <QtNetwork/QHostAddress>
#include <QTimer>

#define slots

class NeuronetMaster: public QObject
{
    Q_OBJECT

public:

    NeuronetMaster();

    ~NeuronetMaster();

private:

    const QString imagePath = "sad";

    QFileSystemWatcher watcher;

    /// \ сокет TCP
    QScopedPointer<QTcpSocket> *m_sockets;

    QScopedPointer<QTcpServer> *m_server;

    int server_status;

    /// \ Инициализация Графа, загрузка его в память
    static void TF_init();

    /// \ Инициализация сокета
    bool connectSocket();

    /// \ прием
    static void reciveSocket();

    void sleep();

    /// \ отправка
    static void sendSocket();

    /// \ Обработка кадра инструментами Питона
    void TF_processing();

    ///\ подстраховка
    static bool TF_done();

    /// \ ОТправка точек
    static void pointSender();
};
#endif
