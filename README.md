# multimedia_data_processing_sandbox

# how to read binary files: `hexdump -C filename`

# full operation ranking from high to low
```cpp
~    (NOT)
<<   (left shift)
>>   (right shift)
&    (AND)
^    (XOR)
|    (OR)
```

# small optimisations:
```cpp
/**
 * DO NOT MIX C and C++ io streams when using these options (cout and printf).
 */
ios::sync_with_stdio(false);  // disable sync with C stdio
cin.tie(nullptr);              // stop cout flushing before every cin read
```

```cpp
// return bit length
return n==0 ? 1 : (int)log2(n) + 1;
/**
 * or with __builtin_clz() which counts the number of leading zeros in the binary representation of an integer:
 * Note: __builtin_clz() is a GCC built-in function and may not be available in all compilers. It also assumes that the input is a 32-bit integer.
 */
return n == 0 ? 1 : 32 - __builtin_clz(n);
```