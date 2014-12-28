#include <string>

void initDB();

void addCollection(std::string name);
std::string getCollections();

void addImage(std::string contour, std::string collName);
std::string getImages(std::string collName);
