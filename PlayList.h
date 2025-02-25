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
  struct PlayFolder browse(int id);
  int currentFolder();
  int currentTrack();
  String next();
  struct PlayEntry nextIs();
  String path(int id);
  String previous();
  struct PlayEntry previousIs();
  void scan(String path);
  String select(int id);

private:
  void scan(int parent, String path);
  int nextId();
  int previousId();

  int currFolder = -1;
  int currTrack = -1;
  std::vector<struct PlayEntry> list;
};