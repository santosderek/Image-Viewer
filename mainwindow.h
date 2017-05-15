// Created By Derek Santos
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include "qimage.h"
#include <QTableWidgetItem>
#include <QLineEdit>
#include <QInputDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_QuitButton_clicked();
    void on_FolderManager_doubleClicked(const QModelIndex &index);
    void on_SettingsButton_clicked();

private:
    // Pointers
    Ui::MainWindow *ui;
    QFileSystemModel *fileSystem;

    QVector<QImage> vectorOfImages;
    QVector<QTableWidgetItem> vectorOfItems;

    QString absoluteRootPath;

    void change_Root_Folder(const QString passedPath);
    void update_icon_viewer();

};

#endif // MAINWINDOW_H
