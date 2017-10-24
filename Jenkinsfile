#!groovy

pipeline{
  agent none
  stages {
    stage("Run Build/Test Matrix") {
      steps{
        parallel(
          'debian8-gcc4.9-fairsoft_oct17': {
            node('debian8-gcc4.9-fairsoft_oct17') {
              checkout scm
              sh "env"
              sh '''\
                gcc --version
                cmake --version
                echo "export LINUX_FLAVOUR=${LINUX_FLAVOUR}" > Dart.cfg
                echo "export EXTRA_FLAGS=\\"-DCMAKE_CXX_COMPILER=g++;-DCMAKE_C_COMPILER=gcc\\" " >> Dart.cfg
                echo "export FAIRSOFT_VERSION=\${FAIRSOFT_VERSION}" >> Dart.cfg
                echo "export SIMPATH=${SIMPATH}" >> Dart.cfg;
                echo "export BUILDDIR=$PWD/build" >> Dart.cfg
                echo "export SOURCEDIR=$PWD" >> Dart.cfg
                echo "export PATH=$SIMPATH/bin:$PATH" >> Dart.cfg
                echo "export GIT_BRANCH=$JOB_BASE_NAME" >> Dart.cfg
                echo $PWD
                cat Dart.cfg
              '''
              sh "env"
              sh "./Dart.sh Experimental Dart.cfg"
            }
          }
        )
      }
    }
  }
}
