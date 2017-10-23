#!groovy

Set available = []
for (slave in jenkins.model.Jenkins.instance.getNodes()) {
    if (slave.toComputer().isOnline()) {
        available.plus(slave.getAssignedLabels())
    }
}

def nodeSpecToLabel(Map spec) {
    return "${spec.os}-${spec.compiler}-${spec.fairsoft}"
}

def nodeSpecs(List specs, Closure callback) {
    def nodes = [:]
    for (spec in specs) {
        def label = nodeSpecToLabel(spec)
        if(available.find { it == label}) {
            nodes[label] = { callback.call(spec) }
        }
    }
    return nodes
}

pipeline{
    agent none
    stages {
        stage("Run Build/Test Matrix") {
            steps{
                parallel(nodeSpecs([
                    [os: 'debian8', compiler: 'gcc4.9', fairsoft: 'oct17'],
                ]) { spec ->
                    timeout(60) {
                        node(nodeSpecToLabel(spec)) {
                            sh "sleep 5"
                        }
                    }
                })
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
