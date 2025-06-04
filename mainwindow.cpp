#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "StorageOperations.h"

#include <QApplication>
#include <QListWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>

//front end stuff

MainWindow::MainWindow(QWidget *parent)//constructor
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
     ui->setupUi(this);

    StorageManager listAllItems;
    findIdInput = new QLineEdit;
    findIdInput->setPlaceholderText("Find an item via ID.");
    removeIdInput = new QLineEdit;
    removeIdInput->setPlaceholderText("Remove an item via ID.");

    QListWidget *itemList = new QListWidget;
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    //buttons
    QPushButton *addButton = new QPushButton("Add Item...", this);
    QPushButton *removeButton = new QPushButton("Remove Item", this);
    QPushButton *findButton = new QPushButton("Find Item", this);
    QPushButton *helpButton = new QPushButton("About", this);
    QPushButton *updateButton = new QPushButton("Update List", this);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(new QLabel("Inventory Manager"));

    //layout interactions
    layout->addWidget(findButton);
    layout->addWidget(findIdInput);
    connect(findIdInput, &QLineEdit::returnPressed, findButton, &QPushButton::click);
    connect(findButton, &QPushButton::clicked, [=](){
       onFindItemClicked(listAllItems);
    });

    layout->addWidget(removeButton);
    layout->addWidget(removeIdInput);
    connect(removeIdInput, &QLineEdit::returnPressed, removeButton, &QPushButton::click);
    connect(removeButton, &QPushButton::clicked, [=](){
       onRemoveItemClicked(listAllItems);
    });

    layout->addWidget(addButton);
    connect(addButton, &QPushButton::clicked, [=](){
        onAddItemClicked(listAllItems);
    });

    layout->addWidget(itemList);
    itemList->clear();

    layout->addWidget(updateButton);
    QObject::connect(updateButton, &QPushButton::clicked, [=]() mutable {
        listAllItems.listItemsByDescription(itemList);
    });

    layout->addWidget(helpButton);
    QObject::connect(helpButton, &QPushButton::clicked, [=]() mutable {
        QMessageBox msgBox;
        msgBox.setText("This application is a demonstration of QTCreator using maps.");
        msgBox.exec();
    });

}


MainWindow::~MainWindow()
{
    delete ui;
}

//buttonfunctions
void MainWindow::onAddItemClicked(StorageManager addSearch){
    QWidget *window = new QWidget;
    QVBoxLayout *addItemLayout = new QVBoxLayout;

    QPushButton *finishAdd = new QPushButton("Insert item", this);
    idInput = new QLineEdit;
    descInput = new QLineEdit;
    locInput = new QLineEdit;

    addItemLayout->addWidget(new QLabel("Item ID"));
    addItemLayout->addWidget(idInput);
    idInput->setPlaceholderText("Input the ID for the item");
    addItemLayout->addWidget(new QLabel("Item Description"));
    addItemLayout->addWidget(descInput);
    descInput->setPlaceholderText("Input the description for the item.");
    addItemLayout->addWidget(new QLabel("Item Location"));
    addItemLayout->addWidget(locInput);
    locInput->setPlaceholderText("Input the location for the item.");
    addItemLayout->addWidget(finishAdd);
    connect(idInput, &QLineEdit::returnPressed, finishAdd, &QPushButton::click);
    QObject::connect(finishAdd, &QPushButton::clicked, [=]() mutable {
        QString addIdInput = idInput->text();
        QString addDescInput = descInput->text();
        QString addLocInput = locInput->text();
        if (!addIdInput.isEmpty() && !addDescInput.isEmpty() && !addLocInput.isEmpty()) {
            std::string conv1 = addIdInput.toStdString();
            std::string conv2 = addDescInput.toStdString();
            std::string conv3 = addLocInput.toStdString();
            auto item = std::make_shared<StoredItem>(conv1, conv2, conv3);
            addSearch.addMapItem(item);
            std::cout << conv1 << conv2 << conv3;
        } else {
            QLabel *errLabel = new QLabel;
            errLabel->setText("Nothing to insert.");
            addItemLayout->addWidget(errLabel);
        }
    });
    window->setLayout(addItemLayout);
    window->show();
}


void MainWindow::onFindItemClicked(StorageManager findItem){//this shows the item clicked
    std::cout << "Working1.";
    QString findId = findIdInput->text();
    std::string findConversion = findId.toStdString();
    auto findSearch = findItem.findById(findConversion);
}
void MainWindow::onRemoveItemClicked(StorageManager removeSearch){//this removes the item
    std::cout << "Working2.";
    QString removeInput = removeIdInput->text();
    std::string removeConversion = removeInput.toStdString();

    removeSearch.removeItem(removeConversion);
}




