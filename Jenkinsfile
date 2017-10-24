#!groovy

pipeline{
  agent none
  stages {
    stage("Run Build/Test Matrix") {
      steps{
        parallel(
          'Debian8-x86_64-gcc4.9-FairSoft_oct17': {
            node('Debian8-x86_64-gcc4.9-FairSoft_oct17') {
              githubNotify(context: 'alfa-ci/Debian8-x86_64-gcc4.9-FairSoft_oct17', description: 'Building ...', status: 'PENDING')
              script { try {
                deleteDir()
                checkout scm
                sh 'gcc --version'
                sh 'cmake --version'
                sh 'echo $PWD'
                sh '''\
                  echo "export BUILDDIR=$PWD/build" >> Dart.cfg
                  echo "export SOURCEDIR=$PWD" >> Dart.cfg
                  echo "export PATH=$SIMPATH/bin:$PATH" >> Dart.cfg
                  echo "export GIT_BRANCH=$JOB_BASE_NAME" >> Dart.cfg
                '''
                sh "env"
                sh "./Dart.sh Experimental Dart.cfg"
                githubNotify(context: 'alfa-ci/Debian8-x86_64-gcc4.9-FairSoft_oct17', description: 'Success', status: 'SUCCESS', targetUrl: 'https://cdash.gsi.de/index.php?project=FairRoot')
              } catch (e) {
                githubNotify(context: 'alfa-ci/Debian8-x86_64-gcc4.9-FairSoft_oct17', description: 'Error', status: 'ERROR', targetUrl: 'https://cdash.gsi.de/index.php?project=FairRoot')
                throw e
              }}
            }
          },
          'MacOS10.11-x86_64-AppleLLVM8.0.0-FairSoft_oct17': {
            node('MacOS10.11-x86_64-AppleLLVM8.0.0-FairSoft_oct17') {
              githubNotify(context: 'alfa-ci/MacOS10.11-x86_64-AppleLLVM8.0.0-FairSoft_oct17', description: 'Building ...', status: 'PENDING')
              script { try {
                deleteDir()
                checkout scm
                sh 'clang --version'
                sh 'cmake --version'
                sh 'echo $PWD'
                sh '''\
                  echo "export BUILDDIR=$PWD/build" >> Dart.cfg
                  echo "export SOURCEDIR=$PWD" >> Dart.cfg
                  echo "export PATH=$SIMPATH/bin:$PATH" >> Dart.cfg
                  echo "export GIT_BRANCH=$JOB_BASE_NAME" >> Dart.cfg
                '''
                sh "env"
                sh "./Dart.sh Experimental Dart.cfg; echo $?"
                githubNotify(context: 'alfa-ci/MacOS10.11-x86_64-AppleLLVM8.0.0-FairSoft_oct17', description: 'Success', status: 'SUCCESS', targetUrl: 'https://cdash.gsi.de/index.php?project=FairRoot')
              } catch (e) {
                githubNotify(context: 'alfa-ci/MacOS10.11-x86_64-AppleLLVM8.0.0-FairSoft_oct17', description: 'Error', status: 'ERROR', targetUrl: 'https://cdash.gsi.de/index.php?project=FairRoot')
                throw e
              }}
            }
          }
        )
      }
    }
  }
}
