'''Create acceleration platform for Vitis AI.
'''
import os
import shutil
import vitis

PFM_NAME = 'u96_vai'
top_dir = os.path.dirname(__file__)
pfm_dir = os.path.join(top_dir, '_pfm')
# boot_dir = os.path.join(top_dir, '_boot')
sd_dir = os.path.join(top_dir, '_sd_dir')
petalinux_dir = os.path.join(top_dir, 'petalinux', 'images', 'linux')
hw_xsa_path = os.path.join(top_dir, 'hw.xsa')
hw_emu_xsa_path = os.path.join(top_dir, 'hw_emu.xsa')

# prepare required files
for d in [pfm_dir, sd_dir]:
    if os.path.exists(d):
        shutil.rmtree(d)
    os.mkdir(d)

for fn in ['boot.scr', 'image.ub']:
    shutil.copy(os.path.join(petalinux_dir, fn), sd_dir)

# generate platform
client = vitis.create_client()
client.set_workspace(path=pfm_dir)

platform = client.create_platform_component(
    name=PFM_NAME, hw=hw_xsa_path, desc='Ultra96 v1 platform',
    os='linux', cpu='psu_cortexa53', no_boot_bsp=True,
    emulation_xsa_path=hw_emu_xsa_path
)

domain = platform.get_domain(name='linux_psu_cortexa53')
status = domain.update_name(new_name='xrt')
assert status
status = domain.add_bif(os.path.join(top_dir, 'src', 'linux.bif'))
# status = domain.generate_bif()
assert status
status = domain.add_boot_dir(petalinux_dir)
assert status
status = domain.set_sd_dir(sd_dir)
assert status
platform = client.get_platform_component(name=PFM_NAME)

platform.remove_boot_bsp()
status = platform.build()

print('----- domain.report')
domain.report()
print('----- platform.report')
platform.report()
