#!/usr/bin/env bash
set -euo pipefail
exec script -q -e -c 'make -C /home/ksrtakosar/CFU-Playground/proj/mnist_fusion_sim_20261014_130437 load PLATFORM=sim BUILD_JOBS=4 OUT_DIR=build/sim.mnist_fusion_sim_20261014_130437' /home/ksrtakosar/MNIST_CFU_FUSION_20261013_V1/revisions/MNIST_STEP10_SIM/results/mnist_fusion_sim_20261014_130437/simulation_console.log
