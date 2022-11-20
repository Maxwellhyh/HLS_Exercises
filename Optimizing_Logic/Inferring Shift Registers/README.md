Vitis HLS will now infer a shift register when encountering the following code:

int A[N]; // This will be replaced by a shift register
 
for(...) {
  // The loop below is the shift operation
  for (int i = 0; i < N-1; ++i)
    A[i] = A[i+1];
  A[N] = ...;
 
  // This is an access to the shift register
  ... A[x] ...
}

Shift registers can perform a one shift operation per cycle, and also allows a random read access per cycle anywhere in the shift register, thus it is more flexible than a FIFO.

## Repository Tree
```
.
├── fir.cpp          //源码示例
├── fir.h            //头文件
├── fir_test.cpp     //测试源码
├── input.dat        //测试输入
├── out.gold.dat     //标准输出
├── tcl_script.tcl   //tcl文件
└── README.md        //说明文件
```
