class Function {
  public:
    int index;
    Function(int i) {
      index = i;
    }
    static float apply(float N, float parameters[], int i, int j, int Index) {
      float result = 0;
      switch (Index) {
        case 0: //double
          result = sigmoid(N, parameters, i, j);
          break;
        case 1: //half
          result = dSigmoid(N, parameters, i, j);
          break;
        case 2:
          result = multiply(N, parameters, i, j);
          break;
        default:
          break;
      }
      return result;
    }

    static float sigmoid(float N, float parameters[], int i, int j) {
      float e = 2.71828;
      float y;
      y = 1.0 / (1.0 + pow(e, -N));
      return y;
    }

    static float dSigmoid(float N, float parameters[], int i, int j) {
      return N * (1 - N);
    }

    static float multiply(float N, float parameters[], int i, int j) {
      float scaler = parameters[0];
      return N * scaler;
    }
};

Function sigmoid(0);
Function dSigmoid(1);
Function multiply(2);

class Array {
  public:
    String name = "array";
    int length = -1;
    float* data;

    Array() {}

    Array(String name_) {
      name = name_;
    }

    Array(int length_) {
      constructor(length_);
    }

    Array(float a[], int arrayLength) {
      constructor(a, arrayLength);
    }
    /*
        Array(float* a, int arrayLength) {
          length = arrayLength;
          data = (float*)calloc(length, sizeof(float));
          for (int i = 0; i < length; i++) data[i] = a[i];
        }
    */
    Array(Array* a) {
      if (length != -1)remove();
      length = a->length;
      data = (float*)calloc(length, sizeof(float));
      for (int i = 0; i < length; i++) data[i] = a->data[i];
    }

    Array(float** matrixData, int matrixRows, int matrixCols, String name_) { //no memory loss
      length = matrixRows * matrixCols;
      data = (float*)calloc(length, sizeof(float));
      name = name_;

      for (int i = 0; i < matrixRows; i++) {
        for (int j = 0; j < matrixCols; j++) {
          data[i * matrixCols + j] = matrixData[i][j];
        }
      }
    }

    void constructor(int length_) {
      length = length_;
      data = (float*)calloc(length, sizeof(float));
      for (int i = 0; i < length; i++) data[i] = 0;
    }

    void constructor(float a[], int arrayLength) {
      length = arrayLength;
      data = (float*)calloc(length, sizeof(float));
      for (int i = 0; i < length; i++) data[i] = a[i];
    }
    /*
        void constructor(float* a, int arrayLength) {
          length = arrayLength;
          data = (float*)calloc(length,sizeof(float));
          for(int i = 0; i < length; i++) data[i] = a[i];
        }
    */
    void setTo(Array* a) {
      if (length != -1)remove();
      length = a->length;
      data = (float*)calloc(length, sizeof(float));
      for (int i = 0; i < length; i++) data[i] = a->data[i];
    }

    void setTo(float a[], int arrayLength) {
      if (length != -1)remove();
      constructor(a, arrayLength);
    }

    void remove() {
      free(data);
    }

    void setName(String name_) {
      name = name_;
    }

    void  matrixToArray(float** matrixData, int matrixRows, int matrixCols) { //no memory loss
      if (length != -1) free(data);
      length = matrixRows * matrixCols;
      data = (float*)calloc(length, sizeof(float));

      for (int i = 0; i < matrixRows; i++) {
        for (int j = 0; j < matrixCols; j++) {
          data[i * matrixCols + j] = matrixData[i][j];
        }
      }
    }

    void printOut() { //checked
      Serial.print("float " + name + " [] = \n{");
      for (int i = 0; i < length; i++) {
        Serial.print(data[i]);
        if (i < length - 1) Serial.print(", ");
      }
      Serial.println("};");
    }
};

Array input_Arrayq;
Array output_Arrayq;

/////////////////////////////////////////////////////////////////////  MATRIX
class Matrix {
  public:
    int rows = -1, cols = -1;
    float** data;
    String name = "matrix";

    Matrix() {}

    Matrix(String name_) {
      name = name_;
      //mem2();
      //info();
    }

    Matrix(int rows_, int cols_) { //checked
      MatrixConstructor(rows_, cols_, name);
      //mem2();
      //info();
    }

    Matrix(int rows_, int cols_, String name_) { //checked
      MatrixConstructor(rows_, cols_, name_);
      //mem2();
      //info();
    }

    Matrix(Matrix* a, String name_) {
      name = name_;
      setTo(a);
      //mem2();
      //info();
    }

    Matrix(Array* a, String name_) {
      name = name_;
      setTo(a);
      //mem2();
      //info();
    }

    void MatrixConstructor(int rows_, int cols_) { //checked
      MatrixConstructor(rows_, cols_, name);
    }

    void MatrixConstructor(int rows_, int cols_, String name_) { //checked
      rows = rows_;
      cols = cols_;
      data = (float**)calloc(rows, sizeof(float*));
      for (int i = 0; i < rows; i++) {
        float* myArray = (float*)calloc(cols, sizeof(float));
        data[i] = myArray;
      }
      for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) data[i][j] = 0;
      name = name_;
      //Serial.println(name + " " + String(rows) + " " + String(cols));
      //mem2();
      //info();
      //Serial.println(freeMemory());
    }

    void setTo(Matrix* a) { //checked
      if (rows != -1) {
        for (int i = 0; i < rows; i++) free(data[i]);
        free(data);
      }
      MatrixConstructor(a->rows, a->cols);
      for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) data[i][j] = a->data[i][j];
    }

    void setTo(Array* a) { //checked
      if (rows != -1) {
        for (int i = 0; i < rows; i++) free(data[i]);
        free(data);
      }
      MatrixConstructor(a->length, 1);
      for (int i = 0; i < a->length; i++) data[i][0] = a->data[i];
    }


    void arrayToRow(int row, float myArray[]) {
      for (int i = 0; i < rows; i++) data[row][i] = myArray[i];
    }

    //Array*

    void remove() { //checked
      if (rows != -1) {
        for (int i = 0; i < rows; i++) free(data[i]);
        free(data);
      }
    }

    void setName(String name_) { //checked
      name = name_;
    }

    void randomise() { //checked
      for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) data[i][j] = myRandom(-1, 1, 6);
    }

    void randomise(float first, float last, int precision) {
      for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) data[i][j] = myRandom(first, last, precision);
    }

    void multiply(float scaler) { //checked
      for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) data[i][j] *= scaler;
    }

    void multiply(Matrix* a) {
      if (rows != a-> rows || cols != a-> cols) {
        Serial.println("Size mismatch in multiply(Matrix* a): \n rows_" + a->name + ": " + String(a->rows) + "  cols_" + a->name + ": " + String(a->cols));
        delay(1000);
        while (true) {};
      }
      for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) data[i][j] *= a->data[i][j];
    }

    void add(float add) {
      for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) data[i][j] += add;
    }

    void add(Matrix* a) {
      if (rows != a-> rows || cols != a-> cols) {
        Serial.println("Size mismatch in add(Matrix* a): \n rows_" + a->name + ": " + String(a->rows) + "  cols_" + a->name + ": " + String(a->cols));
        delay(1000);
        while (true) {}
      }
      for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) data[i][j] += a->data[i][j];
    }

    void map(Function* f, float parameters[]) {
      for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) data[i][j] = f->apply(data[i][j], parameters, i, j, f->index);
    }
    void map(Function* f, float a) { //checked
      float parameters[] = {a};
      for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) data[i][j] = f->apply(data[i][j], parameters, i, j, f->index);
    }
    void map(Function* f) {
      float parameters[] = {};
      for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) data[i][j] = f->apply(data[i][j], parameters, i, j, f->index);
    }
    /*
        void MatrixMultiply(Matrix* b) { //checked
          if (cols != b->rows) {
            Serial.println("Size mismatch in MatrixMultiply(Matrix* b): \n rows_" + name + ": " + String(rows) + "  cols_" + name + ": " + String(cols) + "  rows_" + b->name + ": " + String(b->rows)+"  cols_" + b->name + ": " + String(b->cols));
            delay(1000);
            while(true){};
          }
          static Matrix newMatrix;
          newMatrix.MatrixConstructor(rows, b->cols, "dotProduct("+name+", "+b->name+")");

          for (int i = 0; i < newMatrix.rows; i++) {
            for (int j = 0; j < newMatrix.cols; j++) {
              float sum = 0;
              for (int k = 0; k < cols; k++) {
                sum += data[i][k] * b->data[k][j];
              }
              newMatrix.data[i][j] = sum;
            }
          }
          setTo(&newMatrix);
          newMatrix.remove();
        }
    */
    void MatrixMultiply(Matrix* a, Matrix* b) { //no nenory loss
      if (a->cols != b->rows) {
        Serial.println("Size mismatch in MatrixMultiply(Matrix* a, Matrix* b): \n rows_" + a->name + ": " + String(a->rows) + "  cols_" + a->name + ": " + String(a->cols) + "  rows_" + b->name + ": " + String(b->rows) + "  cols_" + b->name + ": " + String(b->cols));
        delay(1000);
        while (true) {};
      }
      remove();
      MatrixConstructor(a->rows, b->cols);

      float newData[rows][cols];

      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          float sum = 0;
          for (int k = 0; k < a->cols; k++) {
            sum += a->data[i][k] * b->data[k][j];
          }
          newData[i][j] = sum;
        }
      }
      for (int i = 0; i < a->rows; i++) for (int j = 0; j < b->cols; j++) data[i][j] = newData[i][j];
    }

    void MatrixSubtract(Matrix* a, Matrix* b) { //no memory loss
      if (a->rows != b-> rows || a->cols != b-> cols) {
        //Serial.println(a->name);
        String outputText = "Size mismatch in MatrixSubtract(Matrix* a, Matrix* b): " + b->info2();
        Serial.println(outputText);
        delay(10000);
        while (true) {};
      }
      remove();
      MatrixConstructor(a->rows, a->cols);
      for (int i = 0; i < a->rows; i++) for (int j = 0; j < a->cols; j++) data[i][j] = a->data[i][j] - b->data[i][j];
    }
    /*
        void MatrixMultiply(Matrix* a, Matrix* b) { //checked
          if (a->cols != b->rows) {
            Serial.println("Size mismatch in MatrixMultiply(Matrix* a, Matrix* b): \n rows_" + a->name + ": " + String(a->rows) + "  cols_" + a->name + ": " + String(a->cols) + "  rows_" + b->name + ": " + String(b->rows)+"  cols_" + b->name + ": " + String(b->cols));
            delay(1000);
            while(true){};
          }
          static Matrix newMatrix;
          newMatrix.MatrixConstructor(a->rows, b->cols, "dotProduct("+a->name+", "+b->name+")");

          for (int i = 0; i < newMatrix.rows; i++) {
            for (int j = 0; j < newMatrix.cols; j++) {
              float sum = 0;
              for (int k = 0; k < a->cols; k++) {
                sum += a->data[i][k] * b->data[k][j];
              }
              newMatrix.data[i][j] = sum;
            }
          }
          setTo(&newMatrix);
          newMatrix.remove();
        }
    */
    /*
        Matrix* MatrixSubtract(Matrix* a, Matrix* b) { //checked
          if (a->rows != b-> rows || a->cols != b-> cols) {
            //Serial.println(a->name);
            String outputText = "Size mismatch in MatrixSubtract(Matrix* a, Matrix* b): " + b->info();
            Serial.println(outputText);
            delay(10000);
            while(true){};
          }
          static Matrix result;
          result.MatrixConstructor(a->rows, a->cols, "MatrixSubtract("+a->name+", "+b->name+")");
          for (int i = 0; i < a->rows; i++) for (int j = 0; j < a->cols; j++) result.data[i][j] = a->data[i][j] - b->data[i][j];
          return &result;
        }

        Matrix* transpose(Matrix* b) { //checked
          static Matrix newMatrix;
          newMatrix.MatrixConstructor(b->cols, b->rows, b->name+"_T");
          for (int i = 0; i < b->rows; i++) {
            for (int j = 0; j < b->cols; j++) {
              newMatrix.data[j][i] = b->data[i][j];
            }
          }
          return &newMatrix;
        }
    */
    void transpose() { //no memory loss
      int oldRows = rows, oldCols = cols;
      float newData[rows][cols];
      for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) newData[i][j] = data[i][j];
      remove();
      MatrixConstructor(oldCols, oldRows);
      for (int i = 0; i < oldRows; i++) {
        for (int j = 0; j < oldCols; j++) {
          data[j][i] = newData[i][j];
        }
      }
    }
    /*
        Matrix* MatrixFromArray(float Array[], int ArrayLength) { //checked
          static Matrix newMatrix;
          newMatrix.MatrixConstructor(ArrayLength, 1);
          for (int i = 0; i < newMatrix.rows; i++) {
            newMatrix.data[i][0] = Array[i];
          }
          //
          return &newMatrix;
        }
    */
    void matrixFromArray(Array* myArray) {
      if (rows != -1)remove();
      MatrixConstructor(myArray->length, 1);
      for (int i = 0; i < rows; i++) {
        data[i][0] = myArray->data[i];
      }
    }

    void map(Matrix* M, Function* f, float parameters[]) {
      if (rows != -1)remove();
      MatrixConstructor(M->rows, M->cols);
      for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) data[i][j] = f->apply(M->data[i][j], parameters, i, j, f->index);
    }
    void map(Matrix* M, Function* f, float a) { //no memory loss
      if (rows != -1)remove();
      MatrixConstructor(M->rows, M->cols);
      float parameters[] = {a};
      for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) data[i][j] = f->apply(M->data[i][j], parameters, i, j, f->index);
    }

    void map(Matrix* M, Function* f) {
      if (rows != -1)remove();
      MatrixConstructor(M->rows, M->cols);
      float parameters[] = {};
      for (int i = 0; i < rows; i++) for (int j = 0; j < cols; j++) data[i][j] = f->apply(M->data[i][j], parameters, i, j, f->index);
    }



    String arrayToString(float myArray[], int arrayLength, String text) { //checked
      text += "{";
      for (int i = 0; i < arrayLength; i++) {
        if (i < arrayLength - 1) text += (String(myArray[i]) + ",");
        else text += (String(myArray[i]));
      }
      text += "}";
      return text;
    }

    String MatrixToString(String text) { //checked
      text += "{\n";
      for (int i = 0; i < rows; i++) {
        text = arrayToString(data[i], cols, text);
        if (i < rows - 1) text += ",\n";
      }
      text += "\n}";
      return text;
    }
    /*
        void printOut() { //checked
          String firstLine = "float " + name + " [][] = ";
          Serial.println(MatrixToString(firstLine) + ";\n");
        }
    */
    void info() {
      Serial.println(name + "(" + String(rows) + ", " + String(cols) + ")");
    }

    String info2() {
      String text = name + "(" + String(rows) + ", " + String(cols) + ")";
      return text;
    }

    void printOut() { //checked
      String firstLine = "float " + name + "(" + rows + ", " + cols + ") = {";
      //String firstLine = "lol";
      Serial.println(firstLine);
      for (int i = 0; i < rows; i++) {
        Serial.print("{");
        for (int j = 0; j < cols; j++) {
          Serial.print(data[i][j]);
          if (j < cols - 1) Serial.print(", ");
        }
        if (i < rows - 1) Serial.println("},");
        else  Serial.println("}");
      }
      Serial.println("};");
    }



    float myRandom(float first, float last, int precision) { //checked
      precision = max(precision, 1);
      float factor = pow(10, precision - 1);
      float r = random(0, (last - first) * factor);
      r /= factor;
      r += first;
      return r;
    }

};

Matrix matrix("matrixForReference");


//////////////////////////////////////////////////////////////// NEURAL NETWORK
class NeuralNetwork {
  public:
    String name = "neural network";
    float learning_rate = 0.1;
    int numberOfLayers;
    int* numberOfNeurons;
    Matrix* neurons;
    Matrix* weights;
    Matrix* biases;

    NeuralNetwork() {}

    NeuralNetwork(int* NofNeurons, int numberOfLayers_) {
      constructor(NofNeurons, numberOfLayers_);
    }

    void constructor(int* NofNeurons, int numberOfLayers_) {
      //define shape of the network
      numberOfLayers = numberOfLayers_;
      numberOfNeurons = NofNeurons;

      neurons = (Matrix*)calloc(numberOfLayers, sizeof(Matrix));
      weights = (Matrix*)calloc(numberOfLayers - 1, sizeof(Matrix));
      biases = (Matrix*)calloc(numberOfLayers - 1, sizeof(Matrix));

      //initialise neurons, weights, biases
      for (int i = 0; i < numberOfLayers; i++) {
        if (i < numberOfLayers - 1) {
          weights[i].MatrixConstructor(numberOfNeurons[i + 1], numberOfNeurons[i]);
          biases[i].MatrixConstructor(numberOfNeurons[i + 1], 1);

          weights[i].setName("weights" + String(i));
          biases[i].setName("biases" + String(i));

          weights[i].randomise(); //might wanna do this in the constructor
          biases[i].randomise();
        }
        neurons[i].MatrixConstructor(numberOfNeurons[i], 1);
        neurons[i].setName("neurons" + String(i));
      }
    }

    void feedForward(Array* input_array) {
      neurons[0].setTo(input_array);
      for (int i = 0; i < numberOfLayers - 1; i++) {
        neurons[i + 1].MatrixMultiply(&weights[i], &neurons[i]);
        neurons[i + 1].add(&biases[i]);
        neurons[i + 1].map(&sigmoid);
      }
    }

    void train(Array* input_array, Array* desiredOutputs_array) {
      //feed forward the input to calculate all neuron values
      feedForward(input_array);

      Matrix previous_errors("previous_errors");
      for (int i = numberOfLayers - 1; i > 0; i--) {
        //calculate errors
        Matrix errors("errors");
        if (i == numberOfLayers - 1) {
          Matrix desiredOutputs_Matrix(desiredOutputs_array, "desiredOutputs_Matrix");
          errors.MatrixSubtract(&desiredOutputs_Matrix, &neurons[i]);
          desiredOutputs_Matrix.remove();
        }
        else {
          Matrix weights_i_T(&weights[i], "weights_i_T");
          weights_i_T.transpose();
          errors.MatrixMultiply(&weights_i_T, &previous_errors);
          weights_i_T.remove();
        }

        //calculate gradients
        Matrix gradients("gradients");
        gradients.map(&neurons[i], &dSigmoid);
        gradients.multiply(&errors);
        gradients.multiply(learning_rate);
        //adjust biases
        biases[i - 1].add(&gradients);
        //calculate deltas for weights
        Matrix weights_deltas("weights_deltas");
        Matrix neurons_im1_T(&neurons[i - 1], "neurons_im1_T");
        neurons_im1_T.transpose();
        weights_deltas.MatrixMultiply(&gradients, &neurons_im1_T);
        //adjust weights
        weights[i - 1].add(&weights_deltas);

        previous_errors.setTo(&errors);
        errors.remove();
        gradients.remove();
        weights_deltas.remove();
        neurons_im1_T.remove();
      }
      previous_errors.remove();
    }

    void fit(Matrix* inputsMatrix, Matrix* outputsMatrix, int epochs) {
      for (int i = 0; i < epochs; i++) {
        int sampleN = int(myRandom(0, inputsMatrix->rows, 1));
        //inputsArray.setTo(inputsMatrix->data[sampleN], inputsMatrix->cols);
        //outputsArray.setTo(outputsMatrix->data[sampleN], outputsMatrix->cols);
        input_Arrayq.setTo(inputsMatrix->data[sampleN], inputsMatrix->cols);
        output_Arrayq.setTo(outputsMatrix->data[sampleN], outputsMatrix->cols);
        train(&input_Arrayq, &output_Arrayq);
        //inputsArray.remove();
        //outputsArray.remove();
        if (i % 1000 == 0) Serial.println(i);
      }
    }

    void assignRandomNetwork() {
      for (int i = 0; i < numberOfLayers - 1; i++) {
        weights[i].randomise();
        biases[i].randomise();
      }
    }

    float myRandom(float first, float last, int precision) {
      precision = max(precision, 1);
      float factor = pow(10, precision - 1);
      float r = random(0, (last - first) * factor);
      r /= factor;
      r += first;
      return r;
    }
};




//////////////////////////////////////////////////////////////////////////Functions

/*
  String initialisePointers(Matrix a[], String pointerName) {
  String text = "";
  text += "char* " + pointerName + "[] = new char*[" + a.length + "];\n";
  return text;
  }

  String assignPointers(Matrix a[], String pointerName) {
  String text = "";
  for (int i = 0; i < a.length; i++) {
    text += pointerName + "[" + i + "] = " + a[i].name + ";\n";
  }
  return text;
  }

  String definePointers(Matrix a[], String pointerName) {
  String text = "";
  text += "char* " + pointerName + "[] = {";
  for (int i = 0; i < a.length; i++) {
    text += a[i].name;
    if (i < a.length - 1) text += ", ";
  }
  text+= "};\n";
  return text;
  }



  NeuralNetwork fileToNeuralNetwork(String fileName) {
  //extract text
  String extractedText[] = loadStrings(fileName);
  return stringArrayToNeuralNetwork(extractedText);

  }

*/


/*
  NeuralNetwork stringArrayToNeuralNetwork(String extractedText[]) {
  //calculate number of layers and neurons in them
  int numberOfLayers_n = 0;
  int numberOfNeurons_n_Temporary[10];
  String stringNumber = "";
  for (int i = 0; i < extractedText[0].length(); i++) {
    char c = extractedText[0].charAt(i);
    if (c == ',' || c == ';') {
      numberOfNeurons_n_Temporary[numberOfLayers_n] = int(stringNumber.toFloat());
      numberOfLayers_n++;
      stringNumber = "";
    } else stringNumber += c;
  }
  //assign numbers of neurons
  int numberOfNeurons_n[numberOfLayers_n];
  for (int i = 0; i < numberOfLayers_n; i++) numberOfNeurons_n[i] = numberOfNeurons_n_Temporary[i];
  //create a neural network of this shape
  NeuralNetwork n;
  n.NeuralNetworkConstructor(numberOfNeurons_n, sizeof(numberOfNeurons_n) / sizeof(numberOfNeurons_n[0]));

  //find weights
  int layer = 0, i = 0, j = 0;
  stringNumber = "";
  boolean doneWithWeights = false, metAnOpenBracket = false;
  int line = 1;
  for (; line < sizeof(extractedText) / sizeof(extractedText[0]) && !doneWithWeights; line++) {
    for (int index = 0; index < extractedText[line].length() && !doneWithWeights; index++) {
      char c = extractedText[line].charAt(index);
      if (layer == n.numberOfLayers - 1) doneWithWeights = true;
      else if (extractedText[line].length() < 2) line++;
      else if (i >= n.weights[layer].rows) {
        i = 0;
        j = 0;
        layer++;
      }
      else if (c == '{') {
        metAnOpenBracket = true;
      }
      else if (c == '}') {
        n.weights[layer].data[i][j] = stringNumber.toFloat();
        stringNumber = "";
        i++;
        j = 0;
        line++;
        index = -1;
        metAnOpenBracket = false;
      }
      else if (c == ',') {
        n.weights[layer].data[i][j] = stringNumber.toFloat();
        stringNumber = "";
        j++;
      }
      else if (metAnOpenBracket &&
               ((int(c) >= int('0') && int(c) <= int('9')) || c == '-' || c == '.')) stringNumber += c;
    }
  }

  //find biases
  layer = 0;
  i = 0;
  stringNumber = "";
  line--;
  boolean doneWithBiases = false;
  metAnOpenBracket = false;
  for (; line < sizeof(extractedText) / sizeof(extractedText[0]) && !doneWithBiases; line++) {
    for (int index = 0; index < extractedText[line].length() && !doneWithBiases; index++) {
      char c = extractedText[line].charAt(index);
      if (layer == n.numberOfLayers - 1) doneWithBiases = true;
      else if (extractedText[line].length() < 2) line++;
      else if (i >= n.biases[layer].rows) {
        i = 0;
        layer++;
      }
      else if (c == '{') metAnOpenBracket = true;
      else if (c == '}') {
        n.biases[layer].data[i][0] = stringNumber.toFloat();
        stringNumber = "";
        i = 0;
        line++;
        index = 0;
        metAnOpenBracket = false;
        layer++;
      }
      else if (c == ',') {
        n.biases[layer].data[i][0] = stringNumber.toFloat();
        stringNumber = "";
        i++;
      }
      else if (metAnOpenBracket &&
               ((int(c) >= int('0') && int(c) <= int('9')) || c == '-' || c == '.')) stringNumber += c;
    }
  }
  return n;
  }


  NeuralNetwork longStringToNeuralNetwork(String text) {
  //calculate number of layers and neurons in them
  int numberOfLayers_n = 0;
  int numberOfNeurons_n_Temporary[10];
  String stringNumber = "";
  for (int i = 0; text.charAt(i) != '\n'; i++) {
    char c = text.charAt(i);
    if (c == ',' || c == ';') {
      numberOfNeurons_n_Temporary[numberOfLayers_n] = int(stringNumber.toFloat());
      numberOfLayers_n++;
      stringNumber = "";
    } else stringNumber += c;
  }

  int lines = 2 + 2 * (numberOfLayers_n - 1) + 2; //last +2 just in case
  for (int i = 1; i < numberOfLayers_n; i++) {
    lines += numberOfNeurons_n_Temporary[numberOfLayers_n] + 2;
  }
  String extractedTextArray[lines];
  for (int i = 0; i < sizeof(extractedTextArray) / sizeof(extractedTextArray[0]); i++) extractedTextArray[i] = "";
  int line = 0;
  for (int i = 0; i < text.length(); i++) {
    char c = text.charAt(i);
    if (c == '\n') line++;
    else extractedTextArray[line] += c;
  }
  return stringArrayToNeuralNetwork(extractedTextArray);
  }

*/
