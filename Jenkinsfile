#!groovy

def specToLabel(Map spec) {
  return "${spec.os}-${spec.arch}-${spec.compiler}-FairSoft_${spec.fairsoft}"
}

def jobMatrix(String prefix, List specs, Closure callback) {
  def nodes = [:]
  for (spec in specs) {
    def label = specToLabel(spec)
    def os = spec.os
    def compiler = spec.compiler
    def fairsoft = spec.fairsoft
    nodes["${prefix}/${label}"] = {
      node(label) {
        githubNotify(context: "${prefix}/${label}", description: 'Building ...', status: 'PENDING')
        try {
          deleteDir()
          checkout scm

          sh """\
            echo "export SIMPATH=\${SIMPATH_PREFIX}${fairsoft}" >> Dart.cfg
            echo "export FAIRSOFT_VERSION=${fairsoft}" >> Dart.cfg
          """

          if (os =~ /Debian8/ && compiler =~ /gcc8/) {
            sh '''\
              echo "source /etc/profile.d/modules.sh" >> Dart.cfg
              echo "module use /cvmfs/it.gsi.de/modulefiles" >> Dart.cfg
              echo "module load compiler/gcc/8.1.0" >> Dart.cfg
            '''
          }

          if (os =~ /MacOS/) {
            sh "echo \"export EXTRA_FLAGS=\\\"-DCMAKE_CXX_COMPILER=clang++;-DCMAKE_C_COMPILER=clang\\\"\" >> Dart.cfg"
          } else {
            sh "echo \"export EXTRA_FLAGS=\\\"-DCMAKE_CXX_COMPILER=g++;-DCMAKE_C_COMPILER=gcc\\\"\" >> Dart.cfg"
          }

          sh '''\
            echo "export BUILDDIR=$PWD/build" >> Dart.cfg
            echo "export SOURCEDIR=$PWD" >> Dart.cfg
            echo "export PATH=\\\$SIMPATH/bin:\\\$PATH" >> Dart.cfg
            echo "export GIT_BRANCH=$JOB_BASE_NAME" >> Dart.cfg
            echo "echo \\\$PATH" >> Dart.cfg
          '''
          sh 'cat Dart.cfg'

          callback.call(spec, label)

          deleteDir()
          githubNotify(context: "${prefix}/${label}", description: 'Success', status: 'SUCCESS')
        } catch (e) {
          deleteDir()
          githubNotify(context: "${prefix}/${label}", description: 'Error', status: 'ERROR')
          throw e
        }
      }
    }
  }
  return nodes
}

pipeline{
  agent none
  stages {
    stage("Run CI Matrix") {
      steps{
        script {
          def build_jobs = jobMatrix('alfa-ci/build', [
            [os: 'Debian8',    arch: 'x86_64', compiler: 'gcc8.1.0',        fairsoft: 'dev'],
            [os: 'Debian8',    arch: 'x86_64', compiler: 'gcc8.1.0',        fairsoft: 'dev_mt'],
            [os: 'MacOS10.13', arch: 'x86_64', compiler: 'AppleLLVM10.0.0', fairsoft: 'dev'],
            [os: 'MacOS10.13', arch: 'x86_64', compiler: 'AppleLLVM10.0.0', fairsoft: 'dev_mt'],
            [os: 'MacOS10.14', arch: 'x86_64', compiler: 'AppleLLVM10.0.0', fairsoft: 'dev'],
            [os: 'MacOS10.14', arch: 'x86_64', compiler: 'AppleLLVM10.0.0', fairsoft: 'dev_mt'],
          ]) { spec, label ->
            sh './Dart.sh alfa_ci Dart.cfg'
          }

          parallel(build_jobs)
        }
      }
    }
  }
}
