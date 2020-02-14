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

#ifndef UCDPWAB_PLUGINS_H
#define UCDPWAB_PLUGINS_H

// Universal Include
#include "universalInclude.hpp"

// local project
#include "Interface.hpp"

/*
 * UCDPWAB = UC Davis PI Web API Browser
 */
namespace UCDPWAB {

void loadPlugins();

class PluginManager {
public:
  template <class T, std::string S> void addPluginInterface(std::string interfaceName) {

  }
};

} // namespace UCDPWAB

#endif
// end UCDPWAB_PLUGINS_H
