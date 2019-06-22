#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  /// Show the 'About this application' dialog
  void showAboutDialog();

  /// Show the 'Open file...' dialog
  void showOpenFileDialog();

  void setStatusMessage(const QString &str);

  void setImageSize(const QSize &size);

  void setImage(const QImage &img);

protected:
  /// Open a file
  ///
  /// \param[in] fileName The name of the file including the path
  void openFile(const QString &fileName);

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
