#ifndef PHOTOIMPORT_H
#define PHOTOIMPORT_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>

class PhotoImport : public Gtk::Window
{

public:
    PhotoImport();
    virtual ~PhotoImport();

protected:
    //Signal handlers:
    void on_button_clicked();

    //Member widgets:
    Gtk::Button m_button;
};

#endif
