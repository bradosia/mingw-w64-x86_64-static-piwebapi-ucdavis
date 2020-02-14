I'm trying to create a plugin manager for c++ that checks a directory for shared libraries (dll,so,dylib) and checks if they have an interface available

plugin.hpp source for plugin.dll 
```cpp
#include <boost/config.hpp> // for BOOST_SYMBOL_EXPORT

class PluginClass : public pluginInterface {
  void testPlugin(){
    printf("Hello World!");
  }
}

extern "C" BOOST_SYMBOL_EXPORT PluginClass pluginName;
PluginClass pluginName;
```

```cpp
PluginManager pluginManagerObj;
pluginManagerObj.addPluginInterface<pluginInterface>("pluginName");
pluginManagerObj.loadPlugins("plugins_directory");
std::shared_ptr<pluginInterface> plugin = pluginManagerObj.getPlugin("pluginName");
```
