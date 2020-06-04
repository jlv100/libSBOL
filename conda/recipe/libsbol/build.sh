set -x

mkdir -p $PREFIX/lib
mkdir -p $PREFIX/lib/python$PY_VER/sbol

cd $SRC_DIR
git submodule update --init --recursive

cp ${PREFIX}/include/raptor2/* ${PREFIX}/include/

cmake \
    -DCMAKE_INSTALL_PREFIX="${PREFIX}" \
    -DCMAKE_INSTALL_LIBDIR="${PREFIX}/lib" \
    -DCMAKE_PREFIX_PATH="${PREFIX}" \
    -DCMAKE_INCLUDE_PATH="${PREFIX}/include" \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    -DLIBXSLT_INCLUDE_DIR="${PREFIX}/include/libxslt" \
    -DRAPTOR_DIR="${PREFIX}" \
    -DRAPTOR_INCLUDE_DIR="${PREFIX}/include/raptor2" \
    -DRAPTOR_LIBRARY="${PREFIX}/lib" \
    -DRASQAL_INCLUDE_DIR="${PREFIX}/include/rasqal" \
    -DRASQAL_LIBRARY="${PREFIX}/lib" \
    -DJsonCpp_LIBRARIES="${PREFIX}/lib/json" \
    -DJsonCpp_INCLUDE_DIRS="${PREFIX}/include/json" \
    -DSBOL_BUILD_PYTHON3=TRUE \
    -DSBOL_BUILD_JSON=FALSE \
    -DSBOL_BUILD_RASQAL=FALSE \
    -DPYTHON_INCLUDE_DIR=$(python -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())") \
    -DPYTHON_LIBRARY=$(python -c "import distutils.sysconfig as sysconfig; import os; print(os.path.join(sysconfig.get_config_var('LIBDIR'), sysconfig.get_config_var('LDLIBRARY')))") \
    .

make install

cp -r release/wrapper/Linux_64_3/sbol/* $PREFIX/lib/python$PY_VER/sbol/
#cp -r test __init__.py libsbol.py sbol.py unit_tests.py _libsbol.so $PREFIX/lib/python$PY_VER/sbol/
