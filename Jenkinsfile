pipeline {
    agent any

    tools {
        'hudson.plugins.cmake.CmakeTool' 'cmake' // Name of the CMake installation configured in Jenkins
    }

    stages {

        stage('Clean Workspace') {
            steps {
                deleteDir() // Clean the workspace before checking out
            }
        }

        stage('Checkout') {
            steps {
                checkout([
                    $class: 'GitSCM', 
                    branches: [[name: '*/main']], 
                    doGenerateSubmoduleConfigurations: True, 
                    extensions: [[$class: 'CleanCheckout'], [$class: 'SubmoduleOption', recursiveSubmodules: true]], // Ensures a clean checkout
                    userRemoteConfigs:  scm.userRemoteConfigs
                ])
            }
        }

        stage('Build') {
            steps {
                script {
                    // Use the CMake installation configured in Jenkins
                    withEnv(["PATH+CM=${tool name: 'cmake'}/bin"]) {
                        // Create a build directory
                        sh 'mkdir -p build'
                        dir('build') {
                            // Run CMake to configure the build system
                            sh 'cmake ..'
                            // Build the project
                            sh 'cmake --build .'
                        }
                    }
                }
            }
        }

        stage('Test') {
            steps {
                script {
                    dir('build') {
                        // Run tests
                        sh 'ctest'
                    }
                }
            }
        }
    }

    post {
        always {
            // Clean up build directory after the build
            deleteDir()
        }
    }
}
