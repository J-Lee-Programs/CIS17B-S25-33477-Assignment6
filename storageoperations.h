#ifndef STORAGEOPERATIONS_H
#define STORAGEOPERATIONS_H
#include <iostream>
#include <unordered_map>
#include <map>
#include <memory>
#include <QListWidget>

class StoredItem {
private:
    std::string id;
    std::string description;
    std::string location;

    QString Qid = QString::fromStdString(id);
    QString Qdesc = QString::fromStdString(description);
    QString Qloc = QString::fromStdString(location);
public:
    StoredItem(std::string id, std::string desc, std::string loc)//constructor
        : id(id), description(desc), location(loc) {
    }

    std::string getId() const { return id; }
    std::string getDescription() const { return description; }
    std::string getLocation() const { return location; }
    QString returnQid() { return Qid; }
    QString returnQdesc() const { return Qdesc; }
    QString returnQloc() const { return Qloc; }
};


class StorageManager
{
private:
    std::unordered_map<std::string, std::shared_ptr<StoredItem>> itemById;
    std::map<std::string, std::shared_ptr<StoredItem>> itemByDescription;
public:
    StorageManager();
    void addMapItem(const std::shared_ptr<StoredItem>& item);
    void removeItem(const std::string& id);
    std::shared_ptr<StoredItem> findById(const std::string& id) const;
    void listItemsByDescription(QListWidget *list) const;

};

#endif // STORAGEOPERATIONS_H
