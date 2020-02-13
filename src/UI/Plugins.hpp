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

/*
 * UCDPWAB = UC Davis PI Web API Browser
 */
class WidgetInterface : public QWidget {
public:
    virtual ~WidgetInterface() = default;
    virtual void init();
};

QT_BEGIN_NAMESPACE

#define BrushInterface_iid "org.qt-project.Qt.Examples.PlugAndPaint.BrushInterface/1.0"

Q_DECLARE_INTERFACE(WidgetInterface, BrushInterface_iid)

QT_END_NAMESPACE

namespace UCDPWAB {

class WidgetInterface : public QWidget {
public:
    virtual void init();
};

void loadPlugins();

} // namespace UCDPWAB

#endif
// end UCDPWAB_PLUGINS_H
