I'm trying to create a plugin manager for c++ that checks a directory for shared libraries (dll,so,dylib) and checks if they have an interface available

```cpp
PluginManager pluginManagerObj;
pluginManagerObj.addPluginInterface<pluginInterface>("pluginName");
pluginManagerObj.loadPlugins("plugins_directory");
std::shared_ptr<pluginInterface> plugin = pluginManagerObj.getPlugin("pluginName");
```
