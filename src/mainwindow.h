#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datamodel.h"
#include "tabledatamodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void createMenus();
    void setUpTable();
    ~MainWindow();

public slots:
    void addRow();
    void deleteRow();
    void saveAsHtml();

private:
    Ui::MainWindow *ui;
    TableDataModel *td;
    DataModel *dataModel;
};

#endif // MAINWINDOW_H
