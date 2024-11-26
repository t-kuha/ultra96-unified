"""
Create platform.
"""
import os
import shutil
import vitis


TOP_DIR=os.path.dirname(os.path.abspath(__file__))

# platform info
PFM_WS_DIR=os.path.join(TOP_DIR, '_pfm')
PFM_NAME='u96v2_led'

if os.path.exists(PFM_WS_DIR):
    print('[INFO] removing existing directory...')
    shutil.rmtree(PFM_WS_DIR)

client = vitis.create_client()
client.set_workspace(path=PFM_WS_DIR)

platform = client.create_platform_component(
    name=PFM_NAME,
    desc='Ultra96 v2 standalone platform',
    hw_design=os.path.join(TOP_DIR, 'ultra96v2.xsa'),
    os='standalone',
    cpu='psu_cortexa53_0',
    domain_name='standalone_psu_cortexa53_0',
    is_pmufw_req=True
)

platform = client.get_component(name=PFM_NAME)

domain = platform.get_domain(name='zynqmp_pmufw')
status = domain.set_config(option='os', param='standalone_stdin', value='psu_uart_1')
status = domain.set_config(option='os', param='standalone_stdout', value='psu_uart_1')
domain = platform.get_domain(name='zynqmp_fsbl')
status = domain.set_config(option='os', param='standalone_stdin', value='psu_uart_1')
status = domain.set_config(option='os', param='standalone_stdout', value='psu_uart_1')
domain = platform.get_domain(name='standalone_psu_cortexa53_0')
status = domain.set_config(option='os', param='standalone_stdin', value='psu_uart_1')
status = domain.set_config(option='os', param='standalone_stdout', value='psu_uart_1')

status = platform.build()

vitis.dispose()
