pipeline {
    agent any

    tools {
        'hudson.plugins.cmake.CmakeTool' 'cmake' // Name of the CMake installation configured in Jenkins
    }

    environment {
        SCANNER_HOME = tool 'sonar'
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

        stage('SonarQube Analysis') {
            steps {
                withSonarQubeEnv('sonarcloud') {
                    withCredentials([string(credentialsId: 'SONAR_TOKEN', variable: 'SONAR_TOKEN')]) {
                        sh '''${SCANNER_HOME}/bin/sonar-scanner \
                            -Dsonar.token=${SONAR_TOKEN} \
                            -Dsonar.organization=panizolledotangel-1 \
                            -Dsonar.projectKey=panizolledotangel_c_devops_test \
                            -Dsonar.sources=./src \
                            -Dsonar.language=c 
                        '''
                    }
                }   
            }
        }

        stage('Quality Gate') {
            steps {
                script {
                    timeout(time: 1, unit: 'HOURS') {
                        def qg = waitForQualityGate()
                        if (qg.status != 'OK') {
                            error "Pipeline aborted due to quality gate failure: ${qg.status}"
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
                        sh 'ctest --verbose'
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
