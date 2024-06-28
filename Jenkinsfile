pipeline {
    agent any

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

        stage('Test') {
            steps {
                script {
                    dir('build') {
                        // Run tests
                        sh 'ctest -c Debug'
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
