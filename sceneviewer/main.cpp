#include <QApplication>

#include <iostream>

#include <spatium/Image.h>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
  spatium::Image<unsigned char, 3> rgbImage(640,480);

  QApplication app(argc, argv);
  QCoreApplication::setOrganizationName("Martijn Koopman");
  QCoreApplication::setApplicationName("SceneViewer");
  QCoreApplication::setApplicationVersion("0.1.0");

  MainWindow mainWin;
  mainWin.show();

  return app.exec();
}
