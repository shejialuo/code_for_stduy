#include "../algostuff.hpp"
using namespace std;

int main() {
  vector<string> coll1 = {"Hello", "this", "is", "an", "example"};
  list<string> coll2;

  copy(coll1.cbegin(), coll1.cend(), back_inserter(coll2));

  move(coll2.cbegin(), coll2.cend(),
      ostream_iterator<string>(cout, " "));
  cout << endl;

  move(coll1.crbegin(), coll1.crend(), coll2.begin());

  move(coll2.cbegin(), coll2.cend(),
      ostream_iterator<string>(cout, " "));
  cout << endl;

  return 0;
}
