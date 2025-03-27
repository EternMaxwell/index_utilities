# Index Utilities

This is a template utility library dedicated for [epix_engine](https://github.com/EternMaxwell/epix_engine.git)

## Integration

To integrate the library in your project, use cmake subdirectories and git submodules.

```
git submodule add https://github.com/EternMaxwell/index_utilities <path/to/lib>
```

Then in CMakeLists.txt file, add

```
add_subdirectories(path/to/lib)
...
# your target
...
add_library(your_target index_utilities)
```

And you are now able to use the library in your project.

## Current Modules

### concurrent

Utils for multithread programming.

#### conqueue<T>

A concurrent FIFO queue.

#### channel

This contains 2 structs, `Sender<T>` and `Receiver<T>`, and a function to create a pair of Sender and Receiver `std::tuple<Sender<T>, Receiver<T>> make_channel();`

### traits

This module contains structs for compile time type reflections needed for [epix_engine](https://github.com/EternMaxwell/epix_engine.git), including structs to detecting whether a struct is an implementation of a template struct, and whether tuple contain certain types or template types.
