## Repository Tree

```
.
├── cordiccart2pol.cpp        //源码框架
├── cordiccart2pol.h          //头文件
├── cordiccart2pol_test.cpp   //测试源码
├── tcl_script.tcl            //tcl文件
└── README.md                 //说明文件
```

The pragma specifies that the variable coeffs uses a single port RAM implemented on a BRAM core from the library.

#pragma HLS bind_storage variable=coeffs type=RAM_1P impl=bram