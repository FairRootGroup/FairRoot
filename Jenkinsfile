def nodeSpecs(List specs, Closure callback) {
    def nodes = [:]
    for (spec in specs) {
        nodes["${spec}"] = { callback.call(spec) }
    }
     
    return nodes
}
 
stage("Run Build/Test Matrix") {
    parallel nodeSpecs([
        [os: 'debian8', compiler: 'gcc4.9', fairsoft: 'oct17'],
        [os: 'fedora26', compiler: 'gcc7.2', fairsoft: 'oct17'],
    ]) { spec -> 
        node {
            stage("Configure ${spec}") {
                sh "sleep 5"
            }
            stage("Build ${spec}") {
                sh "sleep 5"
            }
            stage("Test ${spec}") {
                sh "sleep 5"
            }
        }
    }
}

/* node { */
    /* try { */
    /*     stage('Test') { */
    /*         sh 'echo "Fail!"; exit 1' */
    /*     } */
    /*     echo 'This will run only if successful' */
    /* } catch (e) { */
    /*     echo 'This will run only if failed' */
    /*  */
    /*     // Since we're catching the exception in order to report on it, */
    /*     // we need to re-throw it, to ensure that the build is marked as failed */
    /*     throw e */
    /* } finally { */
    /*     def currentResult = currentBuild.result ?: 'SUCCESS' */
    /*     if (currentResult == 'UNSTABLE') { */
    /*         echo 'This will run only if the run was marked as unstable' */
    /*     } */
    /*  */
    /*     def previousResult = currentBuild.previousBuild?.result */
    /*     if (previousResult != null && previousResult != currentResult) { */
    /*         echo 'This will run only if the state of the Pipeline has changed' */
    /*         echo 'For example, if the Pipeline was previously failing but is now successful' */
    /*     } */
    /*  */
    /*     echo 'This will always run' */
    /* } */
/* } */
