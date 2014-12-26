#include <boost/functional/hash.hpp>

#include "rapidjson/writer.h"
#include "rapidjson/reader.h"
#include "rapidjson/stringbuffer.h"

#include <fstream>
#include <iostream>

#include <string>
#include <unordered_set>
#include <unordered_map>

#include <memory>

typedef std::vector<std::string> img_list;
typedef std::unordered_map<std::string, img_list> img_dict;
typedef std::unordered_set<std::string> coll_set;
typedef coll_set::iterator coll_iter;

class DB {
public:
    static DB& getInstance() {
        static DB instance;
        return instance;
    }

    std::string getCollections() {
        rapidjson::StringBuffer buf;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
        writer.StartArray();
        for (const auto &elem: *collections.get()) {
            writer.StartObject();
            writer.String("name");
            writer.String(elem.c_str());
            writer.EndObject();
         }
         writer.EndArray();
         return buf.GetString();
    }

    void addCollection(const std::string& json) {
    }

    std::string getImages(std::string collName) {
        rapidjson::StringBuffer buf;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
        writer.StartArray();
        for (const auto &img: images.get()->find(collName)->second) {
            writer.StartObject();
            writer.String("contour");
            writer.String(img.c_str());
            writer.EndObject();
        }
        writer.EndArray();
        return buf.GetString();
    }

    void addImage(std::string image) {
    }

private:
    std::unique_ptr<coll_set> collections;
    std::unique_ptr<img_dict> images;

    void loadCollections() {
        std::ifstream ifstream("/home/aslgb/mag/web/ex/collection");
        std::string name;
        while (ifstream >> name) {
            collections.get()->insert(name);
        }
        ifstream.close();
    }

    void loadImages() {
        std::ifstream ifstream("/home/aslgb/mag/web/ex/images");
        std::string name;
        int size;
        std::string img;
        while (ifstream >> name >> size) {
            img_list imgs = img_list();
            for (int i = 0; i < size; ++i) {
                ifstream >> img;
                imgs.push_back(img);
            }
            images.get()->insert(std::pair<std::string, img_list>(name, imgs));
        }
    }

    DB() : collections(new coll_set()), images(new img_dict()) {
        loadCollections();
        loadImages();
    };

    DB(const DB& other);

    DB& operator=(const DB&);
};

