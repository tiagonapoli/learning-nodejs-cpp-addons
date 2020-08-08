Some learnings from "C++ and Node.js Integration", by Scott Frees:

- In order to manipulate V8 primitives we have to copy data out of V8 storage
  cells into C++ address space. After manipulating we have to allocate new V8
  storage cells to return the data - This have to be done because primitives are
  immutable.
