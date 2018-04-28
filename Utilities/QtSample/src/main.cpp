#include <QApplication>
#include <QGuiApplication>
#include <qquickview.h>
#include <qqmlcontext.h>
#include <qabstracteventdispatcher.h>
#include <qtimer.h>
#include "sampleModel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
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

    QTimer timer;
    timer.setInterval(10);
    QObject::connect(&timer, &QTimer::timeout, [&model]() { model.tick(); });
    timer.start();

    return app.exec();
}
