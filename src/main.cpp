#include <stdio.h>

// c++
#include <string>
#include <iostream>
#include <thread>
#include <sstream>

/*
 * CURL 7.68.0
 */
#define CURL_STATICLIB
#include <curl/curl.h>
#include <brotli/decode.h>

/*
 * piwebapi-ucdavis 1.0
 */
#define DEFAULT_MAXREDIRS 5
#include "piwebapi-ucdavis/amalgamated.h"

size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s) {
	s->append((char*) ptr, size * nmemb);
	return size * nmemb;
}

void printJSON_value(const rapidjson::Value &a, unsigned int depth);
void printJSON_iterator(rapidjson::Value::ConstMemberIterator &itr,
		unsigned int depth);

int main(void) {
	CURL *curl;
	CURLcode res;
	std::string bufferString;
	rapidjson::Document resJSON_Doc;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	if (curl) {
		//std::string homeHTTP = "https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi";
		std::string electricityHTTP =
				"https://ucd-pi-iis.ou.ad3.ucdavis.edu/piwebapi/streams/A0EbgZy4oKQ9kiBiZJTW7eugwC6-3Qzx_5RGrBZiQlqSuWw2sDVYNIPR1YODsG1RUyETgVVRJTC1BRlxDRUZTXFVDREFWSVNcQlVJTERJTkdTXEFDQURFTUlDIFNVUkdFIEJVSUxESU5HXEVMRUNUUklDSVRZfERFTUFORA/recorded";
		curl_easy_setopt(curl, CURLOPT_URL, electricityHTTP.c_str());
		//curl_easy_setopt(curl, CURLOPT_CAINFO, "/etc/ssl/certs/ca-certificates.crt");

		/* Disable SSL/TLS verification
		 * TODO: Write the SSL Certificate Manager
		 */
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

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
		resJSON_Doc.Parse(bufferString.c_str());

		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));

		std::cout << bufferString << std::endl;

		if (resJSON_Doc.IsObject()) {
			for (rapidjson::Value::ConstMemberIterator itr =
					resJSON_Doc.MemberBegin(); itr != resJSON_Doc.MemberEnd();
					++itr) {
				printJSON_iterator(itr, 0);
			}
		}

		/* always cleanup */
		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

	system("pause");

	return 0;
}

void printJSON_value(const rapidjson::Value &a, unsigned int depth) {
	if (a.IsArray()) {
		rapidjson::SizeType n = a.Size(); // rapidjson uses SizeType instead of size_t.
		for (rapidjson::SizeType i = 0; i < n; i++) {
			if (a[i].IsObject()) {
				rapidjson::Value::ConstMemberIterator itr = a[i].MemberBegin();
				printJSON_iterator(itr, ++depth);
			} else if(a[i].IsArray()){
				const rapidjson::Value &aa = a[i];
				printJSON_value(aa, ++depth);
			}
		}
	}
}

void printJSON_iterator(rapidjson::Value::ConstMemberIterator &itr,
		unsigned int depth) {
	static const char *kTypeNames[] = { "Null", "False", "True", "Object",
			"Array", "String", "Number" };
	printf("Type of member %s is %s\n", itr->name.GetString(),
			kTypeNames[itr->value.GetType()]);
	if (itr->value.GetType() == 3) {
		const rapidjson::Value &a = itr->value;
		for (rapidjson::Value::ConstMemberIterator itr2 = a.MemberBegin();
				itr2 != a.MemberEnd(); ++itr2) {
			printJSON_iterator(itr2, ++depth);
		}
	} else if (itr->value.GetType() == 4) {
		const rapidjson::Value &a = itr->value;
		printJSON_value(a, ++depth);
	}
}
