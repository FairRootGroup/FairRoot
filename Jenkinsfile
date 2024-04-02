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
    def image = spec.getOrDefault("image", null)

    nodes[label] = {
      node(selector) {
        githubNotify(context: "${prefix}/${label}", description: 'Building ...', status: 'PENDING')
        try {
          deleteDir()
          checkout scm

          if (check == "warnings") {
            discoverGitReferenceBuild()
          }

          def jobscript = 'job.sh'
          def ctestcmd = "ctest -S FairRoot_${type}_test.cmake -V --output-on-failure"
          sh "echo \"set -e\" >> ${jobscript}"
          if (type == 'check') {
            ctestcmd = "ctest -S FairRoot_${check}_test.cmake -VV"
            sh "echo \"export FAIRROOT_FORMAT_BASE=origin/\${CHANGE_TARGET}\" >> ${jobscript}"
          }
          if (selector =~ /^macos/) {
            // sh "echo \"export SIMPATH=\$(brew --prefix fairsoft)\" >> ${jobscript}"
          } else {
            sh "echo \"export SIMPATH=/fairsoft/${fairsoft}\" >> ${jobscript}"
          }
          if (selector =~ /^macos-10\.15/) {
            sh "echo \"export SDKROOT=\$(xcrun --show-sdk-path)\" >> ${jobscript}"
          }
          sh "echo \"export LABEL=\\\"\${JOB_BASE_NAME} ${label}\\\"\" >> ${jobscript}"
          if (selector =~ /^macos/) {
            sh "echo \"${ctestcmd}\" >> ${jobscript}"
            sh "cat ${jobscript}"
            sh "bash ${jobscript}"
          } else {
            def container = "${os}.${ver}.sif"
            if (image) {
              container = "${os}.${ver}.${image}.sif"
            }
            sh(label: "Create Slurm Job Script", script: """
              exec test/ci/slurm-create-jobscript.sh "${label}" "${container}" "${jobscript}" ${ctestcmd}
            """)
            sh "./test/ci/slurm-submit.sh \"FairRoot \${JOB_BASE_NAME} ${label}\" ${jobscript}"
          }
          if (check == "warnings") {
            recordIssues(tools: [clangTidy(pattern: logpattern)],
                         filters: [excludeFile('build/.*/G__.*[.]cxx'), excludeFile('third_party/.*')],
                         qualityGates: [[threshold: 4, type: 'NEW', unstable: true]],
                         ignoreFailedBuilds: false,
                         skipBlames: true)
            archiveArtifacts(artifacts: logpattern, allowEmptyArchive: true, fingerprint: true)
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
            [os: 'debian', ver: '10',      arch: 'x86_64', compiler: 'gcc-8',   fairsoft: 'jan24_patches',    image: 'jan24'],
            [os: 'debian', ver: '10',      arch: 'x86_64', compiler: 'gcc-8',   fairsoft: 'jan24_patches_mt', image: 'jan24'],
            [os: 'debian', ver: '10',      arch: 'x86_64', compiler: 'gcc-8',   fairsoft: 'nov22_patches',    image: 'nov22'],
            [os: 'debian', ver: '10',      arch: 'x86_64', compiler: 'gcc-8',   fairsoft: 'apr22_patches',    image: 'apr22'],
            [os: 'debian', ver: '11',      arch: 'x86_64', compiler: 'gcc-10',  fairsoft: 'jan24_patches',    image: 'jan24'],
            [os: 'debian', ver: '11',      arch: 'x86_64', compiler: 'gcc-10',  fairsoft: 'jan24_patches_mt', image: 'jan24'],
            [os: 'debian', ver: '11',      arch: 'x86_64', compiler: 'gcc-10',  fairsoft: 'nov22_patches',    image: 'nov22'],
            [os: 'debian', ver: '11',      arch: 'x86_64', compiler: 'gcc-10',  fairsoft: 'apr22_patches',    image: 'apr22'],
            [os: 'debian', ver: '12',      arch: 'x86_64', compiler: 'gcc-12',  fairsoft: 'jan24_patches',    image: 'jan24'],
            [os: 'debian', ver: '12',      arch: 'x86_64', compiler: 'gcc-12',  fairsoft: 'jan24_patches_mt', image: 'jan24'],
            [os: 'debian', ver: '12',      arch: 'x86_64', compiler: 'gcc-12',  fairsoft: 'nov22_patches',    image: 'nov22'],
            [os: 'fedora', ver: '39',      arch: 'x86_64', compiler: 'gcc-13',  fairsoft: 'jan24_patches',    image: 'jan24'],
            [os: 'fedora', ver: '39',      arch: 'x86_64', compiler: 'gcc-13',  fairsoft: 'jan24_patches_mt', image: 'jan24'],
            [os: 'ubuntu', ver: '20.04',   arch: 'x86_64', compiler: 'gcc-9',   fairsoft: 'jan24_patches',    image: 'jan24'],
            [os: 'ubuntu', ver: '20.04',   arch: 'x86_64', compiler: 'gcc-9',   fairsoft: 'jan24_patches_mt', image: 'jan24'],
            [os: 'ubuntu', ver: '20.04',   arch: 'x86_64', compiler: 'gcc-9',   fairsoft: 'nov22_patches',    image: 'nov22'],
            [os: 'ubuntu', ver: '20.04',   arch: 'x86_64', compiler: 'gcc-9',   fairsoft: 'apr22_patches',    image: 'apr22'],
            [os: 'ubuntu', ver: '22.04',   arch: 'x86_64', compiler: 'gcc-11',  fairsoft: 'jan24_patches',    image: 'jan24'],
            [os: 'ubuntu', ver: '22.04',   arch: 'x86_64', compiler: 'gcc-11',  fairsoft: 'jan24_patches_mt', image: 'jan24'],
            [os: 'ubuntu', ver: '22.04',   arch: 'x86_64', compiler: 'gcc-11',  fairsoft: 'nov22_patches',    image: 'nov22'],
            [os: 'ubuntu', ver: '22.04',   arch: 'x86_64', compiler: 'gcc-11',  fairsoft: 'apr22_patches',    image: 'apr22'],
            [os: 'ubuntu', ver: 'rolling', arch: 'x86_64', compiler: 'current', fairsoft: 'dev',
              check: 'warnings',
              extra: '-DUSE_CLANG_TIDY=ON -DBUILD_MBS=OFF -DBUILD_PROOF_SUPPORT=OFF'],
            [os: 'macos',  ver: '13',      arch: 'x86_64', compiler: 'apple-clang-14', fairsoft: '24.01'],
            [os: 'macos',  ver: '14',      arch: 'x86_64', compiler: 'apple-clang-14', fairsoft: '24.01'],
            [os: 'macos',  ver: '14',      arch: 'arm64',  compiler: 'apple-clang-15', fairsoft: '24.01'],
          ])

          checks = [:]
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
