# Set environment variable for Vitis
export XILINX_XRT=/usr

if [ -e /media/card/dpu.xclbin ]; then
    echo "Copying dpu.xclbin..."
    cp /media/card/dpu.xclbin /usr/lib
fi
