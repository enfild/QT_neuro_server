#define QT_NO_KEYWORDS
#undef slots
#include "include/NeuronetMaster.h"
#define slots
#include "include/CommunicationMaster.h"

NeuronetMaster::NeuronetMaster() : QObject(nullptr)
{
//    CommunicationMaster cMaster("neuServer");

    qInfo() << "TF_using";
    if (!Py_IsInitialized()){
        Py_Initialize();
    }
    pModule = PyImport_AddModule("__main__"); //create main module
    main_dict   = PyModule_GetDict(pModule);

    TF_init();
}

NeuronetMaster::~NeuronetMaster()
{
    qInfo() << "~TF_using";

    Py_Finalize();
}

void NeuronetMaster::sleep()
{
    QEventLoop loop;
    QTimer::singleShot(100, &loop, SLOT(quit()));
    loop.exec();
}

bool NeuronetMaster::TF_done()
{
    qInfo() << "TF_done";
    PyRun_SimpleString("cv2.destroyWindow('GUI')	\n");
    //    PyRun_SimpleString("sys.exit()");
    // Py_Finalize();
    return true;
}


void NeuronetMaster::TF_init()
{
    qInfo() << "START PY_INIT";

    PyRun_SimpleString(
                "import os	\n"\
                "import sys	\n"\
                "import cv2	\n"\
                "import numpy as np	\n"\
                "import tensorflow as tf	\n"\
                "from datetime import datetime	\n"\
                "from utils import label_map_util	\n"\
                "from utils import visualization_utils as vis_util	\n"\
                );

    qInfo() << "INIT TF DONE!";

    PyRun_SimpleString(
                "MODEL_NAME = 'inference_graph'	\n"\
                "CWD_PATH = 'C:/neuronet/object_detection'	\n"\
                "PATH_TO_CKPT = os.path.join(CWD_PATH, MODEL_NAME, 'frozen_inference_graph.pb')	\n"\
                "PATH_TO_LABELS = os.path.join(CWD_PATH, 'data', 'object-detection.pbtxt')	\n"\
                "PATH_TO_IMAGE = 'C:/neuronet/Temp_frame/0.png'	\n"\
                "PATH_TO_IMAGE_EX = 'C:/neuronet/Example_frame/0.png'	\n"\
                "NUM_CLASSES = 2	\n"\
                "NumbFrame = 0	\n"\
                "label_map = label_map_util.load_labelmap(PATH_TO_LABELS)	\n"\
                "categories = label_map_util.convert_label_map_to_categories(label_map, max_num_classes = NUM_CLASSES, use_display_name = True)	\n"\
                "category_index = label_map_util.create_category_index(categories)	\n"
                "tf.device('device:GPU:0')	\n"\
                "config = tf.ConfigProto()	\n"\
                "config.gpu_options.visible_device_list= '0'	\n"\
                "config.gpu_options.per_process_gpu_memory_fraction = 0.4	\n"\
                "sess = tf.Session(config = config)	\n"\
                "detection_graph = tf.Graph()	\n"\
                "print('READY TO RAD GRAPH')	\n"\
                "detection_graph = tf.Graph()	\n"\
                "with detection_graph.as_default() :	\n"\
                "	od_graph_def = tf.GraphDef()	\n"\
                "	with tf.gfile.GFile(PATH_TO_CKPT, 'rb') as fid :	\n"\
                "		serialized_graph = fid.read()	\n"\
                "		od_graph_def.ParseFromString(serialized_graph)	\n"\
                "		tf.import_graph_def(od_graph_def, name = '')	\n"\
                "	sess = tf.Session(graph = detection_graph, config = config)	\n"\
                "image_tensor = detection_graph.get_tensor_by_name('image_tensor:0')	\n"\
                "detection_boxes = detection_graph.get_tensor_by_name('detection_boxes:0')	\n"\
                "detection_scores = detection_graph.get_tensor_by_name('detection_scores:0')	\n"\
                "detection_classes = detection_graph.get_tensor_by_name('detection_classes:0')	\n"\
                "num_detections = detection_graph.get_tensor_by_name('num_detections:0')	\n"\
                );

    NeuronetMaster::TF_processing(true);


    qInfo() << "INIT GRAPH DONE";
}

QString NeuronetMaster::TF_processing(bool init)
{
//    sleep();
    PyRun_SimpleString(
                "print('TF_PROCESSIVNG')	\n"\
                "start_time = datetime.now()	\n"\
                );
    if(!init)
    {
        PyRun_SimpleString(
                    "image = cv2.imread(PATH_TO_IMAGE_EX)	\n"\
                    );
    }
    else
    {
        PyRun_SimpleString(
                    "image = cv2.imread(PATH_TO_IMAGE_EX)	\n"\
                    );
    }
    PyRun_SimpleString(
                "image = cv2.resize(image, (1024, 1024))	\n"\
                "image_expanded = np.expand_dims(image, axis = 0)	\n"\
                "print(datetime.now() - start_time)	\n"\
                "(boxes, scores, classes, num) = sess.run(	\n"\
                "	[detection_boxes, detection_scores, detection_classes, num_detections],	\n"\
                "	feed_dict = { image_tensor: image_expanded })	\n"\
                "scores = np.squeeze(scores)	\n"\
                "boxes = np.squeeze(boxes)	\n"\
                "classes = np.squeeze(classes)	\n"\
                "max_boxes_to_draw = boxes.shape[0]	\n"\
                "height = image.shape[0]	\n"\
                "width = image.shape[1]	\n"\
                "channels = image.shape[2]	\n"\
                "listCoordinates = []	\n"\
                "for i in range(min(max_boxes_to_draw, boxes.shape[0])) :	\n"\
                "	if scores is None or scores[i] > 0.5:	\n"\
                "		if classes[i] == 2 :	\n"\
                "			box = tuple(boxes[i].tolist())	\n"\
                "			ymin, xmin, ymax, xmax = box	\n"\
                "			start_point = (int(xmin * height), int(ymin * width))	\n"\
                "			end_point = (int(xmax * height), int(ymax * width))	\n"\
                "			color = (0, 255, 0)	\n"\
                "			center_coordinates = (int((xmax*height + xmin*height) / 2), int((ymax*width + ymin*width) / 2))	\n"\
                "			print(center_coordinates)	\n"\
                "			image = cv2.circle(image, center_coordinates, 15, color, 3)	\n"\
                "			listCoordinates.append(center_coordinates)	\n"\
                "print(listCoordinates)	\n"\
                );

    translation = PyDict_GetItemString(main_dict, "listCoordinates");
    points = pointReader(translation);
    outString = parserString(points);

    CommunicationMaster::sendToClient(CommunicationMaster::localSocket, outString);

    Shower();

    return outString;
}

void NeuronetMaster::Shower()
{
    PyRun_SimpleString(
                "NumbFrame += 1	\n"\
                "cv2.imshow('GUI', image)	\n"\
                "os.remove(PATH_TO_IMAGE)	\n"\
                "print('PROCESSING IS DONE')	\n"\
                "print(datetime.now() - start_time)	\n"\
                );
}

QString NeuronetMaster::pointReader(PyObject *ItemString)
{
    PyObject* representedString = PyObject_Repr(ItemString);
    PyObject* outString = PyUnicode_AsUTF8String(representedString);
    const char *bytesPoints = PyBytes_AS_STRING(outString);
    QString out = QString::fromUtf8(bytesPoints);
    qDebug() << out << "POINT READER";
    return out;
}

QString NeuronetMaster::parserString(QString inString)
{
    inString.remove(0, 1);
    inString.chop(1);
    inString.remove(QRegExp("[()]+"));

    qDebug() << inString << "CROPED STRING";
    countCath = inString.split(",").count() / numCoordinates;
    qDebug() << countCath << "колво катетеров";
    for(int i =0; i < countCath * numCoordinates; i += numCoordinates)
    {
        x = inString.split(",")[0 + i].toInt();
        y = inString.split(",")[1 + i].toInt();
        qDebug() << y;
    }
    return inString;
}

