#include <MemoryFree.h>
#include "PlayList.h"


PlayList pl;

void setup() {
  SD.begin(BUILTIN_SDCARD);

  delay(500);
  Serial.print(F("Free RAM = "));
  Serial.println(freeMemory(), DEC);
  pl.scan("/");
  Serial.print(F("Free RAM = "));
  Serial.println(freeMemory(), DEC);
  Serial.printf("Names %d\n", pl.list.size());
  for (int i = 0; i < (int)pl.list.size(); i++) {
    Serial.printf("%d %d [%d]- %s\n", pl.list[i].parent, i, (int)pl.list[i].isDir, pl.list[i].name.c_str());
  }
  //delay(5000);
}

void loop() {
  //randomSeed(random(millis()));
  //int fileNo = random(pl.list.size());
  //Serial.printf("path %d [%d] = %s\n",fileNo,pl.list[fileNo].id,  pl.path(fileNo).c_str());

  int nextTrack = pl.nextId();
  Serial.printf("next [%d] = %s \n", nextTrack, pl.select(nextTrack).c_str());


  //Serial.println("\n----------------------------\n");
  //Serial.printf("Next %s\n",pl.trackNext().c_str());
  //Serial.printf("Previous %s\n",pl.files[pl.previous()].c_str());
  //Serial.printf("Random 1 %s\n",pl.files[pl.rand()].c_str());
  //Serial.printf("Random 2 %s\n",pl.files[pl.rand()].c_str());
  //Serial.printf("Random 3 %s\n",pl.files[pl.rand()].c_str());
  struct PlayFolder folder = pl.browse(2);

  Serial.printf("folder [%d] = %s \n", folder.id , folder.name.c_str());
  for(int i = 0 ; i < (int)folder.entries.size(); i++){
  Serial.printf("\t [%d] %d = %s \n", i, folder.entries[i].id, pl.path(folder.entries[i].id).c_str());
  }

  delay(5000);
}