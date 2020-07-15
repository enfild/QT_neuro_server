#ifndef TF_using_HEADER
#define TF_using_HEADER
//#define QT_NO_KEYWORDS
#undef slots
//#define PY_SSIZE_T_CLEAN
#include "Python.h"
#define slots
#include <QDebug>
#include <QObject>
#include <QEventLoop>
#include <QTimer>
#include <QImage>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <QBuffer>

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

    NeuronetMaster();

    ~NeuronetMaster();

    /// \ Инициализация Графа, загрузка его в память
    void TF_init();

public slots:

    /// \ Обработка кадра инструментами Питона
    QString TF_processing(bool init, QImage imageQ);

private:
    PyObject *pModule; //create main module

    PyObject *main_dict;

    PyObject *imagePy;

    PyObject *translation;

    PyObject* representedString;

    PyObject* outString;

    QString points;

    QString finString;

    /// \ Обработка кадра инструментами Питона
    void Shower();

    ///\ подстраховка
    bool TF_done();

    /// \ чтение точек
    QString pointReader(PyObject *ItemString);

    /// \ парсер строки
    QString parserString(QString inString);

    void sleep();

    inline cv::Mat QImageToCvMat( const QImage &inImage, bool inCloneImageData = true );

};
#endif
