#include "util.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <curl/curl.h>

size_t WriteCallback(void *contents, const size_t size, size_t nmemb, void *userp) {
  const size_t totalSize = size * nmemb;
  static_cast<std::string *>(userp)->append(static_cast<char *>(contents), totalSize);
  return totalSize;
}

void util::fetchInput(const std::string &path, const std::string &day) {
  std::cout << path << std::endl;
  const auto session = std::getenv("SESSION") ? std::getenv("SESSION") : "";
  const std::string cookie = "session=" + std::string(session);
  const std::string url = "https://adventofcode.com/2024/day/" + day + "/input";
  std::string fetchedInput;

  if (CURL *curl = curl_easy_init()) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_COOKIE, cookie.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &fetchedInput);

    if (CURLcode res = curl_easy_perform(curl); res != CURLE_OK) {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    }

    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  if (std::ofstream outFile(path); outFile.is_open()) {
    outFile << fetchedInput;
  } else {
    std::cerr << "Could not open file for writing" << std::endl;
  }
}

void util::fetchExamples(const std::string &path, const std::string &day) {
  const auto session = std::getenv("SESSION");
  const std::string cookie = "session=" + std::string(session);
  const std::string url = "https://adventofcode.com/2024/day/" + day;
  std::string fetchedPage;

  if (CURL *curl = curl_easy_init()) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_COOKIE, cookie.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &fetchedPage);

    if (const CURLcode res = curl_easy_perform(curl); res != CURLE_OK) {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    }

    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();

  std::regex pattern("<pre><code>((.*\n)*?)</code></pre>");
  if (std::smatch match; std::regex_search(fetchedPage, match, pattern)) {
    std::ofstream outFile(path);
    if (!outFile.is_open()) {
      std::cerr << "Could not open file for writing" << std::endl;
    }
    outFile << match.str(1);
  }
}
