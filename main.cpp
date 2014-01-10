#include "mainwindow.h"
#include <QApplication>
#include "QLogger.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(Appons);
    QLogger::QLoggerManager *manager = QLogger::QLoggerManager::getInstance();

    QApplication app(argc, argv);
    app.addLibraryPath("./plugins");
    app.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);

    MainWindow window;

    //window.showFullScreen();
    window.show();

    manager->addDestination("Appons-test.log", "Appons", QLogger::TraceLevel);
    QLogger::QLog_Trace("Appons", "App start");
    return app.exec();
}
