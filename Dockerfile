FROM ubuntu:22.04

LABEL org.oi-wiki.image.authors="frank99-xu@outlook.com mxr612@icloud.com coelacanthus@outlook.com"

ARG WIKI_REPO PYPI_MIRROR LISTEN_IP LISTEN_PORT
ENV LISTEN_IP=${LISTEN_IP:-0.0.0.0}
ENV LISTEN_PORT=${LISTEN_PORT:-8000}

WORKDIR /
RUN apt-get update \
    && apt-get install -y git wget curl pipenv gcc g++ make \
    && curl -sL https://deb.nodesource.com/setup_18.x | bash - \
    && apt-get install -y nodejs

# If you can't connect to GitHub, set WIKI_REPO to any mirror repo.
RUN git clone ${WIKI_REPO:-https://github.com/OI-wiki/OI-wiki.git} --depth=1 \
    && cd OI-wiki \
    && pipenv install --pypi-mirror ${PYPI_MIRROR:-https://pypi.org/simple/} \
    && yarn --frozen-lockfile

ADD .bashrc /root/

WORKDIR /OI-wiki
EXPOSE ${LISTEN_PORT}
CMD ["/bin/bash"]
