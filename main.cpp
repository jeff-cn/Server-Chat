#include <QCoreApplication>
#include "serverchat.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ServerChat server(3000);
    return a.exec();
}
