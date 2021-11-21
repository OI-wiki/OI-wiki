FROM ubuntu:latest

# MAINTAINER frank-xjh "frank99-xu@outlook.com"

WORKDIR /
RUN apt-get update \
    && apt-get install -y git wget curl python3 python3-pip gcc g++ make \
	&& curl https://bootstrap.pypa.io/get-pip.py | python3 \
    && curl -sL https://deb.nodesource.com/setup_10.x | bash - \
    && apt-get install -y nodejs

RUN git clone https://hub.fastgit.org/OI-wiki/OI-wiki.git --depth=1 \
    && cd OI-wiki \
    && pip install -U -r requirements.txt \
    && npm install

ADD .bashrc /root/

WORKDIR /OI-wiki
EXPOSE 8000
CMD ["/bin/bash"]
