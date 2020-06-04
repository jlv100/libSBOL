FROM continuumio/miniconda3


RUN conda install -y conda-build anaconda-client conda-verify
RUN conda update -y conda-build

WORKDIR /
COPY recipe/libsbol/* libSBOL/

RUN conda config --append channels vanhemertjohn --append channels conda-forge --append channels ptorrestr

RUN conda build libSBOL

RUN echo "anaconda login && anaconda upload --force /opt/conda/conda-bld/linux-64/libsbol*.tar.bz2" > publish.sh
