#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "VideoSurface.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QImageReader>

#include <QCameraInfo>
//#include <QCamera>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
  foreach (const QCameraInfo &cameraInfo, cameras)
  {
    if (!cameraInfo.isNull())
    {

      std::cout << "Camera: \"" << cameraInfo.deviceName().toStdString()
                << "\" description: \"" << cameraInfo.description().toStdString()
                << "\" position: " << (cameraInfo.position() == QCamera::UnspecifiedPosition ? "Unspecified" : (cameraInfo.position() == QCamera::FrontFace ? "Front facing" : "Back facing"))
                << " orientation: " << cameraInfo.orientation() << std::endl;

      QCamera *camera = new QCamera(cameraInfo);

      QCameraViewfinderSettings viewfinderSettings;
      viewfinderSettings.setMinimumFrameRate(10.0);
      viewfinderSettings.setMaximumFrameRate(30.0);
      camera->setViewfinderSettings(viewfinderSettings);

      VideoSurface *videoSurface = new VideoSurface;
      videoSurface->setMainWindow(this);
      camera->setViewfinder(videoSurface);

      camera->start();
    }
  }
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::showAboutDialog()
{
  QMessageBox::information(this, "About", "By Martijn Koopman.\n\nSource code available under GNU General Public License 3.0");
}

void MainWindow::showOpenFileDialog()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", "Image Files (*.png *.jpg *.gif *.bmp)");

  // Open file
  QFile file(fileName);
  file.open(QIODevice::ReadOnly);

  // Return on Cancel
  if (!file.exists())
    return;

  openFile(fileName);
}

void MainWindow::setStatusMessage(const QString &str)
{
  ui->statusbar->showMessage(str);
}

void MainWindow::setImageSize(const QSize &size)
{
  ui->label->resize(size);
  adjustSize();
}

void MainWindow::setImage(const QImage &image)
{
  ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::openFile(const QString &fileName)
{
  QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return;
    }
    ui->label->setPixmap(QPixmap::fromImage(newImage));
    ui->label->resize(ui->label->pixmap()->size());
    adjustSize();
}
