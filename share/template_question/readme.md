# Stackoverflow
https://stackoverflow.com/questions/60220913/c-storing-plugin-interfaces

# Post

I'm trying to create a plugin manager for c++ that checks a directory for shared libraries (dll,so,dylib) and checks if there is a plugin interface available to store the plugin and retrieve it later with.

I'm using boost::dll to import the dll, but I don't know how to set up the template so I can make the code in main.cpp work.

How do I use templates or some other method to add plugin interfaces to the plugin manager so it will check the shared libraries for the export alias name and store the shared library handle?

PluginInterface.hpp
```cpp
class PluginInterface {
public:
  virtual void testPlugin() = 0;
};
```

plugin.hpp source for "plugins_directory/plugin.dll"
```cpp
#include <boost/config.hpp> // for BOOST_SYMBOL_EXPORT
#include "pluginInterface.hpp"

namespace PluginNamespace {
class PluginClass : public PluginInterface {
  void testPlugin(){
    printf("Hello World!");
  }
}

extern "C" BOOST_SYMBOL_EXPORT PluginClass pluginName;
PluginClass pluginName;
}
```

THIS CODE IS INCORRECT, but I am trying to make some attempt to show what I'm trying to do except I'm not sure where to start on the template syntax:
PluginManager.hpp
```cpp
#include <boost/dll/import.hpp>

class PluginManager {
private:
    std::unordered_map<std::string, void*> pluginMap;
public:
  template <class T> void addPluginInterface(std::string pluginName) {
    // somehow create make loadPlugins() and getPlugin() aware of class T
  }

  void PluginManager::loadPlugins(std::string directoryPathStr) {
    for (auto &p :
         std::filesystem::recursive_directory_iterator(directoryPathStr)) {
      std::cout << "PLUGIN: File Found " << p.path() << "\n";
      if (p.is_regular_file() &&
          (p.path().extension() == ".dll" || p.path().extension() == ".dylib" ||
           p.path().extension() == ".so")) {
        boost::filesystem::path lib_path(p.path().string().c_str());
        std::cout << "PLUGIN: Loading " << p.path() << "\n";
        boost::shared_ptr<T> plugin;
        try {
          plugin = boost::dll::import<T>(lib_path, pluginName, boost::dll::load_mode::default_mode);
        } catch (...) {
          std::cout << "PLUGIN: Loading FAILED " << p.path() << "\n";
        }
        if (plugin) {
          std::cout << "PLUGIN: Loading SUCCESS " << p.path() << "\n";
          pluginMap.insert({pluginName,plugin})
        }
      }
    }
  }

  std::shared_ptr<T> getPlugin(std::string pluginName) {
    // somehow return the stored class T instance of the pluginName
  }
};
```

main.cpp
```cpp
#include "PluginManager.hpp"
#include "PluginInterface.hpp"

int main(){
  PluginManager pluginManagerObj;
  pluginManagerObj.addPluginInterface<PluginInterface>("pluginName");
  pluginManagerObj.loadPlugins("plugins_directory");
  std::shared_ptr<PluginInterface> plugin = pluginManagerObj.getPlugin("pluginName");
  plugin->testPlugin();
}
```
