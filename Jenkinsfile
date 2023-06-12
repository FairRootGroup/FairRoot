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
    def check = spec.getOrDefault("check", null)
    def extra = spec.getOrDefault("extra", null)

    nodes[label] = {
      node(selector) {
        githubNotify(context: "${prefix}/${label}", description: 'Building ...', status: 'PENDING')
        def logpattern = 'build/Testing/Temporary/*.log'
        try {
          deleteDir()
          checkout scm

          if (check == "warnings" || check == "doxygen") {
            discoverGitReferenceBuild()
          }
          if (check == "doxygen") {
            gitDiffStat()
            // mineRepository()
          }

          def jobscript = 'job.sh'
          def ctestcmd = "ctest -S FairRoot_${type}_test.cmake -V --output-on-failure"
          sh "echo \"set -e\" >> ${jobscript}"
          if (type == 'check') {
            ctestcmd = "ctest -S FairRoot_${check}_test.cmake -VV"
            sh "echo \"export FAIRROOT_FORMAT_BASE=origin/\${CHANGE_TARGET}\" >> ${jobscript}"
          }
          if (extra) {
            ctestcmd = ctestcmd + " " + extra
          }
          if (selector =~ /^macos/) {
            sh "echo \"export SIMPATH=\$(brew --prefix fairsoft@${fairsoft})\" >> ${jobscript}"
          } else {
            sh "echo \"export SIMPATH=/fairsoft/${fairsoft}\" >> ${jobscript}"
          }
          sh "echo \"export LABEL=\\\"\${JOB_BASE_NAME} ${label}\\\"\" >> ${jobscript}"
          if (selector =~ /^macos/) {
            sh "echo \"${ctestcmd}\" >> ${jobscript}"
            sh "cat ${jobscript}"
            sh "bash ${jobscript}"
          } else {
            def container = "${os}.${ver}.sif"
            sh(label: "Create Slurm Job Script", script: """
              exec test/ci/slurm-create-jobscript.sh "${label}" "${container}" "${jobscript}" ${ctestcmd}
            """)
            sh "./test/ci/slurm-submit.sh \"FairRoot \${JOB_BASE_NAME} ${label}\" ${jobscript}"
          }
          if (check == "warnings") {
            recordIssues(tools: [clangTidy(pattern: logpattern)],
                         filters: [excludeFile('build/.*/G__.*[.]cxx')],
                         qualityGates: [[threshold: 3, type: 'NEW', unstable: true]],
                         ignoreFailedBuilds: false,
                         skipBlames: true)
            archiveArtifacts(artifacts: logpattern, allowEmptyArchive: true, fingerprint: true)
          }
          if (check == "doxygen") {
            recordIssues(tools: [doxygen()],
                         ignoreFailedBuilds: false,
                         skipBlames: true)
            def result_url = readFile(file: 'build/generated-doxygen.url')
            publishChecks(name: 'Doxygen-Preview',
                          title: 'Doxygen Preview',
                          summary: result_url)
          }

          deleteDir()
          githubNotify(context: "${prefix}/${label}", description: 'Success', status: 'SUCCESS')
        } catch (e) {
          if (check == "warnings") {
            archiveArtifacts(artifacts: logpattern, allowEmptyArchive: true, fingerprint: true)
          }
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
            [os: 'ubuntu',   ver: 'rolling', arch: 'x86_64', compiler: 'current',         fairsoft: 'dev',
                             check: 'warnings',
                             extra: '-DUSE_CLANG_TIDY=ON -DBUILD_MBS=OFF -DBUILD_PROOF_SUPPORT=OFF'],
          ])

          def checks = jobMatrix('alfa-ci', 'check', [
            [os: 'ubuntu',   ver: 'rolling', arch: 'x86_64', compiler: 'current',         fairsoft: 'dev',
                             check: 'doxygen'],
          ])
          if (env.CHANGE_ID != null) { // only run checks for PRs
            checks += jobMatrix('alfa-ci', 'check', [
              [os: 'ubuntu',   ver: 'rolling', arch: 'x86_64', compiler: 'current',         fairsoft: 'dev',
                               check: 'format'],
            ])
          }

          parallel(checks + builds)
        }
      }
    }
  }
}
