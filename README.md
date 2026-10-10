Build:
    cmake -S . -B build

    cmake --build build

Test:

    ctest --test-dir build --output-on-failure