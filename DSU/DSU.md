# DSU
给定n个连通块/集合，要求

1. 能够进行集合之间的合并。
2. 能够动态维护连通块中的信息。

## Constructor
`DSU dsu(n)`

这将创建n个编号为0 - n-1的连通块

## merge
用于合并连个连通块

`void merge(const int a, const int b)`

@{keyword.constraints}

0 <= a < n

0 <= b < n

{keyword.complexity}

$O(\alpha(n))$ (均摊)

## same
判断两个集合是否属于同一个集合

`bool same(const int a, const int b)`

@{keyword.constraints}

0 <= a < n

0 <= b < n

{keyword.complexity}

$O(\alpha(n))$ (均摊)

## size
连通块的大小，连通块中独立集合的数量

`int size(const int x)`

{keyword.complexity}

$O(\alpha(n))$ (均摊)