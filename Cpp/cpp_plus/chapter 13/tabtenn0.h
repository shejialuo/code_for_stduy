#ifndef TABTENN0_H_
#define TABTENN0_H_

#include <string>
using std::string;

class TableTennisPlayer {
private:
  string firstName;
  string lastName;
  bool hasTable;
public:
  TableTennisPlayer(const string& fn = "none",
                    const string& ln = "none",
                    bool ht = false);
  void name() const;
  bool HasTable() const {return hasTable;};
  void resetTable(bool v) {hasTable = v;};
};

#endif // TABTENN0_H_