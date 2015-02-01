#include <iostream>
#include <glib.h>
#include <gio/gio.h>
#include <string.h>

bool has_dir(GFileEnumerator *enumerator, const char *searchName) {
    GFileInfo *info;
    while ((info = g_file_enumerator_next_file(enumerator, NULL, NULL)) != NULL) {
        const char *dirname = g_file_info_get_name(info);
        if (strcmp(dirname, searchName) == 0) {
            return true;
        }
    }
    return false;
}

int get_file_count(GFile *dir){
    GFileEnumerator *enumerator = g_file_enumerate_children(dir,
            "standard::name",
            G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
            NULL,
            NULL);

    GFileInfo *info;
    int count = 0;
    while ((info = g_file_enumerator_next_file(enumerator, NULL, NULL)) != NULL) {
        count++;
    }
    return count;
}

void move_pictures(const char *src, const char *dest) {
    GFile *search_root = g_file_new_for_commandline_arg(src);
    GFile *dest_gfile = g_file_new_for_commandline_arg(dest);
    GFile *target;
    GFile *src_file;
    GFileCopyFlags flags = G_FILE_COPY_OVERWRITE;
    int total = get_file_count(search_root);
    GFileEnumerator *enumerator = g_file_enumerate_children(search_root,
            "standard::name",
            G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
            NULL,
            NULL);

    GFileInfo *info;
    int i = 0;
    while ((info = g_file_enumerator_next_file(enumerator, NULL, NULL)) != NULL) {
        std::cout << "Importeren van foto " << i+1 << " van " << total << std::endl;
        const char *filename = g_file_info_get_name(info);
        std::string source_file = std::string(src);
        source_file.append("/");
        source_file.append(filename);
        target = g_file_get_child (dest_gfile, filename);
        src_file = g_file_new_for_commandline_arg(source_file.c_str());
        g_file_move(src_file,target, flags, NULL, NULL, NULL, NULL);
        i++;
    }
}

const char *first_dir(const char *path) {
    GFile *search_root = g_file_new_for_commandline_arg(path);

    GFileEnumerator *enumerator = g_file_enumerate_children(search_root,
            "standard::name",
            G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
            NULL,
            NULL);

    GFileInfo *info;
    while ((info = g_file_enumerator_next_file(enumerator, NULL, NULL)) != NULL) {
        const char *dirname = g_file_info_get_name(info);
        return dirname;
    }
    return "";
}

int main(int argc, char *argv[]) {
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
        GFileEnumerator *enumerator = g_file_enumerate_children(camera_root,
                "standard::name",
                G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS,
                NULL,
                NULL);

        if (has_dir(enumerator, "DCIM")) {
            std::cout << "Foto's importeren van " << name << std::endl;
            std::string dcim_path = std::string(loc_uri);
            dcim_path.append("DCIM");
            const char *picture_dir_name = first_dir(dcim_path.c_str());
            std::string picture_dir = std::string(dcim_path);
            picture_dir.append("/");
            picture_dir.append(picture_dir_name);
            std::cout << "Foto pad is " << picture_dir << std::endl << std::endl;
            move_pictures(picture_dir.c_str(),argv[1]);
            std::cout << std::endl << "Foto's importeren voltooid" << std::endl;
        } else {
            std::cout << name << " bevat geen DCIM map" << std::endl;
        }
    }

    return 0;
}