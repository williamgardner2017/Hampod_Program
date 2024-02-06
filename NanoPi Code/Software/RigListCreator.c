#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <dirent.h>

#include <hamlib/rig.h>

// #include "misc.h"

#include <hamlib/config.h>

#define SERIAL_PORT "/dev/ttyUSB0"
#define FOLDER_PATH "./StartupFiles/"

void removeTextFiles() {
  DIR *d;
  struct dirent *dir;
  d = opendir(FOLDER_PATH);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (dir->d_type == DT_REG && strstr(dir->d_name, ".txt")) {
        char fullFilePath[256];
        snprintf(fullFilePath, sizeof(fullFilePath), "%s%s", FOLDER_PATH, dir->d_name);
        remove(fullFilePath);
      }
    }
    closedir(d);
  }
}

void createTextFileList() {
  DIR *d;
  struct dirent *dir;
  FILE *file = fopen(FOLDER_PATH "CompanyList.txt", "w");
  if (!file) {
    fprintf(stderr, "Error opening file for writing\n");
    exit(1);
  }

  d = opendir(FOLDER_PATH);
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (dir->d_type == DT_REG && strstr(dir->d_name, ".txt")) {
        fprintf(file, "%s\n", dir->d_name);
      }
    }
    closedir(d);
  }

  fclose(file);
}

int callback(struct rig_caps *caps, rig_ptr_t rigp) {
  char filename[256];
  snprintf(filename, sizeof(filename), FOLDER_PATH "%s.txt", caps->mfg_name);

  FILE *file = fopen(filename, "a");
  if (!file) {
    fprintf(stderr, "Error opening file for writing\n");
    exit(1);
  }

  RIG *rig = (RIG *) rigp;
  rig = rig_init(caps->rig_model);
  if (!rig)
  {
    fprintf(stderr, "Unknown rig num: %u\n", caps->rig_model);
    fprintf(stderr, "Please check riglist.h\n");
    exit(1); /* whoops! something went wrong (mem alloc?) */
  }
  const char *port = "/dev/pts/3";
  strcpy(rig->state.rigport.pathname, port);
  fprintf(file, "%s, %s, %u\n", caps->mfg_name, caps->model_name, caps->rig_model);
  fclose(file);
  // printf("%s, %u\n", caps->model_name, caps->rig_model);

  fflush(stdout);
  rig_cleanup(rig); /* if you care about memory */
  return 1;
}

int createRigLists() {
  RIG rig;
  printf("testing rig timeouts when rig powered off\n");

  /* Turn off backend debugging output */
  rig_set_debug_level(RIG_DEBUG_NONE);
  removeTextFiles();
  rig_load_all_backends();
  rig_list_foreach(callback, &rig);
  createTextFileList(); 
  return 0;
}
