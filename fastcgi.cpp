#include <fastcgi2/component.h>
#include <fastcgi2/component_factory.h>
#include <fastcgi2/handler.h>
#include <fastcgi2/request.h>
#include <fastcgi2/data_buffer.h>
#include "fastcgi2/stream.h"

#include <iostream>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <sstream>

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "db.cpp"

class CollectionComponent : virtual public fastcgi::Component, virtual public fastcgi::Handler {

public:
        CollectionComponent(fastcgi::ComponentContext *context) : fastcgi::Component(context) {
        }

        virtual void onLoad() {
            DB::getInstance();
        }

        virtual void onUnload() {
        }

        virtual void handleRequest(fastcgi::Request *request, fastcgi::HandlerContext *context) {
		    if (request->getRequestMethod() == "POST") {
                fastcgi::DataBuffer buf = request->requestBody();
                std::string name;
                buf.toString(name);
                DB::getInstance().addCollection(name);
		    } else {
                std::stringbuf buf(DB::getInstance().getCollections().c_str());
                request->write(&buf);
		    }
        }
};


class ImageComponent : virtual public fastcgi::Component, virtual public fastcgi::Handler {

public:
    ImageComponent(fastcgi::ComponentContext *context) : fastcgi::Component(context) {}
    virtual void onLoad() {
        DB::getInstance();
    }

    virtual void onUnload() {}

    virtual void handleRequest(fastcgi::Request* request, fastcgi::HandlerContext* context) {

        if (request->getRequestMethod() == "POST") {
            fastcgi::DataBuffer buf = request->requestBody();
            std::string image;
            buf.toString(image);
        } else {
            std::string uri(request->getURI());
            size_t len = uri.size();
            size_t last = uri.rfind('/');
            if (len == last+1) {
                last = uri.rfind('/', len-2);
                uri = uri.substr(last+1, len-last-2);
            } else {
                uri = uri.substr(last+1);
            }
            std::stringbuf buf(DB::getInstance().getImages(uri).c_str());
            request->write(&buf);
        }
    }
};

FCGIDAEMON_REGISTER_FACTORIES_BEGIN()
FCGIDAEMON_ADD_DEFAULT_FACTORY("CollectionFactory", CollectionComponent)
FCGIDAEMON_ADD_DEFAULT_FACTORY("ImageFactory", ImageComponent)
FCGIDAEMON_REGISTER_FACTORIES_END()
