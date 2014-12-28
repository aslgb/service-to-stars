#include <cstdlib>
#include <iostream>
#include "mongo/client/dbclient.h"

#include <string>

void initDB() {
    mongo::client::initialize();
}

void addCollection(std::string json) {
    mongo::ScopedDbConnection conn("localhost");
    conn->insert("stars.collections", mongo::fromjson(json));
    conn.done();
}

std::string getCollections() {
    mongo::ScopedDbConnection conn("localhost");
    std::auto_ptr<mongo::DBClientCursor> cursor = conn->query("stars.collections", mongo::BSONObj());
    conn.done();
    mongo::BSONArrayBuilder collBuilder;
    while (cursor->more()) {
        collBuilder << cursor->next().getField("name").wrap();
    }
    return collBuilder.arr().toString(true, true);
}

void addImage(std::string json, std::string collName) {
    mongo::ScopedDbConnection conn("localhost");
    conn->insert("stars." + collName, mongo::fromjson(json));
    conn.done();
}

std::string getImages(std::string collName) {
    mongo::ScopedDbConnection conn("localhost");
    std::auto_ptr<mongo::DBClientCursor> cursor = conn->query("stars." + collName, mongo::BSONObj());
    conn.done();
    mongo::BSONArrayBuilder imgBuilder;
    while (cursor->more()) {
        imgBuilder << cursor->next().getField("contour").wrap();
    }
    return imgBuilder.arr().toString(true, true);
}
