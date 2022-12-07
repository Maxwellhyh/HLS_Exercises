set Project     systolic_array
set Solution    solution1
set Device      "xc7z020-clg400-1"
set Flow        "vivado"
set Clock       10

open_project $Project -reset

set_top mmult_hw

add_files mmult_accel.cpp -cflags -I.
add_files mmult_accel.h -cflags -I. 
add_files -tb main.cpp -cflags -I.

open_solution -flow_target $Flow -reset $Solution
set_part $Device
create_clock -period $Clock

#csim_design
csynth_design
#cosim_design

exit
