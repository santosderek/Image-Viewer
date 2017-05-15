// Created By Derek Santos
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Setting the title
    this->setWindowTitle("Image Viewer");
    // Initalizing the root folder for the fileSystem
    absoluteRootPath = "Path: ";
    absoluteRootPath += QDir::rootPath();

    // File System Initalization
    fileSystem = new QFileSystemModel;
    fileSystem->setRootPath(QDir::rootPath());
    fileSystem->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    ui->FolderManager->setModel(fileSystem);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete fileSystem;
    vectorOfImages.clear();
    vectorOfItems.clear();

}

void MainWindow::change_Root_Folder(const QString passedPath)
{
    try{
        fileSystem->setRootPath(passedPath);


    }
    catch(...)
    {

    }
}

void MainWindow::on_QuitButton_clicked()
{
    this->close();
}

void MainWindow::update_icon_viewer()
{

    // Icon Viewer Inital Settings
    // This clears the table
    ui->FileIconViewer->setRowCount(0);
    ui->FileIconViewer->setColumnCount(1);

    this->vectorOfItems.clear();

    // This sets the table's rows to the amount of images there are
    ui->FileIconViewer->setRowCount(vectorOfImages.size());
    ui->FileIconViewer->setShowGrid(false);

    // Values to scale the image
    int width = 500;
    int height = 500;

    // Counter to count down the rows
    int count = 0;

    // Iterating through the images
    for (auto& image : vectorOfImages)
    {
        // Each image will be encased by a TableWigetItem
        QTableWidgetItem* tItem = new QTableWidgetItem;

        // This loads the image within memory to be used by QT
        auto pixel_map = QPixmap::fromImage(image).scaled(width, height , Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // Setting data
        tItem->setData(Qt::DecorationRole, pixel_map);

        // Append to a vector of TableWidgetItems
        vectorOfItems.append(*tItem);

        // Binds the item to the IconViewer
        ui->FileIconViewer->setItem(count++,0,tItem);


    }

    //Resize to fit

    ui->FileIconViewer->resizeColumnsToContents();
    ui->FileIconViewer->resizeRowsToContents();
}

void MainWindow::on_FolderManager_doubleClicked(const QModelIndex &index)
{
    // Index holds information of the folder that was just clicked
    absoluteRootPath = fileSystem->fileInfo(index).absoluteFilePath();
    ui->DirectoryLabel->setText("Path: " + absoluteRootPath);

    // Directory Iterator
    QDirIterator directory_iterator(absoluteRootPath, QDir::Files);

    vectorOfImages.clear();
    while(directory_iterator.hasNext())
    {
        try
        {
           // Loading Image to QTImage
           QImage* image = new QImage();
           bool loaded = image->load(directory_iterator.next());

           if (loaded)
           {
               // If loaded then set to const image to put into vector
               const QImage* cImage = new QImage(*image);
               vectorOfImages.append(*cImage);


           }
           // Delete the unused image
           delete image;
        }
        catch(...)
        {
            // Will just move onto next file
        }
    }

    // Updating Image Viewer

    update_icon_viewer();



}

void MainWindow::on_SettingsButton_clicked()
{
    // Opens a popup that will ask for a new working directory
    bool self_check;
    auto text = QInputDialog::getText(this, tr("Settings"), tr("Change Path:"), QLineEdit::Normal, QDir::home().dirName(), &self_check);

    if (self_check && !text.isEmpty())
    {
        this->change_Root_Folder(text);
        absoluteRootPath = text;
    }


}
