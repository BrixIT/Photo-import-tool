#ifndef PHOTOIMPORT_H
#define PHOTOIMPORT_H

#include <gtkmm/main.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/progressbar.h>
#include <glibmm.h>

class PhotoImport : public Gtk::Window
{

public:
    PhotoImport();
    virtual ~PhotoImport();

protected:
    //Signal handlers:
    void on_button_clicked();
    bool on_timeout();

    //Main container for window
    Gtk::Box m_box;

    //Member widgets:
    Gtk::Label m_label_count;
    Gtk::Entry m_entry_name;
    Gtk::ProgressBar m_progressbar;
    Gtk::Button m_button;

    bool m_searching;
};

#endif
