#include "doctest.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "ResponseContent.hpp"
#include "test_utils.hpp"

const char* const DEFAULT_MIME_TYPE = "text/plain";

bool mimeTypeCheck(const std::string& type, const std::string& expected) {
    if (type != expected) {
        std::cerr << "MIME type check failed at " << __FILE__ << ":" << __LINE__
                  << "\n  actual:   [" << type << "]"
                  << "\n  expected: [" << expected << "]\n";
        return false;
    }
    return true;
}

bool bodyCheck(const std::string& body, const std::string& expected) {
    if (body != expected) {
        std::cerr << "Body check failed at " << __FILE__ << ":" << __LINE__
                  << "\n  actual:   [" << body << "]"
                  << "\n  expected: [" << expected << "]\n";
        return false;
    }
    return true;
}

static void test_basic_two_column() {
    http::ResponseContent rc;

	writeFile("<!DOCTYPE html><html><head><title>Example</title></head><body><p>This is an example of a simple HTML page with one paragraph.</p></body></html>", "test_files/index.html");
    rc = http::ResponseContent("test_files/index.html");
    CHECK(mimeTypeCheck(rc.getType(), "text/html"));

    writeFile("test_files/style.css", "test_files/style.css");
    rc = http::ResponseContent("test_files/style.css");
    CHECK(mimeTypeCheck(rc.getType(), "text/css"));

    writeFile("test_files/photo.jpg", "test_files/photo.jpg");
    rc = http::ResponseContent("test_files/photo.jpg");
    CHECK(mimeTypeCheck(rc.getType(), "image/jpeg"));

    writeFile("test_files/README", "test_files/README");
    rc = http::ResponseContent("test_files/README");
    CHECK(mimeTypeCheck(rc.getType(), DEFAULT_MIME_TYPE));

    writeFile("test_files/.bashrc", "test_files/.bashrc");
    rc = http::ResponseContent("test_files/.bashrc");
    CHECK(mimeTypeCheck(rc.getType(), DEFAULT_MIME_TYPE));

    writeFile("test_files/weird.", "test_files/weird.");
    rc = http::ResponseContent("test_files/weird.");
    CHECK(mimeTypeCheck(rc.getType(), DEFAULT_MIME_TYPE));
}

static void test_whitespace_tabs_comments() {

    http::ResponseContent rc;

    writeFile("test_files/anim.gif", "test_files/anim.gif");
    rc = http::ResponseContent("test_files/anim.gif");
    CHECK(mimeTypeCheck(rc.getType(), "image/gif"));

    writeFile("test_files/data.json", "test_files/data.json");
    rc = http::ResponseContent("test_files/data.json");
    CHECK(mimeTypeCheck(rc.getType(), "application/json"));

    writeFile("test_files/note.TXT", "test_files/note.TXT");
    rc = http::ResponseContent("test_files/note.TXT");
    CHECK(mimeTypeCheck(rc.getType(), "text/plain"));
}

static void test_multiple_exts_in_one_line() {

    http::ResponseContent rc;

    writeFile("test_files/script.js", "test_files/script.js");
    rc = http::ResponseContent("test_files/script.js");
    CHECK(mimeTypeCheck(rc.getType(), "application/javascript"));

	writeFile("test_files/module.mjs", "test_files/module.mjs");
    rc = http::ResponseContent("test_files/module.mjs");
    CHECK(mimeTypeCheck(rc.getType(), "application/javascript"));

	writeFile("test_files/photo.jpeg", "test_files/photo.jpeg");
    rc = http::ResponseContent("test_files/photo.jpeg");
    CHECK(mimeTypeCheck(rc.getType(), "image/jpeg"));

	writeFile("test_files/vector.svg", "test_files/vector.svg");
    rc = http::ResponseContent("test_files/vector.svg");
    CHECK(mimeTypeCheck(rc.getType(), "image/svg+xml"));
}

static void test_leading_dot_in_mapping() {

    http::ResponseContent rc;

	writeFile("test_files/icon.PNG", "test_files/icon.PNG");
    rc = http::ResponseContent("test_files/icon.PNG");
    CHECK(mimeTypeCheck(rc.getType(), "image/png"));

	writeFile("test_files/report.pdf", "test_files/report.pdf");
    rc = http::ResponseContent("test_files/report.pdf");
    CHECK(mimeTypeCheck(rc.getType(), "application/pdf"));
}

static void test_unknown_extension_defaults() {

    http::ResponseContent rc;

	writeFile("test_files/archive.xyz", "test_files/archive.xyz");
    rc = http::ResponseContent("test_files/archive.xyz");
    CHECK(mimeTypeCheck(rc.getType(), DEFAULT_MIME_TYPE));

	writeFile("test_files/unknown.ext", "test_files/unknown.ext");
    rc = http::ResponseContent("test_files/unknown.ext");
    CHECK(mimeTypeCheck(rc.getType(), DEFAULT_MIME_TYPE));
}

TEST_CASE("testing the ResponseContent class") {
	mkdir("test_files", 0777);
    test_basic_two_column();
    test_whitespace_tabs_comments();
    test_multiple_exts_in_one_line();
    test_leading_dot_in_mapping();
    test_unknown_extension_defaults();

	http::ResponseContent rc("test_files/index.html");
	CHECK(bodyCheck(rc.getBody(), "<!DOCTYPE html><html><head><title>Example</title></head><body><p>This is an example of a simple HTML page with one paragraph.</p></body></html>"));

	removeDirectoryRecursive("test_files"); // Clean up the test directory
}