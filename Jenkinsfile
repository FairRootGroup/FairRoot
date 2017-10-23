def buildMatrix(List specs, Closure callback) {
    def builds = [:]
    for (spec in specs) {
        builds["${spec.os}-${spec.compiler}"] = { callback.call(spec) }
    }

    return builds
}
 
//if(env.BRANCH_NAME ==~ /^PR.*/) {

pipeline {
    agent any

    stages {
        stage("distribute") {
            script {
                parallel buildMatrix([
                    [os: 'debian8', compiler: 'gcc4.9']
                ]) { spec ->
                    stage("${spec}") {
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
    }
}

//}
