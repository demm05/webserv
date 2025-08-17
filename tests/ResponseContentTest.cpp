#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "ResponseContent.hpp"
#include "doctest.h"

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

static void writeMimeFile(const std::string& content, const char* path) {
    std::ofstream out(path);
    out << content;
    out.close();
}

static void test_basic_two_column() {
    ResponseContent rc;

	writeMimeFile("<!DOCTYPE html><html><head><title>Example</title></head><body><p>This is an example of a simple HTML page with one paragraph.</p></body></html>", "test_files/index.html");
    rc = ResponseContent("test_files/index.html");
    CHECK(mimeTypeCheck(rc.getType(), "text/html"));

    writeMimeFile("test_files/style.css", "test_files/style.css");
    rc = ResponseContent("test_files/style.css");
    CHECK(mimeTypeCheck(rc.getType(), "text/css"));

    writeMimeFile("test_files/photo.jpg", "test_files/photo.jpg");
    rc = ResponseContent("test_files/photo.jpg");
    CHECK(mimeTypeCheck(rc.getType(), "image/jpeg"));

    writeMimeFile("test_files/README", "test_files/README");
    rc = ResponseContent("test_files/README");
    CHECK(mimeTypeCheck(rc.getType(), DEFAULT_MIME_TYPE));

    writeMimeFile("test_files/.bashrc", "test_files/.bashrc");
    rc = ResponseContent("test_files/.bashrc");
    CHECK(mimeTypeCheck(rc.getType(), DEFAULT_MIME_TYPE));

    writeMimeFile("test_files/weird.", "test_files/weird.");
    rc = ResponseContent("test_files/weird.");
    CHECK(mimeTypeCheck(rc.getType(), DEFAULT_MIME_TYPE));
}

static void test_whitespace_tabs_comments() {

    ResponseContent rc;

    writeMimeFile("test_files/anim.gif", "test_files/anim.gif");
    rc = ResponseContent("test_files/anim.gif");
    CHECK(mimeTypeCheck(rc.getType(), "image/gif"));

    writeMimeFile("test_files/data.json", "test_files/data.json");
    rc = ResponseContent("test_files/data.json");
    CHECK(mimeTypeCheck(rc.getType(), "application/json"));

    writeMimeFile("test_files/note.TXT", "test_files/note.TXT");
    rc = ResponseContent("test_files/note.TXT");
    CHECK(mimeTypeCheck(rc.getType(), "text/plain"));
}

static void test_multiple_exts_in_one_line() {

    ResponseContent rc;

    writeMimeFile("test_files/script.js", "test_files/script.js");
    rc = ResponseContent("test_files/script.js");
    CHECK(mimeTypeCheck(rc.getType(), "application/javascript"));

	writeMimeFile("test_files/module.mjs", "test_files/module.mjs");
    rc = ResponseContent("test_files/module.mjs");
    CHECK(mimeTypeCheck(rc.getType(), "application/javascript"));

	writeMimeFile("test_files/photo.jpeg", "test_files/photo.jpeg");
    rc = ResponseContent("test_files/photo.jpeg");
    CHECK(mimeTypeCheck(rc.getType(), "image/jpeg"));

	writeMimeFile("test_files/vector.svg", "test_files/vector.svg");
    rc = ResponseContent("test_files/vector.svg");
    CHECK(mimeTypeCheck(rc.getType(), "image/svg+xml"));
}

static void test_leading_dot_in_mapping() {

    ResponseContent rc;

	writeMimeFile("test_files/icon.PNG", "test_files/icon.PNG");
    rc = ResponseContent("test_files/icon.PNG");
    CHECK(mimeTypeCheck(rc.getType(), "image/png"));

	writeMimeFile("test_files/report.pdf", "test_files/report.pdf");
    rc = ResponseContent("test_files/report.pdf");
    CHECK(mimeTypeCheck(rc.getType(), "application/pdf"));
}

static void test_unknown_extension_defaults() {

    ResponseContent rc;

	writeMimeFile("test_files/archive.xyz", "test_files/archive.xyz");
    rc = ResponseContent("test_files/archive.xyz");
    CHECK(mimeTypeCheck(rc.getType(), DEFAULT_MIME_TYPE));

	writeMimeFile("test_files/unknown.ext", "test_files/unknown.ext");
    rc = ResponseContent("test_files/unknown.ext");
    CHECK(mimeTypeCheck(rc.getType(), DEFAULT_MIME_TYPE));
}

bool removeRecursive(const std::string &path) {
    DIR *dir = opendir(path.c_str());
    if (!dir) return false;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        std::string name = entry->d_name;
		// Skip the current and parent directory entries
        if (name == "." || name == "..") continue;

        std::string fullPath = path + "/" + name;
        struct stat st;
        if (stat(fullPath.c_str(), &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
				// Recursively remove the directory
                if (!removeRecursive(fullPath)) {
                    closedir(dir);
                    return false;
                }
            } else {
				// Remove the file
                if (unlink(fullPath.c_str()) != 0) {
                    closedir(dir);
                    return false;
                }
            }
        }
    }
    closedir(dir);
    return rmdir(path.c_str()) == 0;
}

TEST_CASE("testing the ResponseContent class") {
	mkdir("test_files", 0777);
    test_basic_two_column();
    test_whitespace_tabs_comments();
    test_multiple_exts_in_one_line();
    test_leading_dot_in_mapping();
    test_unknown_extension_defaults();

	ResponseContent rc("test_files/index.html");
	CHECK(bodyCheck(rc.getBody(), "<!DOCTYPE html><html><head><title>Example</title></head><body><p>This is an example of a simple HTML page with one paragraph.</p></body></html>"));

	removeRecursive("test_files"); // Clean up the test directory
}