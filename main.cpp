#include <iostream>
#include <cstddef>

struct Ints {
  Ints();
  ~Ints();
  Ints(const Ints & w);
  Ints(Ints && w);
  Ints & operator=(const Ints & w);
  Ints & operator=(Ints && w);
  private:
    size_t k;
    int * d;
};

Ints::Ints():
  d(nullptr),
  k(0ull) {

}

Ints::Ints(const Ints & w):
  d(w.k ? new int[w.k] : nullptr),
  k(w.k) {
  for (size_t i = 0; i < k; ++i) {
    d[i] = w.d[i];
  }
}

// Ints & Ints::operator=(const Ints & w) {
//   int * r = nullptr;
//   if (w.k) {
//     r = new int[w.k];
//     for (size_t i = 0; i < k; ++i) {
//       r[i] = w.d[i];
//     }
//   }
//   delete[] d;
//   d = r;
//   k = w.k;
//   return *this; //*this - указатель на объект
//   //разыменованный указатель дает ссылку
// }

Ints & Ints::operator=(Ints && w) { // перемещение, масив не копируется а просто перемещается
  // if (this = &w) {
  //   return *this;
  // }
  //v = std::move(v); v - lvalue, std::move(v) - xvalue;
  delete[] d;
  d = w.d;
  k = w.k;
  w.d = nullptr;
  return *this;
}

int main() {

}