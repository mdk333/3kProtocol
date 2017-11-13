
/**
 * 
 * Simulation of 'genetic' security attack on the kkk protocol.
 * 
 * Author: Maduka Attamah
 * 
 * Copyright 2016 Maduka Attamah
 */


#include "3kprotocol.h"

#define GENETIC_SYNCHRONISATION_THRESHOLD 1
#define GENETIC_EPOCH_LIMIT 1000000

int main() {
    int k = 0;
    int n = 0;
    int l = 0;
    int m = 0;

    printf("Enter the value of k:");
    scanf("%d", &k);
    printf("Enter the value of n:");
    scanf("%d", &n);
    printf("Enter the value of l:");
    scanf("%d", &l);
    printf("Enter the value of m:");
    scanf("%d", &m);

    struct NeuralNetwork neuralNetA = constructNeuralNetwork(k, n, l);
    struct NeuralNetwork neuralNetB = constructNeuralNetwork(k, n, l);
    struct NeuralNetwork attackNeuralNetworks[1]; //Start with one attack network.
    attackNeuralNetworks[0] = constructNeuralNetwork(k, n, l);

    int** inputs = getRandomInputs(k, n);
    printf("\n==============BEFORE PROTOCOL RUN=======================\n");
    printNetworkWeights(neuralNetA, k, n);
    printf("\n=====================================\n");
    printNetworkWeights(neuralNetB, k, n);
    printf("\n=====================================\n");
    printNetworkWeights(attackNeuralNetworks[0], k, n);

    /*
     * To run the KKK Protocol normally (without any attacks), uncomment the call to function runKKKProtocol(...) below, 
     * and comment out the call to function runGenenticAttackKKKProtocol(...) which follows.  To run the attack in 'offline'
     * mode the call to runGenenticAttackKKKProtocol(...) can come after the runKKKProtocol(...), but then you ought to modify 
     * (or create another version of) the function runGenenticAttackKKKProtocol(...) to not update the weights of
     * neuralNetA and neuralNetB during the attack.
     */
    
    // bool status = runKKKProtocol(neuralNetA, neuralNetB, inputs, k, n, l);
    bool status = runGeneticAttackKKKProtocol(neuralNetA, neuralNetB, attackNeuralNetworks, inputs, k, n, l, m, GENETIC_SYNCHRONISATION_THRESHOLD, GENETIC_EPOCH_LIMIT);

    printf("\n==============AFTER PROTOCOL RUN=======================\n");
    if (status == true) {
        printf("The networks are now synchronised after %d epochs!\n", epoch);
        printNetworkWeights(neuralNetA, k, n);
        printf("\n=====================================\n");
        printNetworkWeights(neuralNetB, k, n);
        printf("\n=====================================\n");
        printf("\n===We have the following attack neural networks status*********");
        for (int i = 0; i < sizeof (attackNeuralNetworks); i++) {
            printNetworkWeights(attackNeuralNetworks[i], k, n);
        }
    } else {
        printNetworkWeights(neuralNetA, k, n);
        printf("\n=====================================\n");
        printNetworkWeights(neuralNetB, k, n);
        printf("\n=====================================\n");
        printf("\n===We have the following attack neural networks status*********");
        for (int i = 0; i < sizeof (attackNeuralNetworks); i++) {
            printNetworkWeights(attackNeuralNetworks[i], k, n);
        }
        printf("Networks are unsynchronised after %d epochs.", GENETIC_EPOCH_LIMIT);
    }
    
    freeMemoryForNetwork(neuralNetA, k, n);
    freeMemoryForNetwork(neuralNetB, k, n);
    
    for (int i = 0; i < sizeof (attackNeuralNetworks); i++) {
        freeMemoryForNetwork(attackNeuralNetworks[i], k, n);
    }
    
    free(inputs);
    return 0;
}



