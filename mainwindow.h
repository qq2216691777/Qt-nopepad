#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include <QFile>
#include <QFileDialog>
#include <QDir>

#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>
#include <QDate>

#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString saveFileName;
private slots:
    void newFileSlot();
    void openFileSlot();
    void saveFileSlot();
    void saveAsFileSlot();
    void setFontSlot();
    void setColorSlot();
    void currentDateTimeSlot();
};

#endif // MAINWINDOW_H
