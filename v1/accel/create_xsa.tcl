# Setting
set PRJ_DIR     _vivado
set PRJ_NAME    ultra96
set BD_NAME     ${PRJ_NAME}
set SRC_DIR     src

# Add board repo path
set_param board.repoPaths $::env(RDI_DATADIR)/xhub/boards/XilinxBoardStore/boards/Avnet

# Remove existing directory
file delete -force ${PRJ_DIR}

# Create project
create_project ${PRJ_NAME} ${PRJ_DIR} -part xczu3eg-sbva484-1-e
set_property board_part avnet.com:Ultra96v1:part0:1.2 [current_project]
set_property platform.extensible "true" [current_project]

# Create block design
source ${SRC_DIR}/bd.tcl

# Set top-level source
make_wrapper -files [get_files [current_bd_design].bd] -top
add_files -norecurse ${PRJ_DIR}/${PRJ_NAME}.srcs/sources_1/bd/${BD_NAME}/hdl/${BD_NAME}_wrapper.v
set_property top ${BD_NAME}_wrapper [current_fileset]
update_compile_order -fileset sources_1

# Generate block design
regenerate_bd_layout
validate_bd_design
save_bd_design
generate_target all [get_files ${PRJ_DIR}/${PRJ_NAME}.srcs/sources_1/bd/${BD_NAME}/${BD_NAME}.bd]

# # Generate bitstream
# update_compile_order -fileset sources_1

# reset_run synth_1
# launch_runs synth_1
# wait_on_run synth_1
# launch_runs impl_1 -to_step write_bitstream
# wait_on_run impl_1

# # Report utilization & clock after implementation
# open_run impl_1
# report_utilization
# report_clocks

# Export .xsa file
set_property platform.design_intent.embedded {true} [current_project]
set_property platform.design_intent.server_managed {false} [current_project]
set_property platform.design_intent.external_host {false} [current_project]
set_property platform.design_intent.datacenter {false} [current_project]
set_property platform.default_output_type {sd_card} [current_project]
set_property platform.uses_pr {false} [current_project]
write_hw_platform -force -file ${PRJ_NAME}.xsa
validate_hw_platform ${PRJ_NAME}.xsa

# Finish - close project
close_project
