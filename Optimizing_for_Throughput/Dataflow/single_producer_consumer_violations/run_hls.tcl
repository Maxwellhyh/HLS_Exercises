 
open_project producer_consumer
set_top dut
add_files dut.cpp
add_files -tb test_dut.cpp
open_solution "solution1"
set_part {xc7z020clg400-1}
create_clock -period 10 -name default
csim_design
csynth_design
cosim_design


