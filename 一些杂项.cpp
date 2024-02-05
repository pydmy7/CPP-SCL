// GCC优化选项
#pragma GCC optimize("Ofast", "inline")

// 进制控制格式
std::oct  // 八进制 Octal
std::dec  // 十进制 decimalism
std::hex  // 十六进制 hexadecimal
std::cout << 0b100 << '\n';  // 二进制
std::cout << 0100 << '\n';  // 八进制
std::cout << 100 << '\n';  // 十进制
std::cout << 0x100 << '\n';  // 十六进制

// __builtin_
__builtin_popcount();  // pop Count
__builtin_popcountll();
__builtin_clz();  // Count Leading Zero
__builtin_ctz();  // Count Tail Zero

// rng
auto starter = std::chrono::steady_clock::now().time_since_epoch();
std::mt19937 rng(starter.count());
std::shuffle(arr.begin(), arr.end(), rng);
auto ender = std::chrono::steady_clock::now().time_since_epoch();
double timer = 1E-9 * (ender - starter).count();

// file
std::ifstream fin("input.txt"); fin >> ;
std::ofstream fout("output.txt"); fout << ;

// stl
cbrt
partial_sum
adjacent_difference
partition
rotate
shuffle