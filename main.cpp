#include <iostream>
#include <glib.h>
#include <gio/gio.h>

int main() {
    GVolumeMonitor *volume_monitor;
    GList *mounts;
    GList *l;
    int c;
    GMount *mount;

    volume_monitor = g_volume_monitor_get();
    mounts = g_volume_monitor_get_mounts(volume_monitor);
    if (mounts == NULL) {
        std::cout << "Geen camera gevonden!" << std::endl;
        return 1;
    }

    for (c = 0, l = mounts; l != NULL; l = l->next, c++) {
        mount = (GMount *) l->data;
        std::cout << "CAMERA!" << std::endl;
    }

    return 0;
}