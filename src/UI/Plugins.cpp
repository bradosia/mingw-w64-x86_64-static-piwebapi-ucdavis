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

#include "Plugins.hpp"

/*
 * UCDPWAB = UC Davis PI Web API Browser
 */
namespace UCDPWAB {

void loadPlugins() {
  const auto staticInstances = QPluginLoader::staticInstances();
  // for (QObject *plugin : staticInstances)
  //    populateMenus(plugin);

  for (auto &p : std::filesystem::recursive_directory_iterator("plugins")) {
    std::cout << p.path() << "\n";
    if (p.is_regular_file() &&
        (p.path().extension() == ".dll" || p.path().extension() == ".dylib" ||
         p.path().extension() == ".so")) {
      std::cout << p.path() << " is libsh \n";
      QPluginLoader loader(QString(p.path().string().c_str()));
      QObject *plugin = loader.instance();
      if (plugin) {
        auto iWidget = qobject_cast<QWidget *>(plugin);
        if (iWidget) {
          std::cout << p.path() << " is widget \n";
        }
      }
    }
  }
}

} // namespace UCDPWAB
