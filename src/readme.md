# Source Code
The UI directory contains anything that mentions or uses any part of QT or User Interface libraries. 
The theory is that presentation should be separated from logic. 

The core directory should include logic

# Plugins
Boost is used for loading the dynamic libraries. QT also includes a plugin manager, but that won't be
used to reduce dependence on the QT system.