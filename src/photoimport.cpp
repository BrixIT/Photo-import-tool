#include "photoimport.h"
#include <iostream>

PhotoImport::PhotoImport()
        : m_button("Import"),   // creates a new button with label "Hello World".
          m_box(Gtk::ORIENTATION_VERTICAL, 4),
          m_label_count("Searching for pictures to import"),
          m_progressbar(),
          m_entry_name() {

    // Sets window title
    set_title("Picture import");

    // Sets the padding inside the window.
    set_border_width(10);

    // When the button receives the "clicked" signal, it will call the
    // on_button_clicked() method defined below.
    m_button.signal_clicked().connect(sigc::mem_fun(*this,
            &PhotoImport::on_button_clicked));

    // Pack all widgets in the vbox
    m_box.add(m_label_count);
    m_box.add(m_entry_name);
    m_box.add(m_progressbar);
    m_box.add(m_button);
    add(m_box);

    m_searching = true;

    m_progressbar.pulse();

    // The final step is to display this newly created widget...
    m_label_count.show();
    m_entry_name.show();
    m_progressbar.show();
    m_button.show();
    m_box.show();

    sigc::slot<bool> timer_slot = sigc::mem_fun(*this,
                   &PhotoImport::on_timeout);

    Glib::signal_timeout().connect(timer_slot, 50);

}

PhotoImport::~PhotoImport() {
}

void PhotoImport::on_button_clicked() {
    std::cout << "Hello World" << std::endl;
}

bool PhotoImport::on_timeout() {
    if (m_searching) {
        m_progressbar.pulse();
    }
    return true;
}