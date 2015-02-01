#include <iostream>
#include <glib.h>
#include <gio/gio.h>
#include <string.h>

bool has_dir(GFileEnumerator *enumerator, const char *searchName){
    GFileInfo *info;
    while ((info = g_file_enumerator_next_file (enumerator, NULL, NULL)) != NULL)
    {
        const char *dirname = g_file_info_get_name (info);
        if(strcmp(dirname,searchName) == 0){
            return true;
        }
    }
    return false;
}

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

        default_location = g_mount_get_default_location(mount);
        char *loc_uri = g_file_get_uri(default_location);
        GFile *camera_root = g_file_new_for_commandline_arg(loc_uri);

        // Search for DCIM directory on the device
        GFileEnumerator *enumerator = g_file_enumerate_children (camera_root,
                "standard::name",
                G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
                NULL,
                NULL);

        if(has_dir(enumerator, "DCIM")){
            std::cout << "Foto's importeren van " << name << std::endl;
        }else{
            std::cout << name << " bevat geen DCIM map" << std::endl;
        }
    }

    return 0;
}