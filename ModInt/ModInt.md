// template<int V, int P>
// constexpr ModInt<P> CInv = ModInt<P>(V).inv();

// constexpr int P = 998244353;
// using Z = ModInt<P>;

# ModInt

什么是ModInt？
ModInt是一种自动处理模数的数据结构，可以用来处理静态模数的算术问题。

它有哪些优点？
1. 使用静态多态编写类模板，提高代码的复用性。
2. 使用 `constexpr` 修饰函数，将运行期提前到编译期。

## e.g.
示例求卡特兰数的第n项的模数:
$\frac {C_{2*n}^{n}} {n+1}$ % mod

```cpp
import ModInt;

constexpr int P = 1E9 + 7;
using Z = ModInt<P>;

int main() {
    
    int n;
    std::cin >> n;
    
    Z ans = 1;
    for (int a = n << 1, b = n, i = a, j = 1; j <= b; --i, ++j) {
        ans *= i;
        ans /= j;
    }
    ans /= n + 1;
    
    std::cout << ans << std::endl;
    
    return 0;
}
```

## Constructor
无参初始化与有参初始化
```
constexpr ModInt() : x{} {}
constexpr ModInt(i64 x) : x{norm(x % P)} {}
```

## Operations
以下操作有效
```
-modint;

modint + modint;
modint - modint;
modint * modint;
modint / modint;

modint += modint;
modint -= modint;
modint *= modint;
modint /= modint;

modint == modint;
modint != modint;
```

## power
使用快速幂实现乘方
```
ModInt x.pow(i64 n)
```
return $x^n$

@{keyword.constraints}

0 <= n

@{keyword.complexity}

O(log n)

## inv
使用费马小定理实现逆元
```
ModInt x.inv()
```
return y. xy $\equiv$ 1

@{keyword.constraints}

x != 0 && isPrime(mod)

@{keyword.complexity}

O(log mod)