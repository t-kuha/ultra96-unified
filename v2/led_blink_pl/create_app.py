"""
Create LED blink application.
"""
import os
import shutil
import vitis


PFM_NAME='u96v2_led'
PRJ_NAME='led_blink_pl'
TOP_DIR=os.path.dirname(os.path.abspath(__file__))
PFM_PATH=os.path.join(
    TOP_DIR, '_pfm', PFM_NAME, 'export', PFM_NAME, f'{PFM_NAME}.xpfm'
)
WORKSPACE=os.path.join(TOP_DIR, '_vitis')

if os.path.exists(WORKSPACE):
    print('[INFO] removing existing workspace...')
    shutil.rmtree(WORKSPACE)
assert os.path.exists(PFM_PATH)

client = vitis.create_client()
client.set_workspace(path=WORKSPACE)

comp = client.create_app_component(
    name=PRJ_NAME, platform=PFM_PATH, domain='standalone_psu_cortexa53_0'
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
