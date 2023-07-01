# Setting
set PRJ_DIR     _vivado
set PRJ_NAME    ultra96
set BD_NAME     ${PRJ_NAME}
set SRC_DIR     src
set NUM_JOBS    2

# Add board repo path
set_param board.repoPaths $::env(RDI_DATADIR)/xhub/boards/XilinxBoardStore/boards/Avnet

# Remove existing directory
file delete -force ${PRJ_DIR}

# Create project
create_project ${PRJ_NAME} ${PRJ_DIR} -part xczu3eg-sbva484-1-e
set_property board_part avnet.com:Ultra96v1:part0:1.2 [current_project]

# Add constraint
add_files -fileset constrs_1 -norecurse ${SRC_DIR}/Ultra96_constraints_180318.xdc

# Create block design
source ${SRC_DIR}/bd.tcl

# Set top-level source
make_wrapper -files [get_files ${PRJ_DIR}/${PRJ_NAME}.srcs/sources_1/bd/${BD_NAME}/${BD_NAME}.bd] -top
add_files -norecurse ${PRJ_DIR}/${PRJ_NAME}.srcs/sources_1/bd/${BD_NAME}/hdl/${BD_NAME}_wrapper.v
set_property top ${BD_NAME}_wrapper [current_fileset]
update_compile_order -fileset sources_1

regenerate_bd_layout
validate_bd_design
save_bd_design

# Generate bitstream
update_compile_order -fileset sources_1

reset_run synth_1
launch_runs synth_1 -jobs ${NUM_JOBS}
wait_on_run synth_1
launch_runs impl_1 -to_step write_bitstream -jobs ${NUM_JOBS}
wait_on_run impl_1

# Report utilization & clock after implementation
open_run impl_1
report_utilization
report_clocks

# Export .xsa file
write_hw_platform -fixed -force -include_bit -file ${PRJ_NAME}.xsa
validate_hw_platform ${PRJ_NAME}.xsa

# Finish - close project
close_project
