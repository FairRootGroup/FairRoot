#!groovy

def specToLabel(Map spec) {
  return "${spec.os}-${spec.arch}-${spec.compiler}-FairSoft_${spec.fairsoft}"
}

def buildSteps(Map args) {
  deleteDir()
  checkout scm

  sh 'cmake --version'
  sh 'echo $PWD'
  sh '''\
    echo "export BUILDDIR=$PWD/build" >> Dart.cfg
    echo "export SOURCEDIR=$PWD" >> Dart.cfg
    echo "export PATH=$SIMPATH/bin:$PATH" >> Dart.cfg
    echo "export GIT_BRANCH=$JOB_BASE_NAME" >> Dart.cfg
  '''
  sh 'env'
  sh './Dart.sh Experimental Dart.cfg'
}

def withGithubNotifications(Map args, Closure callback) {
  def cdashUrl = 'https://cdash.gsi.de/index.php?project=FairRoot#!#Experimental'
  githubNotify(context: "alfa-ci/${label}", description: 'Building ...', status: 'PENDING')
  try {
    callback.call()
    githubNotify(context: "alfa-ci/${label}", description: 'Success', status: 'SUCCESS', targetUrl: cdashUrl)
  } catch (e) {
    githubNotify(context: "alfa-ci/${label}", description: 'Error', status: 'ERROR', targetUrl: cdashUrl)
    throw e
  }
}

def buildMatrix(List specs) {
  def nodes = [:]
  for (spec in specs) {
    def label = specToLabel(spec)
    nodes[label] = { 
      node(label) {
        withGithubNotifications(cdashUrl: cdashUrl) {
          buildSteps(spec: spec, label: label)
        }
      }
    }
  }
  return nodes
}

pipeline{
  agent none
  stages {
    stage("Run Build/Test Matrix") {
      steps{
        script {
          parallel(buildMatrix([
            [os: 'Debian8',    arch: 'x86_64', compiler: 'gcc4.9',         fairsoft: 'oct17'],
            [os: 'MacOS10.11', arch: 'x86_64', compiler: 'AppleLLVM8.0.0', fairsoft: 'oct17'],
          ])
        }
      }
    }
  }
}
