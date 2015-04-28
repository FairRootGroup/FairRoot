FROM anaderi/fairsoft

RUN yum -y install python-mtTkinter.noarch
RUN mkdir /tmp/FairRoot
COPY . /tmp/FairRoot
RUN cd /tmp/FairRoot && \
  ./auto_build.sh cleanup
WORKDIR /root
