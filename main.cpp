#include <iostream>
#include <glib.h>
#include <gio/gio.h>

int main() {
    GVolumeMonitor *volume_monitor;
    GList *mounts;
    GList *l;
    int c;
    GMount *mount;
    GFile *default_location;

    // Get list of all gvfs mounts
    volume_monitor = g_volume_monitor_get();
    mounts = g_volume_monitor_get_mounts(volume_monitor);
    if (mounts == NULL) {
        std::cout << "Geen camera gevonden!" << std::endl;
        return 1;
    }

    // Loop through all mounts and get mount details
    for (c = 0, l = mounts; l != NULL; l = l->next, c++) {
        mount = (GMount *) l->data;
        char *name = g_mount_get_name(mount);

        std::cout << "Foto's importeren van " << name << std::endl;

        default_location = g_mount_get_default_location(mount);
        char *loc_uri = g_file_get_uri(default_location);

        std::cout << name << " " << loc_uri << std::endl;
    }

    return 0;
}