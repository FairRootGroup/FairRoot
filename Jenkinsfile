#!groovy

pipeline{
  agent none
  stages {
    stage("Run Build/Test Matrix") {
      steps{
        parallel(
          'debian8-x86_64-gcc4.9-fairsoft_oct17': {
            node('debian8-x86_64-gcc4.9-fairsoft_oct17') {
              githubNotify(context: 'alfa-ci/debian8-x86_64-gcc4.9-fairsoft_oct17', description: 'Building ...', status: 'PENDING')
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
              timeout(60) {
                sh "./Dart.sh Experimental Dart.cfg"
              }
              githubNotify(context: 'alfa-ci/debian8-x86_64-gcc4.9-fairsoft_oct17', description: 'Success.', status: 'SUCCESS')
            }
          }
        )
      }
    }
  }
}
