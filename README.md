# Sensitivity computation using Vibrato Monte Carlo and automatic differentiation

## References: 

See papers [PPS15], and [Gil09].

[[PPS15](https://arxiv.org/abs/1606.06143)] Vibrato and automatic differentiation for high order derivatives and
sensitivities of financial options

[[Gil09](https://link.springer.com/chapter/10.1007/978-3-642-04107-5_23)] Vibrato Monte Carlo Sensitivities

## Prerequisites

For automatic differentiation, we use `autodiff`. It can be installed by following the below steps:

1. Download the library:

    - Using git
      ```
      git clone https://github.com/autodiff/autodiff
      ```
    - Downloading the zip file [ici](https://github.com/autodiff/autodiff/archive/master.zip).

2. Installation:
   Requires admin privileges, otherwise save it in a local folder.

```bash
cd autodiff
mkdir .build && cd .build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
sudo cmake --build . --target install
```

Requirements:

1. `eigne3`:

- Under MacOs run `brew install eigen`
- Under Linux :
    - Fedora : `sudo dnf install eigen3-devel`
    - Debian : `sudo apt install libeigen3-dev`

2. `Catch2`:

```bash
git clone https://github.com/catchorg/Catch2.git
cd Catch2
cmake -Bbuild -H. -DBUILD_TESTING=OFF
sudo cmake --build build/ --target install 
```

3. `pybind11`

- Under Linux:
    - Debian : `sudo apt install pybind11-dev`
    - Fedora : `sudo dnf install pybind11-devel`

For more information check: [autodiff](https://autodiff.github.io/).

## Compilation & execution:

A `Makefile` file contain all the predefined commands that can be run. All the binaries are in `vibrato-mc/bin`.


## Example of outputs:

### Vanilla options:

![Vanilla](src/python/outputs/vibrato_vanilla.pdf "Vanilla Call premium and greeks")


### Digital options:

![Digital](src/python/outputs/vibrato_digital.pdf "Digital Call premium and greeks")