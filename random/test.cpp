#include <iostream>

struct A {
  A(int x) : x(x) {}
  A(const A &a) { x = 2; }
  A(A &&a) { x = 3; }
  int x;
};

void foo(A t) { std::cout << t.x; }

int main() {
  A a(0);
  foo(a);
  foo(A(0));
}
