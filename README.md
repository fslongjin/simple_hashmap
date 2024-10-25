# Simple hashmap

A simple hashmap implemented in C, suitable for scenarios with low performance requirements or small data volumes. **Especially suitable for helping you leave work on time!**

This project aims to provide an out-of-the-box, simple hashmap implementation. (Ideal for situations where you're too lazy to build your own wheel)

This project implements key-value storage (both key and value are primitive types).

Hash collision resolution method: Linear probing (You can replace this strategy by modifying the `next_index()` function).


## Usage

Place the `simple_hashmap.h` and `simple_hashmap.c` files in your project, then include the header file to use.

## Testing

### Functional Testing

```
make test
```

### Benchmark

```
make benchmark
```

Test Environment:

- CPU: AMD EPYC 7K62 48-Core Processor (Tencent Cloud CVM SA2)

| Operation   | Throughput (ops/sec) |
|-------------|----------------------|
| Insert      | 229104965.25         |
| Get         | 229506843.10         |
| Remove      | 229405721.64         |


# License

[MIT](LICENSE)

# Contributing

Feel free to open issues or submit pull requests.

# Contact

If you have any questions, please feel free to contact me.

- longjin@dragonos.org OR jinlong@tencent.com
