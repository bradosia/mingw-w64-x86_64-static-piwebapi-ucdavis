/*
 * @name UC Davis 3D Analyzer
 * @author Brad Lee & SiYi Meng
 * @version 1.01
 * @license GNU LGPL v3
 * @brief 3D map of UC Davis electricity usage
 *
 * QT and OCC integration:
 * Copyright (c) 2018 Shing Liu (eryar@163.com)
 * License: MIT
 * Source: https://github.com/eryar/occQt
 *
 * Data from OSIsoft and UC Davis
 * Icons and images owned by their respective owners
 */

// local project
#include "HTTP_JSON.hpp"

/*
 * UCDPWAB = UC Davis PI Web API Browser
 */
namespace UCDPWAB {

void HTTP_JSON::get(std::string URI) {
  CURL *curl;
  CURLcode res;
  std::string bufferString;
  std::shared_ptr<rapidjson::Document> resJSON_Doc = std::make_shared<rapidjson::Document>();

  printf("HTTPS_GET_JSON called on: %s\n", URI.c_str());

  curl_global_init(CURL_GLOBAL_DEFAULT);

  curl = curl_easy_init();

  if (curl) {

    curl_easy_setopt(curl, CURLOPT_URL, URI.c_str());
    // curl_easy_setopt(curl, CURLOPT_CAINFO,
    // "/etc/ssl/certs/ca-certificates.crt");

    /*
     * TODO: Write the SSL Certificate Manager
     */
    // getCertificates(global);
#ifdef SKIP_PEER_VERIFICATION
    /*
     * If you want to connect to a site who isn't using a certificate that is
     * signed by one of the certs in the CA bundle you have, you can skip the
     * verification of the server's certificate. This makes the connection
     * A LOT LESS SECURE.
     *
     * If you have a CA cert for the server stored someplace else than in the
     * default bundle, then the CURLOPT_CAPATH option might come handy for
     * you.
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
    /*
     * If the site you're connecting to uses a different host name that what
     * they have mentioned in their server certificate's commonName (or
     * subjectAltName) fields, libcurl will refuse to connect. You can skip
     * this check, but this will make the connection less secure.
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif

    /* setup callbacks */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &bufferString);
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    resJSON_Doc->Parse(bufferString.c_str());
    documents.push_back(resJSON_Doc);

    /* Check for errors */
    if (res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
#ifdef DEBUG_JSON
    std::cout << bufferString << std::endl;
#endif
    /* always cleanup */
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s) {
  s->append((char *)ptr, size * nmemb);
  return size * nmemb;
}

} // namespace UCDPWAB
