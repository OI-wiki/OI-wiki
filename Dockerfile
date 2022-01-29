FROM ubuntu:latest

LABEL org.oi-wiki.image.authors="frank99-xu@outlook.com mxr612@icloud.com coelacanthus@outlook.com"

WORKDIR /
RUN apt-get update \
    && apt-get install -y git wget curl python3 python3-pip gcc g++ make \
	&& curl https://bootstrap.pypa.io/get-pip.py | python3 \
    && curl -sL https://deb.nodesource.com/setup_10.x | bash - \
    && apt-get install -y nodejs

# If you can't connect to GitHub, set WIKI_REPO to any mirror repo.
RUN git clone ${WIKI_REPO:-https://github.com/OI-wiki/OI-wiki.git} --depth=1 \
    && cd OI-wiki \
    && pip install -U -r requirements.txt \
    && npm install

ADD .bashrc /root/

WORKDIR /OI-wiki
EXPOSE 8000
CMD ["/bin/bash"]
