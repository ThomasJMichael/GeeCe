# GeeCe Garbage Collector

GeeCe is a simple garbage collector implemented in C that provides automatic memory management. The garbage collector is responsible for detecting unreferenced objects in memory and reclaiming them, thereby freeing up memory that can be reused by the program.

## Getting Started

To build GeeCe, run the following command in the project directory:

```BASH
make
```

This will compile the source code and generate the geece executable in the bin directory.

## Usage

To use GeeCe in your C program, include the gc.h header file in your source code and use the GC_malloc() function to allocate memory. The garbage collector will automatically detect when an object is no longer referenced and reclaim its memory.

```C
#include <stdio.h>
#include <stdlib.h>
#include "gc.h"

int main(void) {
    int *p = GC_malloc(sizeof(int));
    *p = 42;

    printf("The answer is %d\n", *p);

    return 0;
}
```

## Running Tests

To run the test suite for GeeCe, run the following command in the project directory:

```BASH
make test
```

This will compile the test source code and generate the test executables in the bin directory.

## Contributing

Contributions to GeeCe are welcome! If you find a bug or would like to suggest a new feature, please open an issue on the project's GitHub repository.

## License

GeeCe is licensed under the MIT License. See LICENSE for more information.