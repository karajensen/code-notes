#include <QGuiApplication>
#include <qquickview.h>
#include <qqmlcontext.h>
#include <qabstracteventdispatcher.h>
#include <qtimer.h>
#include "sampleModel.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);

    SampleModel::qmlRegisterTypes();
    SampleModel model;
    const int startItemAmount = 9;
    for (int i = 0; i < startItemAmount; ++i)
    {
        model.createItem(("Sample Item " + std::to_string(i)).c_str());
    }

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setTitle("Qt Sample");
    QQmlContext* ctxt = view.rootContext();
    ctxt->setContextProperty("context_model", &model);
    view.setSource(QUrl("qrc:/main.qml"));
    view.show();

    QQuickView palette;
    palette.setResizeMode(QQuickView::SizeRootObjectToView);
    palette.setTitle("Qt Palette");
    palette.setSource(QUrl("qrc:/palette.qml"));
    palette.show();

    QQuickView picker;
    picker.setResizeMode(QQuickView::SizeRootObjectToView);
    picker.setTitle("Qt Picker");
    picker.setSource(QUrl("qrc:/picker.qml"));
    picker.show();

    QTimer timer;
    timer.setInterval(10);
    QObject::connect(&timer, &QTimer::timeout, [&model]() { model.tick(); });
    timer.start();

    auto connection = std::make_shared<QMetaObject::Connection>();
    *connection = QObject::connect(&timer, &QTimer::timeout, [connection]()
    {
        std::cout << "Testing Auto Disconnect" << std::endl;
        QObject::disconnect(*connection);
    });

    return app.exec();
}
