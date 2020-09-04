#include "Router.hpp"
#include "crow_all.h"

int main(int argc, char** argv) {
	crow::SimpleApp app;

	CROW_ROUTE(app, "/")
	([](const crow::request& req, crow::response& res) { Router::sendHtml(res, "index"); });

	CROW_ROUTE(app, "/<string>")
	([](const crow::request& req, crow::response& res, std::string filename) {
		std::cerr << "Html: " << filename << "\n";
		if (filename.size())
			Router::sendHtml(res, filename);
		else
			Router::sendHtml(res, "index");
	});

	CROW_ROUTE(app, "/images/<string>")
	([](const crow::request& req, crow::response& res, std::string filename) {
		Router::sendImage(res, filename);
	});

	char* port = NULL;
	port = getenv("PORT");
	uint16_t i_port = static_cast<uint16_t>(port != NULL ? std::stoi(port) : 18080);
	std::cout << "Running on port: " << i_port << "\n";
	app.port(i_port).multithreaded().run();
}