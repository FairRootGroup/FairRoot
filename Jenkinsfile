#!groovy

def macos_builds = [
]

def linux_builds = [
  [os: "ubuntu", ver: "rolling", compiler: "current", fairsoft: "dev", check: "warnings",
    extra: "-DUSE_CLANG_TIDY=ON -DBUILD_MBS=OFF -DBUILD_PROOF_SUPPORT=OFF"],
]

def linux_checks = [
]

def isBranchBuild() {
  return !env.CHANGE_ID
}

if (!isBranchBuild()) { // PRs only
  linux_checks += [
    [os: "ubuntu", ver: "rolling", compiler: "current", fairsoft: "dev",  check: "format"]
  ]
}

def jobMatrix(String type, String src, List specs) {
  def nodes = [:]
  for (spec in specs) {
    def arch = spec.getOrDefault("arch", "x86_64")
    def check = spec.getOrDefault("check", null)
    def extra = spec.getOrDefault("extra", null)
    def image = spec.getOrDefault("image", null)
    def fairsoft = spec.fairsoft
    def os = spec.os
    def ver = spec.ver
    def compiler = spec.compiler
    def selector = "${os}-${ver}-${arch}"
    def label = ""
    switch(type) {
      case "build":
        label = "${os}-${ver}-${arch} ${compiler} ${fairsoft}"
        break
      case "check":
        label = "Check ${check}"
        break
    }

    nodes[label] = {
      node(selector) {
        githubNotify(context: "${label}", description: "Building ...", status: "PENDING")
        try {
          def sourcedir = src
          if (!sourcedir) {
            deleteDir()
            checkout scm
            sourcedir = pwd()
          }
          def builddir = "build-${os}-${ver}-${arch}-${fairsoft}"
          def builddir_abs = "${pwd()}/${builddir}"
          echo "Source dir: ${sourcedir}"
          echo "Build dir: ${builddir_abs}"
          def logpattern = "${builddir}/Testing/Temporary/*.log"

          if (check == "warnings" || check == "doxygen") {
            discoverGitReferenceBuild()
          }
          if (check == "doxygen") {
            gitDiffStat()
            // mineRepository()
          }

          def jobscript = "${pwd()}/job.sh"
          def ctestcmd = "ctest -S ${sourcedir}/FairRoot_${type}_test.cmake -V --output-on-failure"
          sh "echo \"set -e\" >> ${jobscript}"
          if (type == "check") {
            ctestcmd = "ctest -S ${sourcedir}/FairRoot_${check}_test.cmake -VV"
            sh "echo \"export FAIRROOT_FORMAT_BASE=origin/\${CHANGE_TARGET}\" >> ${jobscript}"
          }
          if (isBranchBuild() && !(os =~ /^macos/)) {
            ctestcmd += " -DENABLE_GEANT3_TESTING=ON"
          }
          if (extra) {
            ctestcmd = ctestcmd + " " + extra
          }
          ctestcmd += " -DCTEST_SOURCE_DIRECTORY='${sourcedir}' -DCTEST_BINARY_DIRECTORY='${builddir_abs}'"
          if (selector =~ /^macos/) {
            // sh "echo \"export SIMPATH=\$(brew --prefix fairsoft)\" >> ${jobscript}"
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
            if (image) {
              container = "${os}.${ver}.${image}.sif"
            }
            sh(label: "Create Slurm Job Script", script: """
              exec ${sourcedir}/tests/ci/slurm-create-jobscript.sh "${label}" "${container}" "${jobscript}" ${ctestcmd}
            """)
            dir(sourcedir) {
              sh "tests/ci/slurm-submit.sh \"${type}\" \"FairRoot \${JOB_BASE_NAME} ${label}\" ${jobscript}"
            }
          }

          if (check == "warnings") {
            recordIssues(tools: [clangTidy(pattern: logpattern)],
                         filters: [excludeFile("build.*/.*/G__.*[.]cxx"), excludeFile("third_party/.*")],
                         qualityGates: [[threshold: 4, type: "NEW", unstable: true]],
                         ignoreFailedBuilds: false,
                         skipBlames: true)
            archiveArtifacts(artifacts: logpattern, allowEmptyArchive: true, fingerprint: true)
          }
          if (check == "doxygen") {
            recordIssues(tools: [doxygen()],
                         ignoreFailedBuilds: false,
                         skipBlames: true)
            def result_url = readFile(file: "${builddir_abs}/generated-doxygen.url")
            publishChecks(name: "Doxygen-Preview",
                          title: "Doxygen Preview",
                          summary: result_url)
          }

          deleteDir()
          githubNotify(context: "${label}", description: "Success", status: "SUCCESS")
        } catch (e) {
          if (check == "warnings") {
            archiveArtifacts(artifacts: logpattern, allowEmptyArchive: true, fingerprint: true)
          }
          deleteDir()
          githubNotify(context: "${label}", description: "Error", status: "ERROR")
          throw e
        }
      }
    }
  }
  return nodes
}

def linux_source = ""

pipeline {
  agent none
  options { skipDefaultCheckout() }
  stages { stage("CI") { parallel {
    stage("Linux") {
      agent { label "slurm" }
      stages {
        stage("SCM Checkout") {
          steps {
            checkout scm
            script { linux_source = pwd() }
            echo "Source dir: ${linux_source}" } }
        stage("Builds and Checks") {
          steps { script { parallel(  jobMatrix("check", linux_source, linux_checks)
                                    + jobMatrix("build", linux_source, linux_builds)) } }
          post { always { dir(linux_source) { deleteDir() } } } } } }
    stage("macOS") { steps { script { parallel(jobMatrix("build", null, macos_builds)) } } } } } } }
