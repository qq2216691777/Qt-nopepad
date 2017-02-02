#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Untitled");
    QObject::connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(newFileSlot()));
    QObject::connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(openFileSlot()));
    QObject::connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(saveFileSlot()));
    QObject::connect(ui->actionSave_as,SIGNAL(triggered()),this,SLOT(saveAsFileSlot()));
    QObject::connect(ui->actionQuit_Q,SIGNAL(triggered()),this,SLOT(close()));

    QObject::connect(ui->undoaction,SIGNAL(triggered()),ui->textEdit,SLOT(undo()));
    QObject::connect(ui->redoaction,SIGNAL(triggered()),ui->textEdit,SLOT(redo()));
    QObject::connect(ui->copyaction,SIGNAL(triggered()),ui->textEdit,SLOT(copy()));
    QObject::connect(ui->pasteaction,SIGNAL(triggered()),ui->textEdit,SLOT(paste()));
    QObject::connect(ui->selectAllaction,SIGNAL(triggered()),ui->textEdit,SLOT(selectAll()));
    QObject::connect(ui->cutaction,SIGNAL(triggered()),ui->textEdit,SLOT(cut()));

    QObject::connect(ui->fontaction,SIGNAL(triggered()),this,SLOT(setFontSlot()));
    QObject::connect(ui->coloraction,SIGNAL(triggered()),this,SLOT(setColorSlot()));
    QObject::connect(ui->dateaction,SIGNAL(triggered()),this,SLOT(currentDateTimeSlot()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newFileSlot()
{
    if( ui->textEdit->document()->isModified())
    {
        qDebug()<<"current file modified";
    }
    else
    {
        //qDebug()<<"not modified";
        ui->textEdit->clear();
        this->setWindowTitle("Untitled.txt");
    }

    saveFileName.clear();
}

void MainWindow::openFileSlot()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath());
    qDebug()<<"file name is"<<fileName<<endl;
    if( fileName.isEmpty())
    {
        QMessageBox::information(this,"Error Message","please select a text file");
        return ;
    }

    QFile *file = new QFile;
    file->setFileName(fileName);
    bool ok=file->open(QIODevice::ReadOnly);
    if( ok )
    {
        this->saveFileName = fileName;
        QTextStream in(file);
        ui->textEdit->setText(in.readAll());
        file->close();
        delete file;
    }
    else
    {
        QMessageBox::information(this,"Error Message","File Open Error" +file->errorString());
        return ;
    }
}

void MainWindow::saveFileSlot()
{
    if(this->saveFileName.isEmpty())
    {
        this->saveAsFileSlot();
        return ;
    }

    QFile *file=new QFile;
    file->setFileName(saveFileName);
    bool ok=file->open(QIODevice::WriteOnly);
    if(ok)
    {
        QTextStream out(file);
        out<<ui->textEdit->toPlainText();
        file->close();
        delete file;
    }
    else
    {
        QMessageBox::information(this,"Error Message","File Save Error" +file->errorString());
        return ;
    }
}

void MainWindow::saveAsFileSlot()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save File",QDir::currentPath());
    if( fileName.isEmpty())
    {
        QMessageBox::information(this, "Error Message","Please select a file");
        return ;
    }
    QFile *file=new QFile;
    file->setFileName(fileName);
    bool ok=file->open(QIODevice::WriteOnly);
    if(ok)
    {
        QTextStream out(file);
        out<<ui->textEdit->toPlainText();
        file->close();
        delete file;
    }
    else
    {
        QMessageBox::information(this,"Error Message","File Save Error" +file->errorString());
        return ;
    }
}

void MainWindow::setFontSlot()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if(ok)
    {
        ui->textEdit->setFont(font);
    }
    else
    {
        QMessageBox::information(this,"Error Message","select font Error!");
    }
}

void MainWindow::setColorSlot()
{
    QColor color = QColorDialog::getColor(Qt::red,this);
    if(color.isValid())
    {
        ui->textEdit->setTextColor(color);
    }
    else
    {
        QMessageBox::information(this,"Error Message","select color Error!");
    }
}


void MainWindow::currentDateTimeSlot()
{
    QDateTime current=QDateTime::currentDateTime();
    QString time=current.toString("yyyy-M-dd hh:mm:ss");
    ui->textEdit->append(time);
}
