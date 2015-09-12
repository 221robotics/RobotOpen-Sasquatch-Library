#include "RobotOpenSQ.h"

// Class constructor
RODashboardClass RODashboard;




void RODashboardClass::debug(String data) {
    RobotOpen.log(data);
}

boolean RODashboardClass::publish(String id, byte val) {
    return RobotOpen.publish(id, val);
}

boolean RODashboardClass::publish(String id, int val) {
    return RobotOpen.publish(id, val);
}

boolean RODashboardClass::publish(String id, long val) {
    return RobotOpen.publish(id, val);
}

boolean RODashboardClass::publish(String id, float val) {
    return RobotOpen.publish(id, val);
}