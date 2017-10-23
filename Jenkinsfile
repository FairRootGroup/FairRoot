def buildMatrix(List specs, Closure callback) {
    def builds = [:]
    for (spec in specs) {
        def label = "${spec.os}-${spec.compiler}"
        builds[label] = { callback.call(label) }
    }

    return builds
}
 
//if(env.BRANCH_NAME ==~ /^PR.*/) {

node {
    parallel buildMatrix([
        [os: 'debian8', compiler: 'gcc4.9']
    ]) { label ->
        node("${label}") {
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

//}
