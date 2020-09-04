#pragma once
#include "crow_all.h"

class Router {
public:
	static void sendHtml(crow::response& res, std::string filename) {
		sendFile(res, filename + ".html", "text/html");
	}

	static void sendImage(crow::response& res, std::string filename) {
		sendFile(res, "images/" + filename, "image/*");
	}

	static void sendScript(crow::response& res, std::string filename) {
		sendFile(res, "scripts/" + filename + ".js", "text/javascript");
	}

	static void sendStyle(crow::response& res, std::string filename) {
		sendFile(res, "styles/" + filename + ".png", "text/css");
	}

private:
	Router() = default;
	static void sendFile(crow::response& res, std::string filename, std::string contentType) {
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
};