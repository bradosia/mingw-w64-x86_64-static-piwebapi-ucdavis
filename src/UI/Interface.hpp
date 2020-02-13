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

#ifndef UCDPWAB_INTERFACE_H
#define UCDPWAB_INTERFACE_H

// c++17
#include <memory>

/* QT 5.13.2-1
 * License: LGPLv3
 */
#include <QWidget>

/*
 * UCDPWAB = UC Davis PI Web API Browser
 */
namespace UCDPWAB {

class WidgetInterface {
public:
    virtual void init() = 0;
    virtual std::shared_ptr<QWidget> getWidget() = 0;
};

} // namespace UCDPWAB

#endif
// end UCDPWAB_INTERFACE_H