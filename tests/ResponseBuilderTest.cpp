#include "doctest.h"

#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <sys/stat.h>
#include <cstring>
#include <dirent.h>
#include <iostream>
#include <string>
#include <unistd.h>

#include "ResponseBuilder.hpp"
#include "Response.hpp"
#include "HttpStatus.hpp"
#include "ServerConfig.hpp"
#include "test_utils.hpp"

static void createTestDir(const std::string& dir) {
    mkdir(dir.c_str(), 0755);
    writeFile("<!DOCTYPE html><html><head><title>Example</title></head><body><p>This is an example of a simple HTML page with one paragraph.</p></body></html>", (dir + "/index.html").c_str());
    // writeFile("errorpage.html", (dir + "/errorpage.html").c_str());
}

TEST_CASE("buildError: returns proper status and loads body from file") {
    const std::string tmp =  "test_tmp_dir";
    const std::string errfile = "test_tmp_dir/errorpage.html";
    createTestDir(tmp);

    config::ServerConfig cfg("config/example.conf");
    ResponseBuilder rb(/*port*/9191, /*server_name*/"localhost", cfg);

    bool ok = rb.buildError("HTTP/1.1", "close", http::NOT_FOUND, errfile);
    CHECK(ok);

    const http::Response& resp = rb.getResponse();
    const std::string wire = resp.toString();

	CHECK(resp.getStatusCode().getCode() == http::NOT_FOUND);
	std::string message = resp.getStatusCode().getMessage();
	CHECK(strcmp(message.c_str(), "Not Found") == 0);
    removeDirectoryRecursive(tmp);
}

TEST_CASE("buildGetFile: returns 200 for existing index file") {
    const std::string tmp =  "test_tmp_dir";

    config::ServerConfig cfg("config/example.conf");
    createTestDir(tmp);

    ResponseBuilder rb(/*port*/9191, /*server_name*/"localhost", cfg);

	bool ok = rb.build("HTTP/1.1", "close", "GET", /*dirPath*/tmp, /*filename*/"index.html");
    CHECK(ok);

	 const http::Response& resp = rb.getResponse();
	 std::string message = resp.getStatusCode().getMessage();
	 
	CHECK(resp.getStatusCode().getCode() == http::OK);
	CHECK(strcmp(message.c_str(), "OK") == 0);
    removeDirectoryRecursive(tmp);
}

// TEST_CASE("buildGetFile: returns 403 when requested filename is not in index list (directory request)") {
//     const std::string tmp = make_tmp_dir();
//     write_file(tmp, "home.html", "<p>Home</p>");

//     config::ServerConfig cfg;
//     cfg.block.loc.root = tmp + "/";
//     cfg.block.loc.index.push_back("index.html"); // home.html тут НІ
//     cfg.block.loc.autoindex = false;

//     ResponseBuilder rb(/*port*/80, /*server_name*/"localhost", cfg);

//     bool ok = rb.buildGetFile("HTTP/1.1", "close", /*dirPath*/tmp + "/", /*filename*/"home.html");
//     CHECK(ok); // buildGetFile повертає true бо зібрав error-відповідь; якщо повертає false — змінюй на CHECK(!ok)

//     const std::string wire = rb.getResponse().toString();
//     CHECK(extract_status_code(wire) == 403); // ти саме щойно поміняв на FORBIDDEN
// }

// TEST_CASE("buildGetFile: returns 404 when file does not exist") {
//     const std::string tmp = make_tmp_dir();

//     config::ServerConfig cfg;
//     cfg.block.loc.root = tmp + "/";
//     cfg.block.loc.index.push_back("index.html");
//     cfg.block.loc.autoindex = false;

//     ResponseBuilder rb(/*port*/80, /*server_name*/"localhost", cfg);

//     bool ok = rb.buildGetFile("HTTP/1.1", "close", /*dirPath*/tmp + "/", /*filename*/"index.html");
//     CHECK(ok);

//     const std::string wire = rb.getResponse().toString();
//     CHECK(extract_status_code(wire) == 404); // немає index.html → 404 (або 403, залежно від твоєї логіки)
// }

// TEST_CASE("build: GET dispatches to buildGetFile and produces 200 for existing index") {
//     const std::string tmp = make_tmp_dir();
//     write_file(tmp, "index.html", "<p>OK!</p>");

//     config::ServerConfig cfg;
//     cfg.block.loc.root = tmp + "/";
//     cfg.block.loc.index.push_back("index.html");
//     cfg.block.loc.autoindex = false;

//     ResponseBuilder rb(/*port*/80, /*server_name*/"localhost", cfg);

//     bool ok = rb.build("HTTP/1.1", "close", "GET", /*dirPath*/tmp + "/", /*filename*/"index.html");
//     CHECK(ok);

//     const std::string wire = rb.getResponse().toString();
//     CHECK(extract_status_code(wire) == 200);
//     CHECK(body_contains(wire, "OK!"));
// }
