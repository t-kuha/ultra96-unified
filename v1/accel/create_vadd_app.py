"""
Create vector addition app.

How to build:
    $ IDE_ZYNQMP_SYSROOT=<path to sysroot> vitis -s create_vadd_app.py
"""
import os
import shutil

import vitis

# settings
top_dir = os.path.dirname(os.path.abspath(__file__))
ws_dir = os.path.join(top_dir, '_vitis-ws')
pfm_dir = os.path.join(top_dir, '_pfm', 'u96_accel', 'export', 'u96_accel')

# check input
assert os.path.exists(pfm_dir)

if os.path.exists(ws_dir):
    print('[INFO] removing existing workspace...')
    shutil.rmtree(ws_dir) 

# start building
client = vitis.create_client()

status = client.set_workspace(path=ws_dir)
assert (status)
status = client.add_platform_repos(platform=pfm_dir)
assert (status)
proj = client.create_sys_project(
    name='vadd',
    platform=os.path.join(pfm_dir, 'u96_accel.xpfm'),
    template='installed_examples/vadd'
)
# add "--package.no_image" option
with open(os.path.join(ws_dir, 'vadd', 'package', 'package.cfg'), 'a') as file:
    file.write('\n')
    file.write('no_image=true')

# control num. of jobs
with open(os.path.join(ws_dir, 'vadd', 'hw_link', 'binary_container_1-link.cfg'), 'a') as file:
    file.write('\n\n')
    file.write('[vivado]\n')
    file.write('impl.jobs=4\n')
    file.write('synth.jobs=4\n')

proj.build(target='hw')

vitis.dispose()
