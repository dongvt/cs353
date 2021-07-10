/***********************************************************************
 * COMPONENT:
 *    CONTROL
 * Author:
 *    Br. Helfrich, Govert Carreno
 * Summary:
 *    This class stores the notion of Bell-LaPadula
 ************************************************************************/

#pragma once

#include <string>
#include <map>

enum Control {
    PUBLIC,
    CONFIDENTIAL,
    PRIVILEGED,
    SECRET
};

bool securityControlRead(Control assetControl, Control subjectControl);

bool securityControlWrite(Control assetControl, Control subjectControl);

Control convertToControl(std::string controlString);