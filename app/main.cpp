#include <QApplication>
#include <iostream>
#include "../include/doctorWindow.h"

using namespace std;

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Services services{};
    vector<DoctorWindow*> windows;
    for(auto d : services.getDoctors())
    {
        DoctorWindow* window = new DoctorWindow{services, d};
        windows.push_back(window);
        window->show();
    }
    return app.exec();
}
