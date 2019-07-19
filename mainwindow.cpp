#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tabledatamodel.h"
#include "datamodel.h"
#include "combobox.h"
#include "htmlconverter.h"
#include <QStyledItemDelegate>
#include <QComboBox>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    dataModel = new DataModel();
    dataModel->InitModel();
    ui->setupUi(this);
    this->setFixedSize(600,400);
    setUpTable();
    createMenus();
}

void MainWindow::setUpTable(){
    td = new TableDataModel((QList<TableAttributable*> &) dataModel->getCompanyList(), this);
    ComboBoxItemDelegate* cbid = new ComboBoxItemDelegate(ui->tableView, dataModel, td);
    td->setDelegateForNestedAttributes(ui->tableView, cbid);
    ui->tableView->setModel(td);
    for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c)
    {
        ui->tableView->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }
    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dataModel;
}



void MainWindow::createNewCountry(){
    td->insertRows<Company>(0,1,QModelIndex());
}

void MainWindow::deletedSelected(){
    int row = ui->tableView->selectionModel()->currentIndex().row();
    td->removeRows(row,1,QModelIndex());
}

void MainWindow::saveAsHtml(){
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save table data"), "",
            tr("Html page (*.html);;All Files (*)"));
    if (fileName.isEmpty())
           return;
       else {
           QFile file(fileName);
           if (!file.open(QIODevice::WriteOnly)) {
               QMessageBox::information(this, tr("Unable to open file"),
                   file.errorString());
               return;
           }
           QTextStream out(&file);
           out << HtmlConverter().convertToHtml(td->getData());
           out.flush();
           file.close();
           QMessageBox::information(this, tr("Status"), "Successfully saved");
    }

}

void MainWindow::createMenus(){
    QMenu *fileMenu = menuBar()->addMenu(tr("&Edit"));
    QAction *openAct = new QAction(tr("&Add new company"), this);
    fileMenu->addAction(openAct);
    connect(openAct, &QAction::triggered, this, &MainWindow::createNewCountry);
    QAction *deleteAct = new QAction(tr("&Delete selected row"), this);
    fileMenu->addAction(deleteAct);
    connect(deleteAct, &QAction::triggered, this, &MainWindow::deletedSelected);
    QAction *convertAct = new QAction(tr("&Save as html"), this);
    fileMenu->addAction(convertAct);
    connect(convertAct, &QAction::triggered, this, &MainWindow::saveAsHtml);
}
