// Evan Jensen
#pragma once
#include <algorithm>
#include <array>
#include <ostream>

template <typename T, size_t X, size_t Y> class M {
public:
  using matrix_t_inner = std::array<T, Y>;
  using matrix_t = std::array<matrix_t_inner, X>;

  // (n x m)  times (m x p) is (n x p) sized
  template <size_t rY> using pair_t = M<T, Y, rY>;
  template <size_t rY> using pair_o = typename pair_t<rY>::matrix_t;
  template <size_t rY> using product_t = M<T, X, rY>;
  template <size_t rY> using product_i = typename product_t<rY>::matrix_t_inner;

  const matrix_t m;
  
  constexpr M(const matrix_t &a) : m(a) {}
  operator matrix_t() { return m; }

  template <size_t rY>
  decltype(auto) constexpr operator*(const pair_t<rY> &rhs) const {
    return this->multiply(rhs);
  }

private:
  template <size_t rY>
  decltype(auto) constexpr multiply(const pair_t<rY> &rhs) const {
    return multiply(std::make_index_sequence<X>{},
                    std::make_index_sequence<Y>{},
                    std::make_index_sequence<rY>{}, this->m, rhs.m);
  }

  template <size_t... Xs, size_t... Ys, size_t... rY>
  static product_t<sizeof...(rY)> constexpr multiply(
      const std::index_sequence<Xs...> &, const std::index_sequence<Ys...> &,
      const std::index_sequence<rY...> &, const matrix_t &lhs,
      const pair_o<sizeof...(rY)> &rhs) {

    return {{[&](const size_t &x) {
      return product_i<sizeof...(rY)>{{[&](const size_t &y) {
        return ((lhs[x][Ys] * rhs[Ys][y]) + ...);
      }(rY)...}};
    }(Xs)...}};
  }
};

template <typename T, size_t X, size_t Y>
std::ostream &operator<<(std::ostream &o, const M<T, X, Y> &m) {
  for (auto a = 0ul; a < X; a++) {
    for (auto b = 0ul; b < Y; b++) {
      o << m.m[a][b] << " ";
    }
    o << "\n";
  }
  return o;
}
template <typename T, std::size_t X> using SM = M<T, X, X>;
using M4 = SM<float, 4>;

static_assert((M4({{
                   {1, 0, 0, 0},
                   {1, 1, 0, 0},
                   {0, 0, 1, 0},
                   {0, 0, 0, 1},
               }}) *
               M4({{
                   {1, 0, 0, 0},
                   {1, 1, 1, 1},
                   {1, 0, 1, 0},
                   {1, 0, 0, 1},
               }}))
                  .m == M4({{
                               {1, 0, 0, 0},
                               {2, 1, 1, 1},
                               {1, 0, 1, 0},
                               {1, 0, 0, 1},
                           }})
                            .m);

static_assert((M<int, 2, 3>({{
                   {1, 2, 3},
                   {4, 5, 6},
               }}) *
               M<int, 3, 2>({{
                   {7, 8},
                   {9, 10},
                   {11, 12},
               }}))
                  .m == M<int, 2, 2>({{
                                         {58, 64},
                                         {139, 154},
                                     }})
                            .m);
