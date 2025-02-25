#include <SD.h>

struct PlayEntry {
  int parent = -1;
  int id = -1;
  bool isDir = false;
  String name;
};

struct PlayFolder {
  int parent = -1;
  int id = -1;
  bool isDir = false;
  String name;
  std::vector<struct PlayEntry> entries;
};

class PlayList {
public:
  void scan(String path);
  String select(int id);
  String path(int id);
  void currentSet(int id);
  int nextId();
  int previousId();
  struct PlayFolder browse(int id);
  std::vector<struct PlayEntry> list;
private:
  void scan(int parent, String path);
  int currentFolder = -1;
  int currentFile = -1;
};