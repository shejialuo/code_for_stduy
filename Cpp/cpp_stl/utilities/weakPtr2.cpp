#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

/*
  * `weak_ptr` allows sharing but not owning an object.
  * This class requires a shared pointer to get created.
  * Whenever the last shared pointer owning the object loses
  * its ownership, any weak pointer automatically becomes
  * empty.
  *
  * You can't use operator * and -> to access a referenced
  * object of a `weak_ptr` directly. Instead, you have to
  * create a shared pointer out of it.
*/
class Person {
public:
  string name;
  shared_ptr<Person> mother;
  shared_ptr<Person> father;
  vector<weak_ptr<Person>> kids;

  Person(const string & n,
         shared_ptr<Person> m = nullptr,
         shared_ptr<Person> f = nullptr)
    : name(n), mother(m), father(f) {}
  virtual ~Person() {
    cout  << "delete " << name << endl;
  }
};

shared_ptr<Person> initFamily(const string& name) {
  shared_ptr<Person> mom(new Person(name+ "'s mon"));
  shared_ptr<Person> dad(new Person(name +"'s dad"));
  shared_ptr<Person> kid(new Person(name, mom, dad));
  mom->kids.push_back(kid);
  dad->kids.push_back(kid);
  return kid;
}

int main() {
  shared_ptr<Person> p = initFamily("nico");

  cout << "nico's family exists" << endl;
  cout << "- nico is shared " << p.use_count() << " times" << endl;
  cout << "- name of 1st kid of nico's mon: "
       << p->mother->kids[0].lock()->name << endl;

  p = initFamily("jim");
  cout << "jim's family exists" << endl;

  return 0;
}
