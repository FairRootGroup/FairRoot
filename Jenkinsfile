/* def nodeSpecs(List specs, Closure callback) { */
/*     def nodes = [:] */
/*     for (spec in specs) { */
/*         nodes["${spec}"] = { callback.call(spec) } */
/*     } */
/*       */
/*     return nodes */
/* } */
 
// if(env.BRANCH_NAME ==~ /^PR.*/) {
pipeline {
    /* parallel nodeSpecs([ */
    /*     [os: 'debian8', compiler: 'gcc4.9'] */
    /* ]) { spec ->  */
        node {

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
    /* } */
}
