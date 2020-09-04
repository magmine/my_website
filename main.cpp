#include "crow_all.h"

void sendFile(crow::response& res, std::string filename, std::string contentType) {
    std::ifstream in("../Public/" + filename, std::ifstream::in);
    if (in) {
        std::ostringstream contents;
        contents << in.rdbuf();
        in.close();
        res.set_header("Content-Type", contentType);
        res.write(contents.str());
    } else {
        res.code = 404;
        res.write("Not found!");
    }
    res.end();
}

void sendHtml(crow::response& res, std::string filename) {
    sendFile(res, filename + ".html", "text/html");
}

void sendImage(crow::response& res, std::string filename) {
    sendFile(res, "images/" + filename, "image/*");
}

void sendScript(crow::response& res, std::string filename) {
    sendFile(res, "scripts/" + filename + ".js", "text/javascript");
}

void sendStyle(crow::response& res, std::string filename) {
    sendFile(res, "styles/" + filename + ".png", "text/css");
}

int main(int argc, char **argv)
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/") 
    ([](const crow::request& req, crow::response& res) {
        sendHtml(res, "index");
    });
    
    CROW_ROUTE(app, "/<string>") 
    ([](const crow::request& req, crow::response& res, std::string filename) {
        std::cerr<<"Html: " << filename<<"\n";
        if (filename.size())
            sendHtml(res, filename);
        else
            sendHtml(res, "index");
    });

    CROW_ROUTE(app, "/images/<string>") 
    ([](const crow::request& req, crow::response& res, std::string filename) {
        sendImage(res, filename);
    });

    char *port = NULL;
    port = getenv("PORT");
    uint16_t i_port = static_cast<uint16_t>(port != NULL ? std::stoi(port) : 18080 );
    std::cout<<"Running on port: "<<i_port<<"\n";
    app.port(i_port).multithreaded().run();
}