#include "StorageOperations.h"
#include "exceptions.h"
#include <iostream>
#include <unordered_map>
#include <map>
#include <memory>

#include <QListWidget>


StorageManager::StorageManager() {}

void StorageManager::addMapItem(const std::shared_ptr<StoredItem>& item) {//add to both maps
    if (itemById.find(item->getId()) != itemById.end()) { //item smart pointer to getid
        throw DuplicateItemException("Item already exists. " + item->getId());
    }
    else {
        itemById[item->getId()] = item; //pass item to itembyid...
        itemByDescription[item->getDescription()] = item; //pass item to itembydesc...
    }
}

void StorageManager::removeItem(const std::string& id) {
    //find id, get the member
    auto it = itemById.find(id);
    std::string desc = it->second->getDescription();

    if (it == itemById.end()) { //if find id reaches the end of it's container, throw excep
        throw ItemNotFoundException("Item does not exist: " + id);
    }
    else {
        itemById.erase(it);
        itemByDescription.erase(desc);
    }
}

std::shared_ptr<StoredItem> StorageManager::findById(const std::string& id) const {
    //if the find function does NOT reach the end of the container then return the item it found
    if (itemById.find(id) != itemById.end()) {
        return itemById.find(id)->second;
    }
    else {
        //throw ItemNotFoundException("Item not found: " + id);
        return NULL;
    }

}

void StorageManager::listItemsByDescription(QListWidget *List) const {
    for (const auto& pair : itemByDescription) {
        List->update();
        List->addItem("ID: " + pair.second->returnQid()
                      + ", " + "Description: " + pair.second->returnQdesc()
                      + ", " + "Location: " + pair.second->returnQloc());
        List->show();
    }

}
