template<int p, int q, int r>
struct ga {
  struct mv { /*...*/ };
  template<int g>
  struct gmv : mv { /*...*/ };
};

template<int p, int q, int r>
void print(ga<p,q,r>::mv v) { /* ... */ }

int main() {
  using pga = ga<3,1,0>;
  pga::gmv<2> v;
  print(v);
}
