#pragma once

#include "Headers.h"

#define Matrix Eigen::MatrixXf

/**
 * @brief Sigmoid function (Activation function) which takes an input and applies it in the equation
 *        1/1+exp(-x), returning the output
 *
 * @param float_x
 * @return (float) 1/1+exp(-x)
 */
float sigmoid(float x) { return 1 / (1 + exp(-x)); }

/**
 * @brief Differentiated Sigmoid
 *
 * @param float_x
 * @return (float) sigmoid(x) * (1 - sigmoid(x))
 */
float dSigmoid(float x) { return sigmoid(x) * (1 - sigmoid(x)); }

class ANN
{

private:
    std::vector<int> topology;
    std::vector<Matrix *> layers;
    std::vector<Matrix *> weights;

    float bias;
    float learningRate;

public:
    /**
     * @brief Construct a new ANN object
     *
     */
    ANN();

    /**
     * @brief Construct a new ANN object taking topology into account
     *
     * @param _topology
     */
    ANN(std::vector<int> _topology);

    /**
     * @brief Destroy the ANN object
     *
     */
    virtual ~ANN();

    /**
     * @brief initializes the layers of the ANN,
     *        creates an ith x 1 layer for each of the numbers sent
     *        in topology vector
     *
     * @param _topology
     */
    void init(std::vector<int> _topology);

    /**
     * @brief Places the input taken from the file in the first layer
     *
     * @param input
     */
    void initInput(Matrix &input);

    /**
     * @brief
     *
     * @param activateFunction
     * @return Matrix
     */

    /**
     * @brief Propogates Forward in the ANN
     *
     * @param activateFunction  Activation Function (Sigmoid)
     * @return Matrix ;Output value for the final layer in a matrix form
     */
    Matrix propogateForward(float (*activateFunction)(float));

    /**
     * @brief Propogates Backwards in the ANN
     *
     * @param targetValue
     * @param dFunction derivative of Activation Function (Sigmoid)
     */
    void propogateBackward(Matrix targetValue, float (*dFunction)(float));

    /**
     * @brief Sets the Learning Rate
     *
     * @param learningRate
     */
    void setLearningRate(float learningRate);

    /**
     * @brief Sets the Bias
     *
     * @param bias
     */
    void setBias(float bias);

    /**
     * @brief Trains the Neural Network for the data set provided
     *
     *
     */
    void train();

    /**
     * @brief Gets the Probability for a certain move
     *
     * @param currBoard
     * @param Positions
     * @param move
     * @return float
     */
    float getProbability(std::vector<float> currBoard, int Positions, int move);

    /**
     * @brief Gets the Best Move in a certain position
     *
     * @param currBoard
     * @param blankPositions
     * @param move
     * @return std::tuple<int, float>
     */
    std::tuple<int, float> getBestMove(std::vector<float> currBoard, std::vector<int> blankPositions, int move);
};

ANN::ANN()
{
    this->learningRate = 0.1f;
    this->bias = 0.5f;
}

ANN::ANN(std::vector<int> _topology)
{
    this->learningRate = 0.1f;
    this->bias = 0.5f;
    init(_topology);
}

ANN::~ANN()
{
    for (auto i : this->layers)
        delete i;

    for (auto i : this->weights)
        delete i;
}

void ANN::init(std::vector<int> _topology)
{
    this->topology = _topology;

    for (int i = 0; i < this->topology.size(); i++)
    {
        this->layers.push_back(new Matrix(this->topology[i], 1));

        if (i != 0)
        {
            this->weights.push_back(new Matrix(this->topology[i], this->topology[i - 1]));
            this->weights.back()->setRandom();
            *this->weights.back() += Matrix::Ones(this->topology[i], this->topology[i - 1]);
            std::cout << *this->weights.back() << std::endl
                      << std::endl;
        }
    }
}

void ANN::initInput(Matrix &input)
{
    *this->layers.front() = input;
}

Matrix ANN::propogateForward(float (*activationFunction)(float))
{
    for (int i = 1; i < this->topology.size(); i++)
    {
        *this->layers[i - 1] = this->layers[i - 1]->unaryExpr(activationFunction);

        if (i == this->topology.size() - 1)
            *this->layers[i] = (*this->weights[i - 1]) * (*this->layers[i - 1]);
        else
            *this->layers[i] = ((*this->weights[i - 1]) * (*this->layers[i - 1])) + (Matrix::Ones(this->topology[i], 1) * this->bias);
    }

    return *this->layers.back();
}

void ANN::propogateBackward(Matrix targetValue, float (*dFunction)(float))
{
    std::vector<Matrix> errors;

    // init errors
    for (auto i : this->topology)
    {
        errors.push_back(Matrix(i, 1));
        // errors.back().setZero();
    }

    // calculating errors
    errors.back() = *this->layers.back() - targetValue;
    for (int i = this->topology.size() - 2; i > 0; i--)
        errors[i] = this->weights[i]->transpose() * errors[i + 1];

    // changing weights
    Matrix deltaWeight;
    for (int i = 0; i < this->topology.size() - 1; i++)
    {
        deltaWeight = this->layers[i + 1]->unaryExpr(dFunction) * errors[i].transpose();
        *this->weights[i] -= deltaWeight * learningRate;
    }
}

void ANN::setLearningRate(float learningRate)
{
    this->learningRate = learningRate;
}

void ANN::setBias(float bias)
{
    this->bias = bias;
}

void ANN::train()
{

    std::cout << "TRAINING HAS STARTED\n\n";

    getInput getinput;

    for (int i = 1; i < 958; i++)
    {
        float output;
        getinput.getInput_(i);

        Matrix input(9, 1);
        input << getinput.INP[0], getinput.INP[1], getinput.INP[2], getinput.INP[3], getinput.INP[4],
            getinput.INP[5], getinput.INP[6], getinput.INP[7], getinput.INP[8];
        Matrix target(1, 1);
        target << getinput.target;

        std::cout << this->propogateForward(sigmoid);
        output = this->propogateForward(sigmoid).norm();
        while (abs(getinput.target - output) > 0.05)
        {
            output = this->propogateForward(sigmoid).norm();
            this->propogateBackward(target, dSigmoid);
        }
        std::cout << "\n";
        std::cout << i << "  " << output << std::endl;
    }

    std::cout << "TRAINING HAS ENDED\n\n";
}

float ANN::getProbability(std::vector<float> currBoard, int Position, int move)
{

    currBoard[Position] = move;

    Matrix tempBoard(9, 1);
    tempBoard << currBoard[0], currBoard[1], currBoard[2], currBoard[3], currBoard[4],
        currBoard[5], currBoard[6], currBoard[7], currBoard[8];

    this->initInput(tempBoard);
    return this->propogateForward(sigmoid).norm();
}

std::tuple<int, float> ANN::getBestMove(std::vector<float> currBoard, std::vector<int> blankPositions, int move)
{
    int pos;
    float highestProbability;

    if (move == -1)
        highestProbability = 10;
    else
        highestProbability = -10;

    for (auto i : blankPositions)
    {
        float moveProbability = this->getProbability(currBoard, i, move);
        if (move == -1)
        {
            if (moveProbability < highestProbability)
            {
                pos = i;
                highestProbability = moveProbability;
            }
        }
        else
        {
            if (moveProbability > highestProbability)
            {
                pos = i;
                highestProbability = moveProbability;
            }
        }
    }

    return make_tuple(pos, highestProbability);
}