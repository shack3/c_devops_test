pipeline {
    agent any

    tools {
        cmake 'cmake' // Name of the CMake installation configured in Jenkins
    }

    stages {
        stage('Checkout') {
            steps {
                // Checkout code from version control including submodules using the scm variable
                checkout([
                    $class: 'GitSCM', 
                    branches: [[name: '*/main']],
                    extensions: [[$class: 'SubmoduleOption', recursiveSubmodules: true]], 
                    userRemoteConfigs: scm.userRemoteConfigs
                ])
            }
        }

        stage('Build') {
            steps {
                withCMake(cmake: 'hudson.plugins.cmake.CmakeTool') { // Use the CMake installation configured in Jenkins
                    script {
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
