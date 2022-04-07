#include <gtkmm/application.h>
#include "MyWindow.hpp"

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create("com.mckaudio.gtk.first");
    return app->make_window_and_run<MyWindow>(argc, argv);
}