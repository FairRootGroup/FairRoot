FROM anaderi/xfairsoft
MAINTAINER Andrey Ustyuzhanin andrey.ustyuzhanin@cern.ch

RUN mkdir /tmp/FairRoot
COPY . /tmp/FairRoot
WORKDIR /tmp/FairRoot
#COPY etc/profile-ship.sh /etc/profile.d/ship.sh
ENV FAIRROOTPATH=/opt/ocean/FairRootInst \
  SIMPATH=/opt/ocean/FairSoftInst\
  FAIRSHIP=/opt/ship/FairShip\
  FAIRSHIP_BLD=/opt/ship/FairShip/build\
  PYTHONPATH+=:$FAIRSHIP/python:$FAIRSHIP_BLD/python:$SIMPATH/lib:$SIMPATH/lib/Geant4
#COPY etc/yandex-etc-issue /etc/issue
RUN ./auto_build.sh
#RUN rm -rf /tmp/FairRoot
ENTRYPOINT ["/bin/sh", "-c", "-l"]
CMD ["bash"]
