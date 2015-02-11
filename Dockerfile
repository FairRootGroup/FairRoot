FROM anaderi/xfairsoft
MAINTAINER Andrey Ustyuzhanin andrey.ustyuzhanin@cern.ch
#ENTRYPOINT ["/bin/sh", "-c", "-l"]
#CMD ["bash"]
#RUN yum install -y bc
#ENV SHIPSOFT /opt/xocean
#ENV FAIRROOTPATH $SHIPSOFT/FairRootInst
#ENV SIMPATH $SHIPSOFT/FairSoftInst
#ENV FAIRSHIP /opt/ship/FairShip
#ENV FAIRSHIP_BLD $FAIRSHIP/build
#ENV PYTHONPATH $FAIRSHIP/python:$FAIRSHIP_BLD/python:$SIMPATH/lib:$SIMPATH/lib/Geant4

RUN mkdir /tmp/FairRoot
COPY . /tmp/FairRoot
WORKDIR /tmp/FairRoot
RUN ./auto_build.sh cleanup
WORKDIR /root
