#!groovy

def macos_builds = [
  [os: "macos",  ver: "13", arch: "x86_64", compiler: "apple-clang-14", fairsoft: "24.01"],
  [os: "macos",  ver: "14", arch: "x86_64", compiler: "apple-clang-14", fairsoft: "24.01"],
  [os: "macos",  ver: "14", arch: "arm64",  compiler: "apple-clang-15", fairsoft: "24.01"],
]

def linux_builds = [
  [os: "debian", ver: "10",      compiler: "gcc-8",   fairsoft: "jan24_patches",    image: "jan24"],
  [os: "debian", ver: "10",      compiler: "gcc-8",   fairsoft: "jan24_patches_mt", image: "jan24"],
  [os: "debian", ver: "10",      compiler: "gcc-8",   fairsoft: "nov22_patches",    image: "nov22"],
  [os: "debian", ver: "10",      compiler: "gcc-8",   fairsoft: "apr22_patches",    image: "apr22"],
  [os: "debian", ver: "11",      compiler: "gcc-10",  fairsoft: "jan24_patches",    image: "jan24"],
  [os: "debian", ver: "11",      compiler: "gcc-10",  fairsoft: "jan24_patches_mt", image: "jan24"],
  [os: "debian", ver: "11",      compiler: "gcc-10",  fairsoft: "nov22_patches",    image: "nov22"],
  [os: "debian", ver: "11",      compiler: "gcc-10",  fairsoft: "apr22_patches",    image: "apr22"],
  [os: "debian", ver: "12",      compiler: "gcc-12",  fairsoft: "jan24_patches",    image: "jan24"],
  [os: "debian", ver: "12",      compiler: "gcc-12",  fairsoft: "jan24_patches_mt", image: "jan24"],
  [os: "debian", ver: "12",      compiler: "gcc-12",  fairsoft: "nov22_patches",    image: "nov22"],
  [os: "fedora", ver: "39",      compiler: "gcc-13",  fairsoft: "jan24_patches",    image: "jan24"],
  [os: "fedora", ver: "39",      compiler: "gcc-13",  fairsoft: "jan24_patches_mt", image: "jan24"],
  [os: "ubuntu", ver: "20.04",   compiler: "gcc-9",   fairsoft: "jan24_patches",    image: "jan24"],
  [os: "ubuntu", ver: "20.04",   compiler: "gcc-9",   fairsoft: "jan24_patches_mt", image: "jan24"],
  [os: "ubuntu", ver: "20.04",   compiler: "gcc-9",   fairsoft: "nov22_patches",    image: "nov22"],
  [os: "ubuntu", ver: "20.04",   compiler: "gcc-9",   fairsoft: "apr22_patches",    image: "apr22"],
  [os: "ubuntu", ver: "22.04",   compiler: "gcc-11",  fairsoft: "jan24_patches",    image: "jan24"],
  [os: "ubuntu", ver: "22.04",   compiler: "gcc-11",  fairsoft: "jan24_patches_mt", image: "jan24"],
  [os: "ubuntu", ver: "22.04",   compiler: "gcc-11",  fairsoft: "nov22_patches",    image: "nov22"],
  [os: "ubuntu", ver: "22.04",   compiler: "gcc-11",  fairsoft: "apr22_patches",    image: "apr22"],
]

def linux_checks = [
  [os: "ubuntu", ver: "rolling", compiler: "current", fairsoft: "dev", check: "warnings",
    extra: "-DUSE_CLANG_TIDY=ON -DBUILD_MBS=OFF -DBUILD_PROOF_SUPPORT=OFF"],
]

if (env.CHANGE_ID != null) { // only run checks for PRs
  linux_checks += [
    [os: "ubuntu", ver: "rolling", compiler: "current", fairsoft: "dev",  check: "format"]
  ]
}

def jobMatrix(String type, String sourcedir, List specs) {
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
          if (!sourcedir) {
            deleteDir()
            checkout scm
            sourcedir = pwd()
          }
          def builddir = "${pwd()}/build-${os}-${ver}-${arch}-${fairsoft}"
          echo "Source dir: ${sourcedir}"
          echo "Build dir: ${builddir}"

          if (check == "warnings") {
            discoverGitReferenceBuild()
          }

          def jobscript = "job.sh"
          def ctestcmd = "ctest -S ${sourcedir}/FairRoot_${type}_test.cmake -V --output-on-failure"
          sh "echo \"set -e\" >> ${jobscript}"
          if (type == "check") {
            ctestcmd = "ctest -S ${sourcedir}/FairRoot_${check}_test.cmake -VV"
            sh "echo \"export FAIRROOT_FORMAT_BASE=origin/\${CHANGE_TARGET}\" >> ${jobscript}"
          }
          ctestcmd += " -DCTEST_SOURCE_DIRECTORY='${sourcedir}' -DCTEST_BINARY_DIRECTORY='${builddir}'"
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
              exec ${sourcedir}/test/ci/slurm-create-jobscript.sh "${label}" "${container}" "${jobscript}" ${ctestcmd}
            """)
            sh "${sourcedir}/test/ci/slurm-submit.sh \"FairRoot \${JOB_BASE_NAME} ${label}\" ${jobscript}"
          }

          if (check == "warnings") {
            recordIssues(tools: [clangTidy(pattern: logpattern)],
                         filters: [excludeFile("build/.*/G__.*[.]cxx"), excludeFile("third_party/.*")],
                         qualityGates: [[threshold: 4, type: "NEW", unstable: true]],
                         ignoreFailedBuilds: false,
                         skipBlames: true)
            archiveArtifacts(artifacts: logpattern, allowEmptyArchive: true, fingerprint: true)
          }

          deleteDir()
          githubNotify(context: "${label}", description: "Success", status: "SUCCESS")
        } catch (e) {
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
          steps { script { parallel(  jobMatrix("build", linux_source, linux_builds)
                                    + jobMatrix("check", linux_source, linux_checks)) } }
          post { always { dir(linux_source) { deleteDir() } } } } } }
    stage("macOS") { steps { script { parallel(jobMatrix("build", null, macos_builds)) } } } } } } }
