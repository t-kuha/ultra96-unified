"""
Create LED blink application.
"""
import os
import shutil
import subprocess
import vitis


PFM_NAME='u96v2_led'
PRJ_NAME='led_blink_pl'
TOP_DIR=os.path.dirname(os.path.abspath(__file__))
PFM_DIR=os.path.join(TOP_DIR, '_pfm', PFM_NAME, 'export', PFM_NAME)
WORKSPACE=os.path.join(TOP_DIR, '_vitis')

if os.path.exists(WORKSPACE):
    print('[INFO] removing existing workspace...')
    shutil.rmtree(WORKSPACE)
assert os.path.exists(PFM_DIR)

client = vitis.create_client()
client.set_workspace(path=WORKSPACE)

client.add_platform_repos(PFM_DIR)
xpfm = client.find_platform_in_repos(PFM_NAME)
comp = client.create_app_component(
    name=PRJ_NAME, platform=client.find_platform_in_repos(PFM_NAME),
    domain='standalone_psu_cortexa53_0'
)

# copy source files
SRC_NAMES = ['helloworld.c', 'platform.c', 'platform.h']
for src_name in SRC_NAMES:
    shutil.copy(
        os.path.join(TOP_DIR, 'src', src_name),
        os.path.join(WORKSPACE, PRJ_NAME, 'src', src_name)
    )

comp.build()

vitis.dispose()

# generate BOOT.bin
subprocess.run([
    'bootgen',
    '-image', os.path.join(TOP_DIR, "bootbin.bif"),
    '-arch', 'zynqmp',
    '-o', 'BOOT.bin',
    '-w', 'on'
])
