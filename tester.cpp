#include "Headers.h"
#include "eigenANN.h"
#include "getFileInput.h"

#define Matrix Eigen::MatrixXf

float setOne() { return 1.f; }

int main(){
    enum moves {o = -1, b, x};
    std::vector<float> testInput = {x,o,b,x,b,b,b,x,o};
    std::vector<int> topology = {9, 5, 2, 1};


    ANN ai(topology);
    ai.setLearningRate(0.5);
    ai.setBias(0.f);


    getInput getinput;

    Matrix input(9, 1);
    Matrix target(1, 1);

    for(int i = 622; i <= 631; i++){
        getinput.getInput_(i);
        input << getinput.INP[0], getinput.INP[1], getinput.INP[2], getinput.INP[3], getinput.INP[4], 
                getinput.INP[5], getinput.INP[6], getinput.INP[7], getinput.INP[8]; 
        target << getinput.target;
        // target << 0.f;

        for(int i = 0; i < 10; i++){
            std::cout << ai.propogateForward(sigmoid) <<"123123123\n"<< std::endl;
            ai.propogateBackward(target, dSigmoid);
        }
        std::cout << "\n\n\n\n";
    }

    std::cout << "\n\n\n\n";
    std::cout << "\n\n\n\n";

     input << testInput[0], testInput[1], testInput[2], testInput[3], testInput[4], 
                testInput[5], testInput[6], testInput[7], testInput[8];
    
    std::cout << ai.propogateForward(sigmoid) << std::endl << std::endl;
}
