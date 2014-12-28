#include <cstdlib>
#include <iostream>
#include "mongo/client/dbclient.h"

#include <string>

void initDB() {
    mongo::client::initialize();
}

void addCollection(std::string name) {
    mongo::DBClientConnection conn;
    conn.connect("localhost");
    mongo::BSONObj obj = mongo::BSONObjBuilder().append("name", name.c_str()).obj();
    conn.insert("stars.collections", obj);
}

std::string getCollections() {
    mongo::DBClientConnection conn;
    conn.connect("localhost");
    std::string collections;
    std::auto_ptr<mongo::DBClientCursor> cursor = conn.query("stars.collections");
    while (cursor->more()) {
        collections.append(cursor->next().getField("name").toString());
    }
    return collections;
}

void addImage(std::string contour, std::string collName) {
    mongo::DBClientConnection conn;
    conn.connect("localhost");
    mongo::BSONObj obj = mongo::BSONObjBuilder().append("contour", contour.c_str()).obj();
    conn.insert("stars." + collName, obj);
}

std::string getImages(std::string collName) {
    mongo::DBClientConnection conn;
    conn.connect("localhost");
    std::string images;
    std::auto_ptr<mongo::DBClientCursor> cursor = conn.query("stars." + collName);
    while (cursor->more()) {
        images.append(cursor->next().getField("contour").toString());
    }
    return images;
}
