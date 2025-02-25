#include "PlayList.h"


PlayList pl;

void setup() {
  SD.begin(BUILTIN_SDCARD);

  pl.scan("/");
}

void loop() {
  Serial.printf("next = %s \n", pl.next().c_str());

  struct PlayFolder folder = pl.browse(61);

  Serial.printf("folder [%d] = %s \n", folder.id , folder.name.c_str());
  for(int i = 0 ; i < (int)folder.entries.size(); i++){
  Serial.printf("\t [%d] %d = %s \n", i, folder.entries[i].id, pl.path(folder.entries[i].id).c_str());
  }

  delay(5000);
}