#include "PlayList.h"


struct PlayFolder PlayList::browse(int id) {
  struct PlayFolder folder;
  folder.parent = list[id].parent;
  folder.id = id;
  folder.isDir = true;
  folder.name = list[id].name;

  for(int i = 0; i < (int)list.size(); i++){
    if (list[i].parent == id){
      folder.entries.push_back(list[i]);
    }
  }
  return folder;
}

int PlayList::currentFolder(){
  return currFolder;
}

int PlayList::currentTrack(){
  return currTrack;
}

String PlayList::next(){
  int nId = nextId();
  currFolder = list[nId].parent;
  currTrack  = nId;
  return this->path(nId); 
}

struct PlayEntry PlayList::nextIs(){
  return list[nextId()];
}

String PlayList::previous(){
  int pId = previousId();
  currFolder = list[pId].parent;
  currTrack = pId;
  return this->path(pId); 
}

struct PlayEntry PlayList::previousIs(){
  return list[previousId()];
}

void PlayList::scan(String path) {
  scan(-1, path);
}

String PlayList::select(int id) {
  currFolder = list[id].parent;
  currTrack = list[id].id;
  return this->path(currTrack); 
}

// ----------------------------- PRIVATE -----------------
int PlayList::nextId() {
  int trackNo = (currTrack + 1) >= (int)list.size() ? 0 : currTrack + 1;
  struct PlayEntry entry;

  for (trackNo; trackNo < (int)list.size() ; trackNo++){
    entry = list[trackNo];
    if (trackNo >= 0 && entry.isDir == false){
      break;
    }
  }

  return trackNo;
}

int PlayList::previousId() {
  int trackNo = (currTrack - 1) >= 0 ? 0 : (int)list.size() - 1;
  struct PlayEntry entry;

  for (trackNo; trackNo < (int)list.size() ; trackNo--){
    entry = list[trackNo];
    if (trackNo >= 0 && entry.isDir == false){
      break;
    }
  }

  return trackNo;
}

String PlayList::path(int id) {
  struct PlayEntry entry = list[id];
  String entryPath = entry.parent > 0 ? path(entry.parent) + "/" + entry.name : entry.name;
  return entryPath;
}

void PlayList::scan(int parent, String path) {
  if (path.length() > 1 && path.startsWith("/")) {
    path = path.substring(2);
  }
  File sdFolder = SD.open(path.c_str());
  if (!sdFolder) {
    return;
  }

  struct PlayEntry listItem;
  listItem.id = list.size();
  listItem.parent = parent;
  listItem.isDir = true;
  listItem.name = sdFolder.name();
  list.push_back(listItem);
  int listId = list.size() - 1;

  std::vector<String> dirs;
  std::vector<String> files;


  while (true) {
    File entry = sdFolder.openNextFile();
    if (!entry) {
      break;
    }

    String entryName = path + "/" + String(entry.name());

    if (entry.isDirectory()) {
      dirs.push_back(entryName);
    } else {
      if (entryName.toLowerCase().endsWith(".mp3")) {
        files.push_back(String(entry.name()));  //entryName);
      }
    }
    entry.close();
  }
  sdFolder.close();

  if (dirs.size() > 0) {
    for (int d = 0; d < (int)dirs.size(); d++) {
      scan(listId, dirs[d]);
    }
  }

  if (files.size() > 0) {
    for (int f = 0; f < (int)files.size(); f++) {
      struct PlayEntry newFile;
      newFile.id = list.size();
      newFile.parent = listId;
      newFile.name = files[f];

      list.push_back(newFile);
    }
  }
}
