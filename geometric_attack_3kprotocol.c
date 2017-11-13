/**
 * 
 * Simulation of 'geometric' security attack on the kkk protocol.
 * 
 * Author: Maduka Attamah
 * 
 * Copyright 2016 Maduka Attamah
 */

#include "3kprotocol.h"

#define EPOCH_LIMIT 150000000
#define SYNCHRONISATION_THRESHOLD 5

int main() {
    int k = 0;
    int n = 0;
    int l = 0;

    printf("Enter the value of k:");
    scanf("%d", &k);
    printf("Enter the value of n:");
    scanf("%d", &n);
    printf("Enter the value of l:");
    scanf("%d", &l);

    struct NeuralNetwork neuralNetA = constructNeuralNetwork(k, n, l);
    struct NeuralNetwork neuralNetB = constructNeuralNetwork(k, n, l);
    struct NeuralNetwork neuralNetC = constructNeuralNetwork(k, n, l);

    int** inputs = getRandomInputs(k, n);
    printf("\n==============BEFORE PROTOCOL RUN=======================\n");
    printNetworkWeights(neuralNetA, k, n);
    printf("\n=====================================\n");
    printNetworkWeights(neuralNetB, k, n);
    printf("\n=====================================\n");
    printNetworkWeights(neuralNetC, k, n);
    
     /*
     * To run the KKK Protocol normally (without any attacks), uncomment the call to function runKKKProtocol(...) below, 
     * and (optionally) comment out the call to function runGeometricAttackKKKProtocol(...) which follows.
     */

    // bool status = runKKKProtocol(neuralNetA, neuralNetB, inputs, k, n, l);
    bool status = runGeometricAttackKKKProtocol(neuralNetA, neuralNetB, neuralNetC, inputs, k, n, l, SYNCHRONISATION_THRESHOLD, EPOCH_LIMIT);

    printf("\n==============AFTER PROTOCOL RUN=======================\n");
    if (status == true) {
        printf("The networks are now synchronised after %d epochs!\n", epoch);
        printNetworkWeights(neuralNetA, k, n);
        printf("\n=====================================\n");
        printNetworkWeights(neuralNetB, k, n);
        printf("\n=====================================\n");
        printNetworkWeights(neuralNetC, k, n);
    } else {
        printNetworkWeights(neuralNetA, k, n);
        printf("\n=====================================\n");
        printNetworkWeights(neuralNetB, k, n);
        printf("\n=====================================\n");
        printNetworkWeights(neuralNetC, k, n);
        printf("Networks are unsynchronised after %d epochs.", EPOCH_LIMIT);
    }

    freeMemoryForNetwork(neuralNetA, k, n);
    freeMemoryForNetwork(neuralNetB, k, n);
    freeMemoryForNetwork(neuralNetC, k, n);
    free(inputs);
    return 0;
}











