#define QT_NO_KEYWORDS
#undef slots
#include "include/NeuronetMaster.h"
#define slots

#define NP_ARR

NeuronetMaster::NeuronetMaster() : QObject(nullptr)
{
    qInfo() << "TF_using";
    if (!Py_IsInitialized())
    {
        Py_Initialize();

        // обьявление модяля(__main__) и словаря для работы с переменными в этом модуле
        pModule = PyImport_AddModule("__main__"); //create main module
        main_dict = PyModule_GetDict(pModule);

        // инициализация TF и графа
        TF_init();
    }
}

NeuronetMaster::~NeuronetMaster()
{
    qInfo() << "~TF_using";
    TF_done();
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

    // возврат ресурсов системе
    Py_XDECREF(pModule); //clear main module

    Py_XDECREF(main_dict);

    Py_XDECREF(imagePy);

    Py_XDECREF(translation);

    Py_XDECREF(representedString);

    Py_XDECREF(outString);

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

	PyRun_SimpleString(
		"MODEL_NAME = 'inference_graph'	\n"\
		"CWD_PATH = 'C:/neuronet/object_detection'	\n"\
		"PATH_TO_CKPT = os.path.join(CWD_PATH, MODEL_NAME, 'frozen_inference_graph.pb')	\n"\
		"PATH_TO_LABELS = os.path.join(CWD_PATH, 'data', 'object-detection.pbtxt')	\n"\
		"PATH_TO_IMAGE_EX = 'C:/neuronet/Example_frame/0.png'	\n"\
		"NUM_CLASSES = 2	\n"\
		"NumbFrame = 0	\n"\

		"label_map = label_map_util.load_labelmap(PATH_TO_LABELS)	\n"\
		"categories = label_map_util.convert_label_map_to_categories(label_map, max_num_classes = NUM_CLASSES, use_display_name = True)	\n"\
		"category_index = label_map_util.create_category_index(categories)	\n"

		"config = tf.compat.v1.ConfigProto()	\n"\

		//"config.gpu_options.allow_growth = True	\n"\

		"config.gpu_options.per_process_gpu_memory_fraction = 0.4	\n"\

		"detection_graph = tf.Graph()	\n"\
		"with detection_graph.as_default() :	\n"\
		"	od_graph_def = tf.compat.v1.GraphDef()	\n"\
		"	with tf.io.gfile.GFile(PATH_TO_CKPT, 'rb') as fid :	\n"\
		"		serialized_graph = fid.read()	\n"\
		"		od_graph_def.ParseFromString(serialized_graph)	\n"\
		"		tf.import_graph_def(od_graph_def, name = '')	\n"\
		"	sess = tf.compat.v1.Session(graph = detection_graph, config = config)	\n"\
		"image_tensor = detection_graph.get_tensor_by_name('image_tensor:0')	\n"\
		"detection_boxes = detection_graph.get_tensor_by_name('detection_boxes:0')	\n"\
		"detection_scores = detection_graph.get_tensor_by_name('detection_scores:0')	\n"\
		"detection_classes = detection_graph.get_tensor_by_name('detection_classes:0')	\n"\
		"num_detections = detection_graph.get_tensor_by_name('num_detections:0')	\n"\
	);
	QByteArray imageBA;

	NeuronetMaster::TF_processing(true, imageBA);

}

QString NeuronetMaster::TF_processing(bool init, QByteArray imageBA)
{

#ifdef NP_ARR
	if (!init)
	{
		// если не инициализация, то раскладываем кадр и отправляем в словарь Python
		// QByteArray bytesImages;
		// QBuffer buffer(&bytesImages);
		// buffer.open(QIODevice::WriteOnly);
		// imageQ.save(&buffer, "png");

		// перевод байтового массива в байтовый обьект, затем в словарь
		imagePy = PyBytes_FromStringAndSize(reinterpret_cast<const char*>(imageBA.data()), static_cast<Py_ssize_t>(imageBA.size()));

		int resultImage = PyDict_SetItemString(main_dict, "imagePy", imagePy);

		PyRun_SimpleString(
			"start_time = datetime.now()	\n"\
			"np_image = np.frombuffer(imagePy, dtype = np.uint8)    \n"\
			"img = cv2.imdecode(np_image, cv2.IMREAD_COLOR) \n"\
			"image = img	\n"\
			"print('TIME FOR READ')	\n"\
			"print(datetime.now() - start_time)	\n"\
		);
	}
#else
	if (!init)
	{
		const auto resSaved = imageQ.save("D:/0.png");
		PyRun_SimpleString(
			"image = cv2.imread('D:/0.png')	\n"\
		);

		PyRun_SimpleString("print('TIME FOR READ')");
		PyRun_SimpleString("print(datetime.now() - start_time)");

	}
#endif
	else
	{
		PyRun_SimpleString(
			"image = cv2.imread(PATH_TO_IMAGE_EX)	\n"\
		);
	}
	PyRun_SimpleString(
		"image = cv2.resize(image, (1024, 1024))	\n"\
		"image_expanded = np.expand_dims(image, axis = 0)	\n"\
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
		"			image = cv2.circle(image, center_coordinates, 15, color, 3)	\n"\
		"			listCoordinates.append(center_coordinates)	\n"\
		"print(datetime.now() - start_time)	\n"\
	);

	//получение обьекта из словаря
	translation = PyDict_GetItemString(main_dict, "listCoordinates");

	points = pointReader(translation);
	finString = parserString(points);

	Shower();

	return finString;
}

void NeuronetMaster::Shower()
{
    PyRun_SimpleString(
                "NumbFrame += 1	\n"\
                "cv2.imshow('GUI', image)	\n"\
                );
}

QString NeuronetMaster::pointReader(PyObject *ItemString)
{
    representedString = PyObject_Repr(ItemString);
    outString = PyUnicode_AsUTF8String(representedString);

    QByteArray bytesPoints = PyBytes_AS_STRING(outString);
    QString out = QString::fromUtf8(bytesPoints);

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
    }
    return inString;
}

inline cv::Mat QImageToCvMat(const QImage &inImage, bool inCloneImageData = true)
{
    switch (inImage.format())
    {
    // 8-bit, 4 channel
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:
    {
        cv::Mat mat(inImage.height(), inImage.width(),
                    CV_8UC4,
                    const_cast<uchar*>(inImage.bits()),
                    static_cast<size_t>(inImage.bytesPerLine())
                    );

        return (inCloneImageData ? mat.clone() : mat);
    }

        // 8-bit, 3 channel
    case QImage::Format_RGB32:
    {
        if (!inCloneImageData)
        {
            qWarning() << "Conversion requires cloning so we don't modify the original QImage data";
        }

        cv::Mat mat(inImage.height(), inImage.width(),
                    CV_8UC4,
                    const_cast<uchar*>(inImage.bits()),
                    static_cast<size_t>(inImage.bytesPerLine())
                    );

        cv::Mat matNoAlpha;

        cv::cvtColor(mat, matNoAlpha, cv::COLOR_BGRA2BGR); // drop the all-white alpha channel

        return matNoAlpha;
    }

        // 8-bit, 3 channel
    case QImage::Format_RGB888:
    {
        if (!inCloneImageData)
        {
            qWarning() << "Conversion requires cloning so we don't modify the original QImage data";
        }

        QImage swapped = inImage.rgbSwapped();

        return cv::Mat(swapped.height(), swapped.width(),
                       CV_8UC3,
                       const_cast<uchar*>(swapped.bits()),
                       static_cast<size_t>(swapped.bytesPerLine())
                       ).clone();
    }

        // 8-bit, 1 channel
    case QImage::Format_Indexed8:
    {
        cv::Mat mat( inImage.height(), inImage.width(),
                     CV_8UC1,
                     const_cast<uchar*>(inImage.bits()),
                     static_cast<size_t>(inImage.bytesPerLine())
                     );

        return (inCloneImageData ? mat.clone() : mat);
    }
    default:
        qWarning() << "QImage format not handled in switch:" << inImage.format();
        break;
    }

    return cv::Mat();
}

