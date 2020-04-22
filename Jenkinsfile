#!groovy

def specToLabel(Map spec) {
  return "${spec.os}-${spec.arch}-${spec.compiler}-FairSoft_${spec.fairsoft}"
}

def jobMatrix(String prefix, String type, List specs, Closure callback) {
  def nodes = [:]
  for (spec in specs) {
    def label = specToLabel(spec)
    def os = spec.os
    def compiler = spec.compiler
    def fairsoft = spec.fairsoft
    def job = label
    if (spec.containsKey('check')) {
      job = spec.check
    }
    nodes["${type}/${job}"] = {
      node(label) {
        githubNotify(context: "${prefix}/${type}/${job}", description: 'Building ...', status: 'PENDING')
        try {
          deleteDir()
          checkout scm

          def env = ''
          if (spec.containsKey('check')) {
            env = 'env.sh'
            if (os =~ /Debian8/) {
              sh """\
                echo "#!/bin/bash" >> ${env}
                echo ". /etc/profile.d/modules.sh" >> ${env}
                echo "module use /cvmfs/it.gsi.de/modulefiles" >> ${env}
                echo "module load cmake" >> ${env}
                echo "module load compiler/gcc/9.1.0" >> ${env}
              """
            }
            sh """\
              echo "export SIMPATH=\${SIMPATH_PREFIX}${fairsoft}" >> ${env}
              echo "export LABEL='\${JOB_BASE_NAME} ${spec.check}'" >> ${env}
              echo "export PATH=\${CHECKS_PREFIX}${spec.check}/bin:\\\$PATH" >> ${env}
            """
          } else {
            env = 'Dart.cfg'
            sh """\
              echo "export SIMPATH=\${SIMPATH_PREFIX}${fairsoft}" >> ${env}
              echo "export FAIRSOFT_VERSION=${fairsoft}" >> ${env}
            """

            if (os =~ /Debian8/ && compiler =~ /gcc9/) {
              sh """\
                echo ". /etc/profile.d/modules.sh" >> ${env}
                echo "module use /cvmfs/it.gsi.de/modulefiles" >> ${env}
                echo "module load compiler/gcc/9.1.0" >> ${env}
              """
            }

            if (os =~ /MacOS/) {
              sh "echo \"export EXTRA_FLAGS=\\\"-DCMAKE_CXX_COMPILER=clang++;-DCMAKE_C_COMPILER=clang\\\"\" >> ${env}"
            } else {
              sh "echo \"export EXTRA_FLAGS=\\\"-DCMAKE_CXX_COMPILER=g++;-DCMAKE_C_COMPILER=gcc\\\"\" >> ${env}"
            }

            sh """\
              echo "export BUILDDIR=\${PWD}/build" >> ${env}
              echo "export SOURCEDIR=\${PWD}" >> ${env}
              echo "export PATH=\\\$SIMPATH/bin:\\\$PATH" >> ${env}
              echo "export GIT_BRANCH=\${JOB_BASE_NAME}" >> ${env}
              echo "echo \\\$PATH" >> ${env}
            """
          }
          sh "cat ${env}"

          callback.call(spec, job, env)

          deleteDir()
          githubNotify(context: "${prefix}/${type}/${job}", description: 'Success', status: 'SUCCESS')
        } catch (e) {
          deleteDir()
          githubNotify(context: "${prefix}/${type}/${job}", description: 'Error', status: 'ERROR')
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
          def builds = jobMatrix('alfa-ci', 'build', [
            [os: 'Debian8',    arch: 'x86_64', compiler: 'gcc9',            fairsoft: 'dev'],
            [os: 'Debian8',    arch: 'x86_64', compiler: 'gcc9',            fairsoft: 'dev_mt'],
            [os: 'MacOS10.13', arch: 'x86_64', compiler: 'AppleLLVM10.0.0', fairsoft: 'dev'],
            [os: 'MacOS10.13', arch: 'x86_64', compiler: 'AppleLLVM10.0.0', fairsoft: 'dev_mt'],
            [os: 'MacOS10.13', arch: 'x86_64', compiler: 'AppleLLVM10.0.0', fairsoft: 'jun19_patches'],
            [os: 'MacOS10.13', arch: 'x86_64', compiler: 'AppleLLVM10.0.0', fairsoft: 'jun19_patches_mt'],
            [os: 'MacOS10.14', arch: 'x86_64', compiler: 'AppleLLVM10.0.0', fairsoft: 'dev'],
            [os: 'MacOS10.14', arch: 'x86_64', compiler: 'AppleLLVM10.0.0', fairsoft: 'dev_mt'],
          ]) { spec, label, config ->
            sh "./Dart.sh alfa_ci ${config}"
          }

          def checks = jobMatrix('alfa-ci', 'check', [
            [os: 'Debian8', arch: 'x86_64', compiler: 'gcc9', fairsoft: 'dev', check: 'format'],
          ]) { spec, check, env ->
            sh ". ./${env} && ctest -S FairRoot_${check}_test.cmake -VV"
          }

          parallel(checks + builds)
        }
      }
    }
  }
}
