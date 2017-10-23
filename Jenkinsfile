def buildMatrix(List specs, Closure callback) {
    def stages = [:]
    for (spec in specs) {
        stages["${spec.os}-${spec.compiler}"] = { callback.call(spec) }
    }

    return stages
}
 
if(env.BRANCH_NAME ==~ /^PR.*/) {

pipeline {
    agent none

    parallel buildMatrix([
        [os: 'debian8', compiler: 'gcc4.9']
    ]) { spec ->
        stage {
            stages {
                stage("pre") {
                    script { setGitHubPullRequestStatus(context: "hui", message: "bla bla", state: 'PENDING') }
                }
                stage("configure") {
                    sh "sleep 5"
                }
                stage("build") {
                    sh "sleep 5"
                }
                stage("test") {
                    sh "sleep 5"
                }
                stage("post") {
                    script { setGitHubPullRequestStatus(context: "hui", message: "bla bla", state: 'SUCCESS') }
                }
            }
        }
    }
}

}
