# Index Bin

 Index Bin is a datastructure concept wherein you have an N-sized vector
 paritioned into used and unused indexes. 
 
 Indices under each partition are not in any particular order. But even 
 though this is the case, searching for an index will take O(1) because
 of the index mapper, which monitors the position of the index under the
 bin.
 
 Below is a sample data structure of a 10-sized element Index Bin.
 
 Bin:
 Used     | Unused
 0 1 2 3    4 5 6 7 8 9 10
 4 5 2 10 | 9 0 1 3 6 7 8 
 
 Index Mapper
 0 1 2 3 4 5 6 7 8  9 10
 5 6 2 7 0 1 8 9 10 4 3  
 
Some Applications of Index Bin
---

Snake Egg Generation
Game of Life 