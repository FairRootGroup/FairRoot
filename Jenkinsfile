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
              sh '''\
                gcc --version
                cmake --version
                echo "export LINUX_FLAVOUR=Debian8" > Dart.cfg
                echo "export EXTRA_FLAGS=\\"-DCMAKE_CXX_COMPILER=g++;-DCMAKE_C_COMPILER=gcc\\" " >> Dart.cfg
                echo "export FAIRSOFT_VERSION=\${FAIRSOFT_VERSION}" >> Dart.cfg
                echo "export SIMPATH=${SIMPATH}" >> Dart.cfg;
                echo "export BUILDDIR=$PWD/build" >> Dart.cfg
                echo "export SOURCEDIR=$PWD" >> Dart.cfg
                echo "export SITE=\\"AlFa CI (lxbuild05.gsi.de)\\" " >> Dart.cfg
                echo "export PATH=$SIMPATH/bin:$PATH" >> Dart.cfg
                echo $PWD
                cat Dart.cfg
              '''
              sh "./Dart.sh Experimental Dart.cfg"
            }
          }
        )
      }
    }
  }
}

/* node { */
    /* try { */
    /*     stage('Test') { */
    /*         sh 'echo "Fail!"; exit 1' */
    /*     } */
    /*     echo 'This will run only if successful' */
    /* } catch (e) { */
    /*     echo 'This will run only if failed' */
    /*  */
    /*     // Since we're catching the exception in order to report on it, */
    /*     // we need to re-throw it, to ensure that the build is marked as failed */
    /*     throw e */
    /* } finally { */
    /*     def currentResult = currentBuild.result ?: 'SUCCESS' */
    /*     if (currentResult == 'UNSTABLE') { */
    /*         echo 'This will run only if the run was marked as unstable' */
    /*     } */
    /*  */
    /*     def previousResult = currentBuild.previousBuild?.result */
    /*     if (previousResult != null && previousResult != currentResult) { */
    /*         echo 'This will run only if the state of the Pipeline has changed' */
    /*         echo 'For example, if the Pipeline was previously failing but is now successful' */
    /*     } */
    /*  */
    /*     echo 'This will always run' */
    /* } */
/* } */
