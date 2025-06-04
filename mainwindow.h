#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QWidget>
#include <QListWidget>
#include <QBoxLayout>
#include "StorageOperations.h"
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// MainWindow.h
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //manage interactions, all in working order
    void onAddItemClicked(StorageManager addItemstothis);
    void onFindItemClicked(StorageManager findItemsforthis);
    void onRemoveItemClicked(StorageManager removeitemsforthis);



private:
    QLineEdit *idInput, *descInput, *locInput;
    QLineEdit *findIdInput, *removeIdInput;
    QListWidget *itemList;
    Ui::MainWindow *ui; //system provided
    StorageManager manager;
};
#endif // MAINWINDOW_H
