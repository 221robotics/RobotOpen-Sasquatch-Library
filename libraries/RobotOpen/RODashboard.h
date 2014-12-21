
#ifndef RODashboard_h
#define RODashboard_h

#include <RobotOpen.h>



class RODashboardClass {
public:
    // Log data to DS
    static void debug(String data);

    // Overloaded calls to publish back data
    static boolean publish(String id, byte val);
    static boolean publish(String id, int val);
    static boolean publish(String id, long val);
    static boolean publish(String id, float val);

};

extern RODashboardClass RODashboard;

#endif