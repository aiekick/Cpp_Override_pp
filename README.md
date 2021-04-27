# Cpp Override of ++/-- pre/post

++/-- mixed post and pre in same exp cause Undefined behavior and different result with many compiler

## clang on win10 give that : 

by cmake

```cpp
int i(5), i = i++ + ++i * i-- => 54
	
Num i(5), i = i++ + ++i * i-- => 54
i++ : 6
++i : 7
i-- : 6
7 * 7 : 49
5 + 49 : 54
```

## Mingw32 on win10 give that : 

by cmake

```cpp
int i(5), i = i++ + ++i * i-- => 47
	
Num i(5), i = i++ + ++i * i-- => 30
i-- : 4
++i : 5
5 * 5 : 25
i++ : 6
5 + 25 : 30
	
```

## MSVC on win10 give that : 

by cmake

```cpp
int i(5), i = i++ + ++i * i-- => 42
	
Num i(5), i = i++ + ++i * i-- => 30
i-- : 4
++i : 5
5 * 5 : 25
i++ : 6
5 + 25 : 30
```

## g++ on linux give that : 

g++ main.cpp -o main -v

```cpp
int i(5), i = i++ + ++i * i-- => 47
	
Num i(5), i = i++ + ++i * i-- => 30
i-- : 4
++i : 5
5 * 5 : 25
i++ : 6
5 + 25 : 30
```

## clang on linux give that : 

clang++ -std=c++11 -pedantic -Wall main.cpp -o main -v

```cpp
int i(5), i = i++ + ++i * i-- => 54

Num i(5), i = i++ + ++i * i-- => 54
i++ : 6
++i : 7
i-- : 6
7 * 7 : 49
5 + 49 : 54
```
