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

  for (auto &p : std::filesystem::recursive_directory_iterator("plugins")) {
    std::cout << "PLUGIN: Found " << p.path() << "\n";
    if (p.is_regular_file() &&
        (p.path().extension() == ".dll" || p.path().extension() == ".dylib" ||
         p.path().extension() == ".so")) {

      boost::filesystem::path lib_path(p.path().string().c_str());
      std::cout << "PLUGIN: Loading " << p.path() << "\n";
      boost::shared_ptr<UCDPWAB_pluginInterface> plugin;
      try {
        plugin = boost::dll::import<UCDPWAB_pluginInterface>(
            lib_path, "plugin", boost::dll::load_mode::default_mode);
      } catch (...) {
        std::cout << "PLUGIN: Loading FAILED " << p.path() << "\n";
      }
      if (plugin) {
        std::cout << "PLUGIN: Loading SUCCESS " << p.path() << "\n";
        plugin->init();
        std::shared_ptr<QWidget> widget = plugin->getWidget();
        std::cout << "PLUGIN: widget " << widget->objectName().toStdString() << "\n";
      }
    }
  }
}

} // namespace UCDPWAB
