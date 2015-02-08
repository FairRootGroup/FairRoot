FROM anaderi/xfairsoft
MAINTAINER Andrey Ustyuzhanin andrey.ustyuzhanin@cern.ch

RUN mkdir /tmp/FairRoot
COPY . /tmp/FairRoot
WORKDIR /tmp/FairRoot
COPY etc/profile-ship.sh /etc/profile.d/ship.sh
COPY etc/yandex-etc-issue /etc/issue
RUN ./auto_build.sh
#RUN rm -rf /tmp/FairRoot
ENTRYPOINT ["/bin/sh", "-c", "-l"]
CMD ["bash"]
