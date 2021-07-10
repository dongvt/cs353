#include "control.h"

bool securityControlRead(Control assetControl, Control subjectControl) {
    return subjectControl >= assetControl;
}

bool securityControlWrite(Control assetControl, Control subjectControl) {
    return subjectControl <= assetControl;
}