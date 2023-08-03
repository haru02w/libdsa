## Data Structure and Algorithms Library

#### How to use it

```sh
cd your_project
git clone https://github.com/haru02w/libdsa.git libs/libdsa
```

then if you are using cmake, copy the following into your `CMakeLists.txt`
replacing < >

```txt
add_subdirectory(libs/libdsa)
target_link_libraries(<your_executable> PRIVATE dsa)
```

[Coding Style](docs/coding_style.md)

#### TODO

- [ ] Arrays
  - [x] Dynamic Arrays (Vector)
  - [ ] Sorting Algorithms
    - [x] Insertion Sort
    - [x] Selection Sort
    - [x] Bubble Sort
    - [x] Merge Sort
    - [x] Shell sort
    - [ ] Quick Sort
    - [ ] Heap Sort
    - [ ] Radix Sort
    - [ ] Bucket Sort
  - [ ] Searching Algorithms
    - [ ] Linear Search
    - [ ] Binary Search
- [ ] Linked Lists (circular, double linked, single linked)
  - [ ] Insertion
  - [ ] Deletion
  - [ ] Search
  - [ ] Find Length
- [ ] Queue (dinamically allocated)
  - [ ] Enqueue
  - [ ] Dequeue
- [ ] Stack (dinamically allocated)
  - [ ] Push
  - [ ] Pop
- [ ] Binary Tree
  - [ ] traversals
    - [ ] pre-order
    - [ ] in-order
    - [ ] post-order
    - [ ] Breadth First Traversal
    - [ ] Depth First Traversals
  - [ ] Find Heights
  - [ ] Binary Search Tree
    - [ ] Insertion
    - [ ] Deletion
    - [ ] Search
    - [ ] AVL
    - [ ] Red-Black
- [ ] Hash
- [ ] Heap
- [ ] Matrix
- [ ] Graph

* More stuff will be added as we learn

Made with ❤
