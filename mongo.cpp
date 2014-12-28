#include <cstdlib>
#include <iostream>
#include "mongo/client/dbclient.h"

#include <string>

void initDB() {
    mongo::client::initialize();
}

void addCollection(std::string json) {
    mongo::DBClientConnection conn;
    conn.connect("localhost");
    conn.insert("stars.collections", mongo::fromjson(json));
}

std::string getCollections() {
    mongo::DBClientConnection conn;
    conn.connect("localhost");
    mongo::BSONArrayBuilder collBuilder;
    std::auto_ptr<mongo::DBClientCursor> cursor = conn.query("stars.collections");
    while (cursor->more()) {
        collBuilder << cursor->next().getField("name").wrap();
    }
    return mongo::tojson(collBuilder.arr());
}

void addImage(std::string json, std::string collName) {
    mongo::DBClientConnection conn;
    conn.connect("localhost");
    conn.insert("stars." + collName, mongo::fromjson(json));
}

std::string getImages(std::string collName) {
    mongo::DBClientConnection conn;
    conn.connect("localhost");
    mongo::BSONArrayBuilder imgBuilder;
    std::auto_ptr<mongo::DBClientCursor> cursor = conn.query("stars." + collName);
    while (cursor->more()) {
        imgBuilder << cursor->next().getField("contour").wrap();
    }
    return mongo::tojson(imgBuilder.arr());
}
