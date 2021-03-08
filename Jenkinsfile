#!groovy

def jobMatrix(String prefix, String type, List specs) {
  def nodes = [:]
  for (spec in specs) {
    def job = ''
    switch(type) {
      case 'build':
        job = "${spec.os}-${spec.ver}-${spec.arch}-${spec.compiler}-fairsoft-${spec.fairsoft}"
        break
      case 'check':
        job = spec.check
        break
    }
    def label = "${type}/${job}"
    def selector = "${spec.os}-${spec.ver}-${spec.arch}"
    def fairsoft = spec.fairsoft
    def os = spec.os
    def ver = spec.ver
    def arch = spec.arch
    def check = spec.check

    nodes[label] = {
      node(selector) {
        githubNotify(context: "${prefix}/${label}", description: 'Building ...', status: 'PENDING')
        try {
          deleteDir()
          checkout scm

          def jobscript = 'job.sh'
          def ctestcmd = "ctest -S FairRoot_${type}_test.cmake -V --output-on-failure"
          sh "echo \"set -e\" >> ${jobscript}"
          if (type == 'check') {
            ctestcmd = "ctest -S FairRoot_${check}_test.cmake -VV"
            sh "echo \"export FAIRROOT_FORMAT_BASE=origin/\${CHANGE_TARGET}\" >> ${jobscript}"
          }
          if (selector =~ /^macos/) {
            sh "echo \"export SIMPATH=\$(brew --prefix fairsoft@${fairsoft})\" >> ${jobscript}"
          } else if (selector =~/^gsi-debian/ && ver == '8') {
            sh "echo \"export SIMPATH=/cvmfs/fairsoft.gsi.de/debian8/fairsoft/${fairsoft}\" >> ${jobscript}"
          } else {
            sh "echo \"export SIMPATH=/fairsoft/${fairsoft}\" >> ${jobscript}"
          }
          sh "echo \"export LABEL=\\\"\${JOB_BASE_NAME} ${label}\\\"\" >> ${jobscript}"
          if (selector =~ /^macos/) {
            sh "echo \"${ctestcmd}\" >> ${jobscript}"
            sh "cat ${jobscript}"
            sh "bash ${jobscript}"
          } else {
            def containercmd = "singularity exec -B/shared ${env.SINGULARITY_CONTAINER_ROOT}/fairroot/${os}.${ver}.sif bash -l -c \\\"${ctestcmd}\\\""
            if (selector =~/^gsi-debian/ && ver == '8') {
              containercmd = "singularity exec -B/shared,/cvmfs ${env.SINGULARITY_CONTAINER_ROOT}/fairroot/${os}.${ver}.sif bash -l -c \\\"spack load gcc@8; spack load cmake arch=${arch}; ${ctestcmd}\\\""
            }
            sh """\
              echo \"echo \\\"*** Job started at .......: \\\$(date -R)\\\"\" >> ${jobscript}
              echo \"echo \\\"*** Job ID ...............: \\\${SLURM_JOB_ID}\\\"\" >> ${jobscript}
              echo \"echo \\\"*** Compute node .........: \\\$(hostname -f)\\\"\" >> ${jobscript}
              echo \"unset http_proxy\" >> ${jobscript}
              echo \"unset HTTP_PROXY\" >> ${jobscript}
              echo \"${containercmd}\" >> ${jobscript}
            """
            sh "cat ${jobscript}"
            sh "./slurm-submit.sh \"FairRoot \${JOB_BASE_NAME} ${label}\" ${jobscript}"
          }

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
          def builds = jobMatrix('alfa-ci', 'build', [
            [os: 'centos',     ver: '7',     arch: 'x86_64', compiler: 'gcc-7',           fairsoft: 'nov20_patches'],
            [os: 'centos',     ver: '7',     arch: 'x86_64', compiler: 'gcc-7',           fairsoft: 'nov20_patches_mt'],
            [os: 'debian',     ver: '10',    arch: 'x86_64', compiler: 'gcc-8',           fairsoft: 'nov20_patches'],
            [os: 'debian',     ver: '10',    arch: 'x86_64', compiler: 'gcc-8',           fairsoft: 'nov20_patches_mt'],
            [os: 'gsi-debian', ver: '8',     arch: 'x86_64', compiler: 'gcc-8',           fairsoft: 'nov20'],
            [os: 'macos',      ver: '10.15', arch: 'x86_64', compiler: 'apple-clang-11',  fairsoft: '20.11'],
            [os: 'macos',      ver: '11',    arch: 'x86_64', compiler: 'apple-clang-12',  fairsoft: '20.11'],
          ])

          def checks = [:]
          if (env.CHANGE_ID != null) { // only run checks for PRs
            checks = jobMatrix('alfa-ci', 'check', [
              [os: 'debian', ver: '10', arch: 'x86_64', check: 'format', fairsoft: 'nov20_patches'],
            ])
          }

          parallel(checks + builds)
        }
      }
    }
  }
}
