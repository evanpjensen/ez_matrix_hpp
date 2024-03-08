# ez_matrix_hpp
Header only C++ matrix multiplication implementation. Underlying storage is std::array.

## example
```c++
  std::cout<< M4({{
    {1,0,0,0},
    {1,1,0,0},
    {0,0,1,0},
    {0,0,0,1},
    }}) * M4({{
    {1,0,0,0},
    {1,1,1,1},
    {1,0,1,0},
    {1,0,0,1},
    }}) <<std::endl;
  // 1 0 0 0 
  // 2 1 1 1 
  // 1 0 1 0 
  // 1 0 0 1 

  std::cout<< M<int,2,3>({{
      {1,2,3},
      {4,5,6},
    }}) * M<int,3,2>({{
      {7,8},
      {9,10},
      {11,12},
    }}) <<std::endl;
  // 58 64
  // 139 154
```
