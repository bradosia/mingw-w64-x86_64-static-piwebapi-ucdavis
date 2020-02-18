/*
 * @name UC Davis PI Web API Browser
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Browser for UC Davis PI Web API data.
 *
 * Data from OSIsoft and UC Davis
 * Icons and images owned by their respective owners
 */

#ifndef UCDPWAB_HTTP_JSON_H
#define UCDPWAB_HTTP_JSON_H

// Universal Include
#include "UI/universalInclude.hpp"

/*
 * UCDPWAB = UC Davis PI Web API Browser
 */
namespace UCDPWAB {

/*
 * Makes HTTP and HTTPS calls to a JSON API.
 */
class HTTP_JSON {
private:
  std::vector<std::shared_ptr<rapidjson::Document>> documents;

public:
  HTTP_JSON() {}
  ~HTTP_JSON(){}
  /* Makes an HTTPS GET request to the URI
   * @param URI The address
   */
  void get(std::string URI);
};

/* Writes data from HTTP request into a string buffer
 * @param ptr data address
 */
size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s);

} // namespace UCDPWAB

#endif // UCDPWAB_HTTP_JSON_H
