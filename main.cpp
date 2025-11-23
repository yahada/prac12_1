#include <iostream>
#include <cstddef>
#include <memory>

struct Ints {
  Ints();
  ~Ints();
  Ints(const Ints & w);
  Ints(Ints && w);
  Ints(size_t kk, int i);
  Ints & operator=(const Ints & w);
  Ints & operator=(Ints && w);
  size_t size() const;
  int get(size_t i) const; // const показывает что метод не будет менять объект
  void set(size_t id, int i);
  Ints append(int i) const;
  Ints append(const Ints& w ) const;
  private:
    size_t k;
    int * d;
};
Ints::Ints(size_t kk, int i):
  d(kk ? new int[kk] : nullptr),
  k(kk)
{

  for (size_t j = 0; j < kk; ++j) {
    d[j] = i;
  }
    
  
}
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

struct p_t {
  int x, y;
};



struct Points {
  Points() = default;
  Points(size_t k, p_t a);
  void set(size_t id, p_t a) const;
  p_t get(size_t id) const;
  size_t size() const;
  Points append(p_t p) const;
  Points append(const Points & w) const;
  private:
  Points(Ints && d);
  Ints data;
};

Points::Points(size_t k, p_t a):
  data(k*2, a.x) {
    for (size_t i = 0; i < k; ++i) {
      data.set(i * 2 + 1, a.y);

    }
}

p_t Points::get(size_t id) const {
  p_t r{data.get(id * 2), data.get(id * 2 + 1)};
  return r;
} 

size_t Points::size() const {
  return data.size()/2;
}

Points::Points(Ints && d):
  data(std::move(d))  
{}

// Points Points::append(p_t a) const {
//   Ints delta(2, a.x);
//   delta.set(1, a.y);
//   delta = data.append(delta);
//   return Points(std::move(delta));
// }

Points Points::append(const Points & w) const 
{
  Points r;
  // r.data = new int[data.size() + w.data.size()];
  for (size_t i = 0; i < data.size(); ++i) {
    r.data.set(i, data.get(i));
  }

  for (size_t i = data.size(); i < data.size() + w.data.size(); ++i) {
    r.set(i, w.get(i-data.size()));
  }
  return r;
}


int main() {

}