/*
 * Name        : PI WEB API for UC Davis
 * Author      : Brad Lee
 * Version     : 1.00
 * License     : GNU LGPL v3
 *
 */

#ifndef PWA_UCD_AMALGAMATED_H
#define PWA_UCD_AMALGAMATED_H

// c++17
#include <string>
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>

// c
#include <stdio.h>
#include <string.h>

/*
 * CURL 7.68.0
 */
#define CURL_STATICLIB
#include <curl/curl.h>
#include <brotli/decode.h>

/* CURL EXE 7.68.0
 * Taken from the source from the CURL executable
 * EDIT 1: Code was taken out because source wouldn't static link
 */
//#include "curlx.h"
//#include "tool_setup.h"
//#include "tool_cfgable.h"
//#include "tool_msgs.h"
//#include "tool_doswin.h" // FindWin32CACert

/* rapidjson v1.1 (2016-8-25)
 * Developed by Tencent
 */
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/reader.h" // rapidjson::ParseResult

/*
 * PWA_UCD = PI Web API for UC Davis
 */
namespace PWA_UCD {

CURLcode http_get(struct GlobalConfig *global) {
	CURLcode result = CURLE_OK;

	return result;
}

}
 // end PWA_UCD

#endif
