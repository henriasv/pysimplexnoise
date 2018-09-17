from setuptools import Extension, setup
import os
import numpy

extension = Extension("pysimplexnoise", 
            ['SimplexNoise/src/SimplexNoise.cpp', "pysimplexnoise.cpp"],
            include_dirs = ["SimplexNoise/src", numpy.get_include()],
            extra_compile_args = ["-std=c++11"]
            )

setup(
    name='pysimplexnoise',
    description='Create simplex noise',
    classifiers=[
        "Development Status :: 4 - Beta",
        "Intended Audience :: Developers",
        "Programming Language :: Python",
        "Programming Language :: Python :: 3",
        "Programming Language :: c++"
        ],
    license='MIT',
    packages=[],
    ext_modules=[extension],
    install_requires=['numpy'],
    )
