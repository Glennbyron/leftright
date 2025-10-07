# Political Alignment Predictor

I will run the code a handful of times to see if it can accurately predict my political alignment based on my responses to a series of questions.

If you wish to have a fresh start, delete the `responses.csv` file.

It will make a new one after you run the code and answer the questions.



To run this code, you need to have Python installed on your machine. You can download it from [python.org](https://www.python.org/downloads/).

# Requirements:

C++ compiler

Python 3.x

pandas

scikit-learn



You can install the required libraries using pip:

pip install pandas scikit-learn



Open a terminal and navigate to the directory where the script is located. Then run the script using the following command:

Eample: C:\Users\gbyron\source\repos\leftright

python train_model.py

This will execute the script and you should see output indicating the progress of the model training and evaluation.

# Machine Learning Model Training and Evaluation

This repository contains a Python script that trains and evaluates a machine learning model using the RandomForestClassifier from the scikit-learn library.

The script reads data from a CSV file, preprocesses it, splits it into training and testing sets, trains the model, and evaluates its performance.



This will:



Ask the user 10 political questions.

Predict their political alignment.

Ask for their self-identified political label.

Save the results to responses.csv.





Example Output

Should we have universal healthcare?

1. Strongly support

2. Somewhat support

3. Neutral

4. Oppose

Your choice (1-4): 1

Current guess: Democrat

...

Final prediction: Democrat



How do you currently identify politically?

1. Democrat

2. Republican

3. Libertarian

4. Green

5. Other / Prefer not to say

Your choice (1-5): 1



Thank you! Your responses have been recorded in 'responses.csv'.



Sample Python Output

Model Evaluation Metrics:

Quize Accuracy : 0.85

Quize Precision: 0.86

Quize Recall  : 0.85

Quize F1 Score : 0.85